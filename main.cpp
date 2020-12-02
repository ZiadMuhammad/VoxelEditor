#include<iostream>
#include <GL/glut.h>
#include<vector>
#include <stdio.h>
#define PI 3.1415927
#include<math.h>


using namespace std;
#include<windows.h>
#include<mmsystem.h>

//Cylinder Data
float x              = 0.0;
float y              = 0.0;
float angle          = 0.0;
float angle_stepsize = 0.1;
float radius = 0.2;
float height = 0.2;

float cx = 0.6;
float cy = 0;
float cz = 0;

bool shapeSpwaned = false;
char currentObject = 's';
char currentColor = 'w';

float rot = 0;
float coinAnim = 0;

struct SpawnedCubes {
    float x, y, z, r, g, b;
}; vector<SpawnedCubes> shapes;

struct SpawnedIcemen {
    float x[5], y[5], z[5];
}; vector<SpawnedIcemen> icemen;

struct SpawnedTrees {
    float x[3], y[3], z[3];
}; vector<SpawnedTrees> trees;

struct spawnedCylinders {
    float x, y, z;
}; vector<spawnedCylinders> cylinders;

void timer(int);

void objectSpawner() {
    float r, g, b;
    if(currentObject == 's') {
        if(currentColor == 'r') {
            r = 1.000;
            g = 0.000;
            b = 0.000;
        } else if(currentColor == 'g') {
            r = 0.000;
            g = 1.000;
            b = 0.000;
        } else if(currentColor == 'b') {
            r = 0.000;
            g = 0.000;
            b = 1.000;
        } else {
            r = 1.000;
            g = 1.000;
            b = 1.000;
        }
        glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(cx, cy, cz);
        glutSolidCube(0.9);
        glPopMatrix();
    } else if(currentObject == 'a') {
        //Iceman Lower
        glPushMatrix();
        glColor3f(0.878, 1.000, 1.000);
        glTranslatef(cx, cy, cz);
        glutSolidSphere(0.9, 20, 20);
        glPopMatrix();
        //Iceman Mid
        glPushMatrix();
        glColor3f(0.878, 1.000, 1.000);
        glTranslatef(cx, cy+1, cz);
        glutSolidSphere(0.7, 20, 20);
        glPopMatrix();
        //Iceman Higher
        glPushMatrix();
        glColor3f(0.878, 1.000, 1.000);
        glTranslatef(cx, cy+2, cz);
        glutSolidSphere(0.5, 20, 20);
        glPopMatrix();
        //Iceman Eye 1
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(cx - 0.1, cy+2.3, cz+0.5);
        glutSolidSphere(0.1, 20, 20);
        glPopMatrix();
        //Iceman Eye 2
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(cx + 0.2, cy+2.3, cz+0.5);
        glutSolidSphere(0.1, 20, 20);
        glPopMatrix();
    } else if(currentObject == 't') {
        //Tree Base
        glPushMatrix();
        glColor3f(0.196, 0.804, 0.196);
        glTranslatef(cx, cy, cz);
        glRotatef(240, 1.0, 1.0, 1.0);
        glutSolidCone(0.5, 2, 20, 20);
        glPopMatrix();
        //Tree Mid
        glPushMatrix();
        glColor3f(0.196, 0.804, 0.196);
        glTranslatef(cx, cy + 1, cz);
        glRotatef(240, 1.0, 1.0, 1.0);
        glutSolidCone(0.5, 2, 20, 20);
        glPopMatrix();
        //Tree High
        glPushMatrix();
        glColor3f(0.196, 0.804, 0.196);
        glTranslatef(cx, cy + 2, cz);
        glRotatef(240, 1.0, 1.0, 1.0);
        glutSolidCone(0.4, 2, 20, 20);
        glPopMatrix();
    } else if(currentObject == 'c') {
        glPushMatrix();
        glTranslatef(cx, cy + 1, cz);
        glColor3f(0.722, 0.525, 0.043);
        glBegin(GL_QUAD_STRIP);
        angle = 0.0;
            while( angle < 2 * PI ) {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , height);
                glVertex3f(x, y , 0.0);
                angle = angle + angle_stepsize;
            }
            glVertex3f(radius, 0.0, height);
            glVertex3f(radius, 0.0, 0.0);
        glEnd();

        glColor3f(0.855, 0.647, 0.125);
        glBegin(GL_POLYGON);
        angle = 0.0;
            while( angle < 2*PI ) {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , height);
                angle = angle + angle_stepsize;
            }
            glVertex3f(radius, 0.0, height);
        glEnd();

    glPopMatrix();
    }
}

void addCube() {
    SpawnedCubes c;
    c.x = cx;
    c.y = cy;
    c.z = cz;

    if(currentColor == 'r') {
        c.r = 1.000;
        c.g = 0.000;
        c.b = 0.000;
    } else if(currentColor == 'g') {
        c.r = 0.000;
        c.g = 1.000;
        c.b = 0.000;
    } else if(currentColor == 'b') {
        c.r = 0.000;
        c.g = 0.000;
        c.b = 1.000;
    } else {
        c.r = 1.000;
        c.g = 1.000;
        c.b = 1.000;
    }

    shapes.push_back(c);
}

void addCylinder() {
    spawnedCylinders c;
    c.x = cx;
    c.y = cy;
    c.z = cz;
    cylinders.push_back(c);
}

void addIceman() {
    SpawnedIcemen c;
    c.x[0] = cx;
    c.y[0] = cy;
    c.z[0] = cz;

    c.x[1] = cx;
    c.y[1] = cy + 1;
    c.z[1] = cz;

    c.x[2] = cx;
    c.y[2] = cy + 2;
    c.z[2] = cz;

    c.x[3] = cx - 0.1;
    c.y[3] = cy + 2.3;
    c.z[3] = cz + 0.5;

    c.x[4] = cx + 0.2;
    c.y[4] = cy + 2.3;
    c.z[4] = cz + 0.5;

    icemen.push_back(c);
}

void addTree() {
    cout << "tree added";
    SpawnedTrees c;
    c.x[0] = cx;
    c.y[0] = cy;
    c.z[0] = cz;

    c.x[1] = cx;
    c.y[1] = cy + 1;
    c.z[1] = cz;

    c.x[2] = cx;
    c.y[2] = cy + 2;
    c.z[2] = cz;

    trees.push_back(c);
}

void spawnObjects() {
    for(int i = 0; i < shapes.size(); i++) {
        glPushMatrix();
        glColor3f(shapes[i].r, shapes[i].g, shapes[i].b);
        glTranslatef(shapes[i].x, shapes[i].y, shapes[i].z);
        glutSolidCube(0.9);
        glPopMatrix();
        shapeSpwaned = true;
    }

    for(int i = 0; i < icemen.size(); i++) {
        //Iceman Lower
        glPushMatrix();
        glColor3f(0.878, 1.000, 1.000);
        glTranslatef(icemen[i].x[0], icemen[i].y[0], icemen[i].z[0]);
        glutSolidSphere(0.9, 20, 20);
        glPopMatrix();
        //Iceman Mid
        glPushMatrix();
        glColor3f(0.878, 1.000, 1.000);
        glTranslatef(icemen[i].x[1], icemen[i].y[1], icemen[i].z[1]);
        glutSolidSphere(0.7, 20, 20);
        glPopMatrix();
        //Iceman Higher
        glPushMatrix();
        glColor3f(0.878, 1.000, 1.000);
        glTranslatef(icemen[i].x[2], icemen[i].y[2], icemen[i].z[2]);
        glutSolidSphere(0.5, 20, 20);
        glPopMatrix();
        //Iceman Eye 1
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(icemen[i].x[3], icemen[i].y[3], icemen[i].z[3]);
        glutSolidSphere(0.1, 20, 20);
        glPopMatrix();
        //Iceman Eye 2
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(icemen[i].x[4], icemen[i].y[4], icemen[i].z[4]);
        glutSolidSphere(0.1, 20, 20);
        glPopMatrix();
    }

    for(int i = 0; i < trees.size(); i++) {
        //Tree Base
        glPushMatrix();
        glColor3f(0.196, 0.804, 0.196);
        glTranslatef(trees[i].x[0], trees[i].y[0], trees[i].z[0]);
        glRotatef(240, 1.0, 1.0, 1.0);
        glutSolidCone(0.5, 2, 20, 20);
        glPopMatrix();
        //Tree Mid
        glPushMatrix();
        glColor3f(0.196, 0.804, 0.196);
        glTranslatef(trees[i].x[1], trees[i].y[1], trees[i].z[1]);
        glRotatef(240, 1.0, 1.0, 1.0);
        glutSolidCone(0.5, 2, 20, 20);
        glPopMatrix();
        //Tree High
        glPushMatrix();
        glColor3f(0.196, 0.804, 0.196);
        glTranslatef(trees[i].x[2], trees[i].y[2], trees[i].z[2]);
        glRotatef(240, 1.0, 1.0, 1.0);
        glutSolidCone(0.4, 2, 20, 20);
        glPopMatrix();
    }

    for(int i = 0; i < cylinders.size(); i++) {
        glPushMatrix();
        glRotated(coinAnim, 0.0, 1.0, 0);
        glTranslatef(cylinders[i].x, cylinders[i].y + 1, cylinders[i].z);
        glColor3f(0.722, 0.525, 0.043);
        glBegin(GL_QUAD_STRIP);
        angle = 0.0;
            while( angle < 2 * PI ) {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , height);
                glVertex3f(x, y , 0.0);
                angle = angle + angle_stepsize;
            }
            glVertex3f(radius, 0.0, height);
            glVertex3f(radius, 0.0, 0.0);
        glEnd();

        glColor3f(0.855, 0.647, 0.125);
        glBegin(GL_POLYGON);
        angle = 0.0;
            while( angle < 2*PI ) {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , height);
                angle = angle + angle_stepsize;
            }
            glVertex3f(radius, 0.0, height);
        glEnd();

    glPopMatrix();
    }
}

void drawGrid() {
    int i;

    for(i = 0; i < 40; i++) {
        glPushMatrix();
        if(i < 20) {
            glTranslatef(0, 0, i);
        }
        if(i >= 20) {
            glTranslatef(i-20, 0, 0);
            glRotatef(-90, 0, 1, 0);
        }

        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glLineWidth(1);
        glVertex3f(0, -0.1, 0);
        glVertex3f(19, -0.1, 0);
        glEnd();
        glPopMatrix();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if(key == 'w') {
        cz -= 1;
    }
    if(key == 's') {
        cz += 1;
    }
    if(key == 'a') {
        cx -= 1;
    }
    if(key == 'd') {
        cx += 1;
    }
    if(key == 'q') {
        cy += 1;
    }
    if(key == 'z') {
        cy -= 1;
    }
    if(key == 32) {
        if(currentObject == 's') {
            addCube();
        } else if(currentObject == 'a') {
            addIceman();
        } else if(currentObject == 't') {
            addTree();
        } else {
            addCylinder();
        }
    }
    if(key == 49) {
        currentObject = 's';
    }
    if(key == 50) {
        currentObject = 'a';
    }
    if(key == 51) {
        currentObject = 't';
    }
    if(key == 52) {
        currentObject = 'c';
    }
    if(key == 'r') {
        currentColor = 'r';
        cout << currentColor;
    }
    if(key == 'g') {
        currentColor = 'g';
    }
    if(key == 'b') {
        currentColor = 'b';
    }
    if(key == 'p') {
        currentColor = 'w';
    }

    glutPostRedisplay();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35, 1.0f, 0.1f, 1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.1, 0.1, 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glClearColor(0.529, 0.808, 0.922, 1.000);

    glTranslatef(-13, 0, -45);
    glRotatef(40, 1, 1, 0);

    //Cloud 1
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0.000 + rot, 10.000, 15.000);
    glutSolidSphere(0.7, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0.700 + rot, 10.000, 15.000);
    glutSolidSphere(0.6, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-0.700 + rot, 10.000, 15.000);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    //Cloud 2


    drawGrid();
    objectSpawner();
    spawnObjects();
    glutSwapBuffers();
}


void texture (void){

    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
    rot += 0.1;
    coinAnim += 0.02;

    if(coinAnim > 2) {
            coinAnim -= 2;
    }

    if(rot > 20) {
        rot = rot - 50;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("17100315");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, timer, 0);
    sndPlaySound("breakout.wav", SND_ASYNC);
    init();
    texture();
    glutMainLoop();

    return 0;
}
