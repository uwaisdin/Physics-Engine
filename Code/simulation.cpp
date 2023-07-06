#include "simulation.h"
#include "glut.h"
#include <iostream>

using namespace std;

vector<sphere*> simulation::s;
vector<cube*> simulation::c;
ground simulation::g;

/* constructor */
simulation::simulation() {

    s = vector<sphere*>();
    c = vector<cube*>();
    g = ground();

}
/* destructor */
simulation::~simulation() {

    for (int i = 0; i < s.size(); i++) {
        delete s[i];
    }
    for (int i = 0; i < c.size(); i++) {
        delete c[i];
    }
    s.clear();
    c.clear();

}

/* setters and getters */
void simulation::addSphere(sphere& s) {

    this->s.push_back(&s);

}

void simulation::addCube(cube& c) {

    this->c.push_back(&c);

}

vector<sphere*>& simulation::getSpheres() {

    return s;

}

vector<cube*>& simulation::getCubes() {

    return c;

}

/* simulation functions */
void simulation::drawPlane() {

    glTranslatef(0.0f, 0.0f, 0.0f); // set ground height
    glBegin(GL_QUADS); // draw ground using quad
    glNormal3f(0.0f, 1.0f, 0.0f); // set the normal vector for lighting

    /* cooridinates of ground vertexs */
    glVertex3f(-20.0f, 0.0f, -20.0f);
    glVertex3f(-20.0f, 0.0f, 20.0f);
    glVertex3f(20.0f, 0.0f, 20.0f);
    glVertex3f(20.0f, 0.0f, -20.0f);

    glColor3f(0.0, 1.0, 0.0); // set the color of the plane
    glEnd();
}

void simulation::collisions(sphere*& s1, sphere*& s2) {


    if (s1->detect(g) == true) {
        s1->res(g);
    }
    if (s1->detect(*s2) == true) { // detect collision with other sphere
        s1->res(*s2); // resolve collision with other sphere
    }
    s1->integrate(0.01);
}

void simulation::collisions(cube*& c1, cube*& c2, sphere*& s1, sphere*& s2) {
    
    if (c1->detect(g) == true) {
        c1->res(g);
    }
    if (c1->detect(*c2) == true) { // detect collision with other sphere
        c1->res(*c2); // resolve collision with other sphere
    }
    if (c1->detect(*s1) == true) { // detect collision with other sphere
        c1->res(*s1); // resolve collision with other sphere
    }
    if (c1->detect(*s2) == true) { // detect collision with other sphere
        c1->res(*s2); // resolve collision with other sphere
    }
    
    c1->integrate(0.01);
}


void simulation::drawSphere() {

    for (int i = 0; i < s.size(); i++) {
        glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(s[i]->getPosition().getX(), s[i]->getPosition().getY(),
                     s[i]->getPosition().getZ());
        glutSolidSphere(s[i]->getRadius(), 50, 50); // stacks and slices
        glPopMatrix();
    }
}

void simulation::drawCube() {

    for (int i = 0; i < c.size(); i++) {
        glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(c[i]->getPosition().getX(), c[i]->getPosition().getY(),
                     c[i]->getPosition().getZ());
        glutSolidCube(c[i]->getRadius() * 2);
        glPopMatrix();
    }
    /* push and pop matrix so drawn independently 
    so they dont appear to overlap or intersect */
}


void simulation::display() {

    // clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100); // setup perspective projection

    // set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 10, 40, 0, 0, 0, 0, 1, 0); // camera position and orientation

    // draw ground
    drawPlane();

    // collision detection and resolution for spheres and draw spheres
    collisions(s[0], s[1]);
    collisions(s[1], s[0]);
    drawSphere();

   // collision detection and resolution for cubes and draw cubes
   collisions(c[0], c[1], s[0], s[1]);
   collisions(c[1], c[0], s[0], s[1]);
   drawCube();

    glutSwapBuffers();  // visualise simulation
    glFlush(); // flush the graphics pipeline
}


void simulation::light() {

    // set the material and lighting properties

    /* material properties */
    // amount of light relfected by material
    GLfloat material_ambience[] = { 0.2, 0.2, 0.2, 1 };
    // amount of light scattered by material
    GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1 };


    /* light properites */
    // normal light source
    GLfloat light_position[] = { 1, 1, 1, 0 };
    // ambient light source 
    GLfloat light_ambience[] = { 0.8, 0.8, 0.8, 0.8 };
    // diffuse of source
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    // shininess of light 
    GLfloat light_specular[] = { 1, 1, 1, 1 };

    /* enabling and setting up the light */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambience);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambience);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);


    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // background colour

}


void simulation::reshape(int w, int h) {

    // set viewport to match window size 
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1, 20);
  
   


}

void simulation::idle() {

    /* updates display continuously for
     smooth simulation */
    glutPostRedisplay();

}

void simulation::run_sim() {

    /* creating window */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Simulation");

    /* apply functions */
    light();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    /* program stops when window is closed */
    glutMainLoop();

}