#include "application.h"

#include <iostream>
#include <cassert>

using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "SOIL/SOIL.h"
void draw_grid();

application::application() 
    : solid(true), sun(false), galaxy(false)
{
    mercury_x = 7;
    mercury_y = 0;
    mercury_z = 7;

    venus_x = 10;
    venus_y = 0;
    venus_z = -10;

    earth_x = -15;
    earth_y = 0;
    earth_z = -15;

    moon_x = -3;
    moon_y = 1;
    moon_z = -3;
}

application::~application()
{
}

// triggered once after the OpenGL context is initialized
void application::init_event()
{

    cout << "CONTROLE DE CAMERA: \n  Mouse-botao-esquerda: Rotate \n  Mouse-botao-meio: Pan \n  Mouse-botao-direita: Dolly" << endl;
    cout << "TECLAS DE ACOES: \n  '=': muda a textura\n  't': muda o foco para a terra\n  'l': muda o foco para a lua\n  's': muda o foco para o sol" << endl;
    cout << "\n* PARA SAIR A QUALQUER MOMENTO 'Esc'"<< endl;
    const GLfloat ambient[] = { 0.15, 0.15, 0.15, 1.0 };
    const GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
    const GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    if (!load_gltextures())
        exit(255);
    // enable a light
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glEnable(GL_LIGHT1);
    
    // enable depth-testing, colored materials, and lighting
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    
    // normalize normals so lighting calculations are correct
    // when using GLUT primitives
    glEnable(GL_NORMALIZE);
    
    // enable smooth shading
    glShadeModel(GL_SMOOTH);

    // set the cameras default coordinates
    camera.set_distance(40);
    camera.set_elevation(35);
    camera.set_twist(45);

    t.reset();
}

bool application::load_gltextures()
{
    texture[0] = SOIL_load_OGL_texture ( "/home/lucas/fire.jpg",
                                         SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[1] = SOIL_load_OGL_texture ( "/home/lucas/10.jpg",
                                         SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[2] = SOIL_load_OGL_texture ( "/home/lucas/100.jpg",
                                         SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[3] = SOIL_load_OGL_texture ( "/home/lucas/galaxy.jpg",
                                         SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(texture[0] == 0 || texture[1] == 0 || texture[2] == 0 || texture[3] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    return true;
}

void application::draw_event()
{
    camera.apply_gl_transform();
    const GLfloat light_pos1[] = { 0.0, float(radius_sun), 0.0, 10 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
    //draw_grid();
    glEnable(GL_TEXTURE_2D);
    draw_galaxy();
    draw_sun();
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glPushMatrix();
    glRotatef(-t.elapsed()*180, 0, 1, 0);
    draw_mercury();
    glPopMatrix();
    glPushMatrix();
    glRotatef(-t.elapsed()*90, 0, 1, 0);
    draw_venus();
    glPopMatrix();
    glPushMatrix();
    glRotatef(-t.elapsed()*45, 0, 1, 0);
    draw_earth();
    glPushMatrix();
    glTranslatef(earth_x, earth_y, earth_z);
    glRotatef(-t.elapsed()*20, 0, 1, 0);
    draw_moon();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

// triggered when mouse is clicked
void application::mouse_click_event(
        mouse_button button, mouse_button_state button_state,
        int x, int y
        )
{
    if (button == 3)
        camera.set_distance(camera.get_distance()-2);
    else if (button == 4)
        camera.set_distance(camera.get_distance()+2);
}

// triggered when mouse button is held down and the mouse is
// moved
void application::mouse_move_event(
        int x, int y
        )
{
}

// triggered when a key is pressed on the keyboard
void application::keyboard_event(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    else if (key == '=')
        solid = !solid;
    else if (key == 't')
        camera.set_focal_point({earth_x, earth_y, earth_z});
    else if (key == 'l')
        camera.set_focal_point({moon_x, moon_y, moon_z});
    else if (key == 's')
        camera.set_focal_point({0, 0, 0});
}

void draw_grid()
{
    glDisable(GL_LIGHTING);
    glLineWidth(2.0);

    //
    // Draws the coordinate frame at origin
    //
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBegin(GL_LINES);

    // x-axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    
    // y-axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    
    // z-axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glPopMatrix();
    
    //
    // Draws a grid along the x-z plane
    //
    glLineWidth(1.0);
    glColor3f(.20, .20, .20);
    glBegin(GL_LINES);

    int ncells = 50;
    int ncells2 = ncells/2;

    for (int i= 0; i <= ncells; i++)
    {
        int k = -ncells2;
        k +=i;
        glVertex3f(ncells2,0,k);
        glVertex3f(-ncells2,0,k);
        glVertex3f(k,0,ncells2);
        glVertex3f(k,0,-ncells2);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void application::draw_solid(double rad, GLuint texture)
{
    GLUquadric *sphere = gluNewQuadric();
    galaxy ? gluQuadricDrawStyle(sphere, GLU_LINE) : gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, texture);
    gluQuadricTexture(sphere, GL_TRUE);
    sun ? gluQuadricNormals(sphere, GLU_NONE) : gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, rad, 4096, 4096);
}

void application::draw_galaxy()
{
    galaxy = false;
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0, 3, 0);
    glRotatef(t.elapsed()*1, 0, 1, 0);
    glScalef(0.5, 0.5, 0.5);
    draw_solid(100, texture[3]);
    glPopMatrix();
    galaxy = false;
}

void application::draw_sun()
{
    sun = true;
    glPushMatrix();

    glColor4f(1, 1, 0, 0);
    glTranslatef(0, 3, 0);
    glRotatef(t.elapsed()*180, 0, 1, 0);
    glScalef(0.5, 0.5, 0.5);
    solid ? draw_solid(radius_sun, texture[0]) : draw_solid(radius_sun, texture[1]);
    glPopMatrix();
    sun = false;
}

void application::draw_mercury()
{
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(mercury_x, mercury_y, mercury_z);
    glRotatef(-t.elapsed()*30, 0, 1, 0);
    solid ? draw_solid(radius_mercury, texture[0]) : draw_solid(radius_mercury, texture[2]);
    glPopMatrix();
}

void application::draw_venus()
{
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(venus_x, venus_y, venus_z);
    glRotatef(-t.elapsed()*90, 0, 1, 0);
    solid ? draw_solid(radius_venus, texture[0]) : draw_solid(radius_venus, texture[1]);
    glPopMatrix();
}

void application::draw_earth()
{
    glPushMatrix();
    glColor4f(0, 0.5, 1, 0);
    glTranslatef(earth_x, earth_y, earth_z);
    glRotatef(-t.elapsed()*365, 0, 1, 0);
    draw_solid(radius_earth, texture[1]);
    glPopMatrix();
}

void application::draw_moon()
{
    glPushMatrix();
    glColor4f(0.7f, 0.7f, 0.7f, 1);
    glTranslatef(moon_x, moon_y, moon_z);
    glRotatef(-t.elapsed()*80, 0, 1, 0);
    draw_solid(radius_moon, texture[2]);
    glPopMatrix();
}
