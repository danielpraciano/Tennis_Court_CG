#include <render/include/myglwidget.h>

#include <QMouseEvent>

// Models
#include <scenario/include/object/models/BlenderBarn.h>
#include <scenario/include/object/models/BlenderCloud.h>
#include <scenario/include/object/models/BlenderCow.h>
#include <scenario/include/object/models/BlenderDog.h>
#include <scenario/include/object/models/BlenderFarmer.h>
#include <scenario/include/object/models/BlenderFence.h>
#include <scenario/include/object/models/BlenderCube.h>
#include <scenario/include/object/models/BlenderHay.h>
#include <scenario/include/object/models/BlenderLamp.h>
#include <scenario/include/object/models/BlenderMill.h>
#include <scenario/include/object/models/BlenderSilo.h>
#include <scenario/include/object/models/BlenderTerrain.h>
#include <scenario/include/object/models/BlenderTree.h>

#include <core/include/util.h>

GLuint  Court;
GLuint  Net;

void draw_court_lines() {
   glPushMatrix ();
   glScalef(1.5, 1.0, 1.0);
   glCallList (Court);
   glPopMatrix ();
   return;
}

void draw_net_lines() {
   glPushMatrix ();
   glScalef(1.5, 1.0, 1.0);
   glCallList (Net);
   glPopMatrix ();
   return;
}

void add_court_matrix() {
    GLfloat k_a_white[] = { 1.0, 1.0, 1.0 };
    GLfloat k_d_white[] = { 1.0, 1.0, 1.0 };
    GLfloat k_s_white[] = { 1.0, 1.0, 1.0 };
    GLfloat m_white     = 1.0;

   Court = glGenLists (1);
   glNewList (Court, GL_COMPILE);
   {
          //sidelines doubles
          glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_white);
          glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_white);
          glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_white);
          glMaterialf (GL_FRONT, GL_SHININESS, m_white);

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f  (0.0, 0.0, 0.0);
          glTexCoord2f(0.0, 1.0); glVertex3f  (0.0, 0.0, 24.002);
          glTexCoord2f(1.0, 1.0); glVertex3f  (0.1, 0.0, 24.002);
          glTexCoord2f(1.0, 0.0); glVertex3f  (0.1, 0.0, 0.0);
       glEnd();

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f  (8.2, 0.0, 0.0);
          glTexCoord2f(0.0, 1.0); glVertex3f  (8.2, 0.0, 24.002);
          glTexCoord2f(1.0, 1.0); glVertex3f  (8.3, 0.0, 24.002);
          glTexCoord2f(1.0, 0.0); glVertex3f  (8.3, 0.0, 0.0);
       glEnd();

       //sidelines single
       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f  (1.0, 0.0, 0.0);
          glTexCoord2f(0.0, 1.0); glVertex3f  (1.0, 0.0, 24.002);
          glTexCoord2f(1.0, 1.0); glVertex3f  (1.1, 0.0, 24.002);
          glTexCoord2f(1.0, 0.0); glVertex3f  (1.1, 0.0, 0.0);
       glEnd();

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (7.2, 0.0, 0.0);
          glTexCoord2f(0.0, 1.0); glVertex3f (7.2, 0.0, 24.002);
          glTexCoord2f(1.0, 1.0); glVertex3f (7.3, 0.0, 24.002);
          glTexCoord2f(1.0, 0.0); glVertex3f (7.3, 0.0, 0.0);
       glEnd();

       //baselines
       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (0.0, 0.0, 0.0);
          glTexCoord2f(0.0, 1.0); glVertex3f (0.0, 0.0, 0.1);//35
          glTexCoord2f(1.0, 1.0); glVertex3f (8.2, 0.0, 0.1);
          glTexCoord2f(1.0, 0.0); glVertex3f (8.2, 0.0, 0.0);
       glEnd();

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (0.0, 0.0, 23.90);
          glTexCoord2f(0.0, 1.0); glVertex3f (0.0, 0.0, 24.00);
          glTexCoord2f(1.0, 1.0); glVertex3f (8.2, 0.0, 24.00);
          glTexCoord2f(1.0, 0.0); glVertex3f (8.2, 0.0, 23.90);
       glEnd();

       //service lines
       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (1.05, 0.0, 5.6);
          glTexCoord2f(0.0, 1.0); glVertex3f (1.05, 0.0, 5.7);
          glTexCoord2f(1.0, 1.0); glVertex3f (7.2, 0.0, 5.7);
          glTexCoord2f(1.0, 0.0); glVertex3f (7.2, 0.0, 5.6);
       glEnd();

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (1.05, 0.0, 18.3);
          glTexCoord2f(0.0, 1.0); glVertex3f (1.05, 0.0, 18.4);
          glTexCoord2f(1.0, 1.0); glVertex3f (7.2, 0.0, 18.4);
          glTexCoord2f(1.0, 0.0); glVertex3f (7.2, 0.0, 18.3);
       glEnd();

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (4.0, 0.0, 5.7);
          glTexCoord2f(0.0, 1.0); glVertex3f (4.0, 0.0, 18.3);
          glTexCoord2f(1.0, 1.0); glVertex3f (4.1, 0.0, 18.3);
          glTexCoord2f(1.0, 0.0); glVertex3f (4.1, 0.0, 5.7);
       glEnd();

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (4.0, 0.0, 0.0);
          glTexCoord2f(0.0, 1.0); glVertex3f (4.0, 0.0, 0.5);
          glTexCoord2f(1.0, 1.0); glVertex3f (4.1, 0.0, 0.5);
          glTexCoord2f(1.0, 0.0); glVertex3f (4.1, 0.0, 0.0);
       glEnd();

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (4.0, 0.0, 23.50);
          glTexCoord2f(0.0, 1.0); glVertex3f (4.0, 0.0, 24.002);
          glTexCoord2f(1.0, 1.0); glVertex3f (4.1, 0.0, 24.002);
          glTexCoord2f(1.0, 0.0); glVertex3f (4.1, 0.0, 23.50);
       glEnd();
   }

   glEndList();
}

void add_net_matrix() {
    GLfloat k_a_white[] = { 1.0, 1.0, 1.0 };
    GLfloat k_d_white[] = { 1.0, 1.0, 1.0 };
    GLfloat k_s_white[] = { 1.0, 1.0, 1.0 };
    GLfloat m_white     = 1.0;

    GLfloat k_a_black[] = { 0.0, 0.0, 0.0 };
    GLfloat k_d_black[] = { 0.0, 0.0, 0.0 };
    GLfloat k_s_black[] = { 0.0, 0.0, 0.0 };
    GLfloat m_black     = 1.0;


   Net = glGenLists (1);
   glNewList (Net, GL_COMPILE);
   {
       glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_white);
       glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_white);
       glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_white);
       glMaterialf (GL_FRONT, GL_SHININESS, m_white);

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (-0.55, 0.0, 12.0);
          glTexCoord2f(0.0, 1.0); glVertex3f (-0.4, 0.0, 12.0);
          glTexCoord2f(1.0, 1.0); glVertex3f (-0.4, 1.0, 12.0);
          glTexCoord2f(1.0, 0.0); glVertex3f (-0.55, 1.0, 12.0);
       glEnd();

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f (8.65, 0.0, 12.0);
          glTexCoord2f(0.0, 1.0); glVertex3f (8.8, 0.0, 12.0);
          glTexCoord2f(1.0, 1.0); glVertex3f (8.8, 1.0, 12.0);
          glTexCoord2f(1.0, 0.0); glVertex3f (8.65, 1.0, 12.0);
       glEnd();

       glBegin(GL_QUADS);
          glNormal3f (0.0, 1.0, 0.0);
          glTexCoord2f(0.0, 1.0); glVertex3f (-0.39, 0.89, 12.1);
          glTexCoord2f(0.0, 0.0); glVertex3f (8.64, 0.89, 12.1);
          glTexCoord2f(1.0, 0.0); glVertex3f (8.64, 1.0, 12.0);
          glTexCoord2f(1.0, 1.0); glVertex3f (-0.39, 1.0, 12.0);

       glEnd();

       glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_black);
       glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_black);
       glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_black);
       glMaterialf (GL_FRONT, GL_SHININESS, m_black);

       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.87, 12.0);
          glVertex3f(-0.38, 0.87, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.8, 12.0);
          glVertex3f(-0.38, 0.8, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.73, 12.0);
          glVertex3f(-0.38, 0.73, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.66, 12.0);
          glVertex3f(-0.38, 0.66, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.59, 12.0);
          glVertex3f(-0.38, 0.59, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.52, 12.0);
          glVertex3f(-0.38, 0.52, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.45, 12.0);
          glVertex3f(-0.38, 0.45, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.38, 12.0);
          glVertex3f(-0.38, 0.38, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.31, 12.0);
          glVertex3f(-0.38,0.31 , 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.24, 12.0);
          glVertex3f(-0.38, 0.24, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.17, 12.0);
          glVertex3f(-0.38, 0.17, 12.0);

       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.10, 12.0);
          glVertex3f(-0.38, 0.10, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.03, 12.0);
          glVertex3f(-0.38, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(-0.38, 0.94, 12.0);
          glVertex3f(-0.38, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(-0.3, 0.94, 12.0);
          glVertex3f(-0.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(-0.2, 0.94, 12.0);
          glVertex3f(-0.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(-0.1, 0.94, 12.0);
          glVertex3f(-0.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(-0.0, 0.94, 12.0);
          glVertex3f(-0.0, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(0.1, 0.94, 12.0);
          glVertex3f(0.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(0.2, 0.94, 12.0);
          glVertex3f(0.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(0.3, 0.94, 12.0);
          glVertex3f(0.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(0.4, 0.94, 12.0);

          glVertex3f(0.4, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(0.5, 0.94, 12.0);
          glVertex3f(0.5, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(0.6, 0.94, 12.0);
          glVertex3f(0.6, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(0.7, 0.94, 12.0);
          glVertex3f(0.7, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(0.8, 0.94, 12.0);
          glVertex3f(0.8, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(0.9, 0.94, 12.0);
          glVertex3f(0.9, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(1.0, 0.94, 12.0);
          glVertex3f(1.0, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(1.1, 0.94, 12.0);
          glVertex3f(1.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(1.2, 0.94, 12.0);
          glVertex3f(1.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(1.3, 0.94, 12.0);
          glVertex3f(1.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(1.4, 0.94, 12.0);
          glVertex3f(1.4, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {

          glVertex3f(1.5, 0.94, 12.0);
          glVertex3f(1.5, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(1.6, 0.94, 12.0);
          glVertex3f(1.6, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(1.7, 0.94, 12.0);
          glVertex3f(1.7, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(1.8, 0.94, 12.0);
          glVertex3f(1.8, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(1.9, 0.94, 12.0);
          glVertex3f(1.9, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(2.0, 0.94, 12.0);
          glVertex3f(2.0, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(2.1, 0.94, 12.0);
          glVertex3f(2.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(2.2, 0.94, 12.0);
          glVertex3f(2.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(2.3, 0.94, 12.0);
          glVertex3f(2.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(2.4, 0.94, 12.0);
          glVertex3f(2.4, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(2.5, 0.94, 12.0);
          glVertex3f(2.5, 0.03, 12.0);
       }
       glEnd();

       glBegin(GL_LINES);
       {
          glVertex3f(2.6, 0.94, 12.0);
          glVertex3f(2.6, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(2.7, 0.94, 12.0);
          glVertex3f(2.7, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(2.8, 0.94, 12.0);
          glVertex3f(2.8, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(2.9, 0.94, 12.0);
          glVertex3f(2.9, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.0, 0.94, 12.0);
          glVertex3f(3.0, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.1, 0.94, 12.0);
          glVertex3f(3.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.2, 0.94, 12.0);
          glVertex3f(3.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.3, 0.94, 12.0);
          glVertex3f(3.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.4, 0.94, 12.0);
          glVertex3f(3.4, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.5, 0.94, 12.0);
          glVertex3f(3.5, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.6, 0.94, 12.0);
          glVertex3f(3.6, 0.03, 12.0);
       }

       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.7, 0.94, 12.0);
          glVertex3f(3.7, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.8, 0.94, 12.0);
          glVertex3f(3.8, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(3.9, 0.94, 12.0);
          glVertex3f(3.9, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.0, 0.94, 12.0);
          glVertex3f(4.0, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.1, 0.94, 12.0);
          glVertex3f(4.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.2, 0.94, 12.0);
          glVertex3f(4.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.3, 0.94, 12.0);
          glVertex3f(4.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.4, 0.94, 12.0);
          glVertex3f(4.4, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.5, 0.94, 12.0);
          glVertex3f(4.5, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.6, 0.94, 12.0);
          glVertex3f(4.6, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.7, 0.94, 12.0);

          glVertex3f(4.7, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.8, 0.94, 12.0);
          glVertex3f(4.8, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(4.9, 0.94, 12.0);
          glVertex3f(4.9, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(5.0, 0.94, 12.0);
          glVertex3f(5.0, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(5.1, 0.94, 12.0);
          glVertex3f(5.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(5.2, 0.94, 12.0);
          glVertex3f(5.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(5.3, 0.94, 12.0);
          glVertex3f(5.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(5.4, 0.94, 12.0);
          glVertex3f(5.4, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(5.5, 0.94, 12.0);
          glVertex3f(5.5, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(5.6, 0.94, 12.0);
          glVertex3f(5.6, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(5.7, 0.94, 12.0);
          glVertex3f(5.7, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);

       {
          glVertex3f(5.8, 0.94, 12.0);
          glVertex3f(5.8, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(5.9, 0.94, 12.0);
          glVertex3f(5.9, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(6.0, 0.94, 12.0);
          glVertex3f(6.0, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(6.1, 0.94, 12.0);
          glVertex3f(6.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(6.2, 0.94, 12.0);
          glVertex3f(6.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(6.3, 0.94, 12.0);
          glVertex3f(6.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(6.4, 0.94, 12.0);
          glVertex3f(6.4, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(6.5, 0.94, 12.0);
          glVertex3f(6.5, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(6.6, 0.94, 12.0);
          glVertex3f(6.6, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(6.7, 0.94, 12.0);
          glVertex3f(6.7, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(6.8, 0.94, 12.0);
          glVertex3f(6.8, 0.03, 12.0);
       }
       glEnd();

       glBegin(GL_LINES);
       {
          glVertex3f(6.9, 0.94, 12.0);
          glVertex3f(6.9, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.0, 0.94, 12.0);
          glVertex3f(7.0, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.1, 0.94, 12.0);
          glVertex3f(7.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.2, 0.94, 12.0);
          glVertex3f(7.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.3, 0.94, 12.0);
          glVertex3f(7.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.4, 0.94, 12.0);
          glVertex3f(7.4, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.5, 0.94, 12.0);
          glVertex3f(7.5, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.6, 0.94, 12.0);
          glVertex3f(7.6, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.7, 0.94, 12.0);
          glVertex3f(7.7, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.8, 0.94, 12.0);
          glVertex3f(7.8, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(7.9, 0.94, 12.0);
          glVertex3f(7.9, 0.03, 12.0);

       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.0, 0.94, 12.0);
          glVertex3f(8.0, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.1, 0.94, 12.0);
          glVertex3f(8.1, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.2, 0.94, 12.0);
          glVertex3f(8.2, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.3, 0.94, 12.0);
          glVertex3f(8.3, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.4, 0.94, 12.0);
          glVertex3f(8.4, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.5, 0.94, 12.0);
          glVertex3f(8.5, 0.03, 12.0);
       }
       glEnd();
       glBegin(GL_LINES);
       {
          glVertex3f(8.63, 0.94, 12.0);
          glVertex3f(8.63, 0.03, 12.0);
       }
       glEnd();
   }
   glEndList();
   return;
}


MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
//    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
//    m_xRot = 0;
//    m_yRot = 0;
//    m_zRot = 0;
}

void MyGLWidget::initializeGL()
{
//    SkyBlue
//    glClearColor(0.529, 0.808, 0.922, 1.0);
    glClearColor(0.0/255, 0.0/255, 204.0/255, 1.0);

    glEnable( GL_NORMALIZE );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );

    glClientActiveTexture( GL_TEXTURE0 );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    GLfloat ambient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat diffuse[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat specular[] = {0.5, 0.5, 0.5, 1.0};

    GLfloat position0[] = {-5.0, 10.0, -5.0, 0.0};
    GLfloat position1[] = {-5.0, 10.0, 23.77+5, 0.0};
    GLfloat position2[] = {12.974+5.0, 10.0, -5, 0.0};
    GLfloat position3[] = {12.974+5.0, 10.0, 23.77+5, 0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.);

    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightf (GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.);

    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT3, GL_POSITION, position3);
    glLightf (GL_LIGHT3, GL_LINEAR_ATTENUATION, 1.);

    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);

}

void MyGLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(positionX, positionY, positionZ, lookAtX, lookAtY, lookAtZ, viewUpX, viewUpY, viewUpZ);

    add_court_matrix();
    draw_court_lines();
    add_net_matrix();
    draw_net_lines();

//    // ----- Objects -----

    //ground
    GLfloat k_a_ground[] = { 101.0/255, 179.0/255, 253.0/255 };
    GLfloat k_d_ground[] = { 101.0/255, 179.0/255, 253.0/255 };
    GLfloat k_s_ground[] = { 101.0/255, 179.0/255, 253.0/255 };
    GLfloat m_ground     = 1.0;

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_ground);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_ground);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_ground);
    glMaterialf (GL_FRONT, GL_SHININESS, m_ground);

//    glTranslatef(-10.974*1.5, -23.77/2, -0.002);
    glTranslatef(10.974/2+1, -0.2, 23.77/2);
    glTranslatef(0, 0, 0);
    glScalef(4.5 * 10.974, 0.001, 2.5 * 23.77);

    glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
    glNormalPointer(GL_FLOAT, 0, cubeNormals);
    glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

    glPopMatrix();

//    court
    GLfloat k_a_court[] = { 69.0/255, 114.0/255, 172.0/255 };
    GLfloat k_d_court[] = { 69.0/255, 114.0/255, 172.0/255 };
    GLfloat k_s_court[] = { 69.0/255, 114.0/255, 172.0/255 };
    GLfloat m_court     = 1.0;

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_court);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_court);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_court);
    glMaterialf (GL_FRONT, GL_SHININESS, m_court);
    glTranslatef(12.3/2, -0.0001, 24.00/2);
    glTranslatef(0, 0, 0);
    glScalef(12.3, 0.001, 23.77);

    glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
    glNormalPointer(GL_FLOAT, 0, cubeNormals);
    glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

    glPopMatrix();

    GLfloat k_a_wood[] = { 130.0/255, 82.0/255, 1.0/255 };
    GLfloat k_d_wood[] = { 130.0/255, 82.0/255, 1.0/255 };
    GLfloat k_s_wood[] = { 130.0/255, 82.0/255, 1.0/255 };
    GLfloat m_wood     = 1.0;

    // Lamp 1
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_wood);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_wood);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_wood);
    glMaterialf (GL_FRONT, GL_SHININESS, m_wood);

    glTranslatef(-5.0, 0.0, -5.0);
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(10.0, 20.0, 10.0);

    // set input data to arrays
    glVertexPointer(3, GL_FLOAT, 0, LampVerts);
    glNormalPointer(GL_FLOAT, 0, LampNormals);

    // draw data
    glDrawArrays(GL_TRIANGLES, 0, LampNumVerts);

    glPopMatrix();

    // Lamp 2
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_wood);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_wood);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_wood);
    glMaterialf (GL_FRONT, GL_SHININESS, m_wood);

    glTranslatef(-5.0, 0.0, 23.77 + 5.0);
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(10.0, 20.0, 10.0);

    // set input data to arrays
    glVertexPointer(3, GL_FLOAT, 0, LampVerts);
    glNormalPointer(GL_FLOAT, 0, LampNormals);

    // draw data
    glDrawArrays(GL_TRIANGLES, 0, LampNumVerts);

    glPopMatrix();

    // Lamp 3
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_wood);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_wood);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_wood);
    glMaterialf (GL_FRONT, GL_SHININESS, m_wood);

    glTranslatef(12.974 + 5.0, 0.0, -5.0);
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(10.0, 20.0, 10.0);

    // set input data to arrays
    glVertexPointer(3, GL_FLOAT, 0, LampVerts);
    glNormalPointer(GL_FLOAT, 0, LampNormals);

    // draw data
    glDrawArrays(GL_TRIANGLES, 0, LampNumVerts);

    glPopMatrix();

    // Lamp 4
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_wood);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_wood);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_wood);
    glMaterialf (GL_FRONT, GL_SHININESS, m_wood);

    glTranslatef(12.974 + 5.0, 0.0, 23.77 + 5.0);
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(10.0, 20.0, 10.0);

    // set input data to arrays
    glVertexPointer(3, GL_FLOAT, 0, LampVerts);
    glNormalPointer(GL_FLOAT, 0, LampNormals);

    // draw data
    glDrawArrays(GL_TRIANGLES, 0, LampNumVerts);

    glPopMatrix();

    GLfloat k_a_sand[] = { 150.0/255, 113.0/255, 23.0/255 };
    GLfloat k_d_sand[] = { 150.0/255, 113.0/255, 23.0/255 };
    GLfloat k_s_sand[] = { 150.0/255, 113.0/255, 23.0/255 };
    double m_sand    = 1.0;

    for (int i = 0; i < 10; i++) {
            glPushMatrix();

            glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_sand);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_sand);
            glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_sand);
            glMaterialf (GL_FRONT, GL_SHININESS, m_sand);

            glTranslatef(-6.5 - i*0.5, i*0.8, 24.002/2);
            glTranslatef(0, 0, 0);
            glScalef(3.0 + (10-i) * 0.5, 0.8, 24.002);

            glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
            glNormalPointer(GL_FLOAT, 0, cubeNormals);
            glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

            glPopMatrix();
    }

    for (int i = 0; i < 10; i++) {
            glPushMatrix();

            glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_sand);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_sand);
            glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_sand);
            glMaterialf (GL_FRONT, GL_SHININESS, m_sand);

            glTranslatef(13+6.5 + i*0.5, i*0.8, 24.002/2);
            glTranslatef(0, 0, 0);
            glScalef(3.0 + (10-i) * 0.5, 0.8, 24.002);

            glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
            glNormalPointer(GL_FLOAT, 0, cubeNormals);
            glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

            glPopMatrix();
    }

    for (int i = 0; i < 10; i++) {
            glPushMatrix();

            glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_sand);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_sand);
            glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_sand);
            glMaterialf (GL_FRONT, GL_SHININESS, m_sand);

            glTranslatef(6.1, i*0.8,  24.002 + 6.0 + i*0.5);
            glTranslatef(0, 0, 0);
            glScalef(12.2, 0.8, 3.0 + (10-i) * 0.5);

            glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
            glNormalPointer(GL_FLOAT, 0, cubeNormals);
            glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

            glPopMatrix();
    }

    for (int i = 0; i < 10; i++) {
            glPushMatrix();

            glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_sand);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_sand);
            glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_sand);
            glMaterialf (GL_FRONT, GL_SHININESS, m_sand);

            glTranslatef(6.4, i*0.8, -6.5 - i*0.5);
            glTranslatef(0, 0, 0);
            glScalef(12.4, 0.8, 3.0 + (10-i) * 0.5);

            glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
            glNormalPointer(GL_FLOAT, 0, cubeNormals);
            glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

            glPopMatrix();
    }

}

void MyGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
//    gluPerspective( 45, width/height, 0.01, 1000 );

//        // Camera default position
//        this->positionX = 10.974/2;
//        this->positionY = 23.77/2;
//        this->positionZ = 40.0;

//        // Camera default lookAt
//        this->lookAtX = 10.974/2;
//        this->lookAtY = 23.77/2;
//        this->lookAtZ = 0.0;

//        // Camera default viewUp
//        this->viewUpX = 10.974/2 - this->positionX;
//        this->viewUpY = 20.0 - this->positionY;
//        this->viewUpZ = 0.0 - this->positionZ;


    //arquibancada
    // Camera default position
    this->positionX = 6.1;
    this->positionY = 0.5;
    this->positionZ = 12.0;

    // Camera default lookAt
    this->lookAtX = 6.1;
    this->lookAtY = 1.5;
    this->lookAtZ = 0.0;

    // Camera default viewUp
    this->viewUpX = 0;
    this->viewUpY = 1;
    this->viewUpZ = 0;

    // de lado
    // Camera default position
    this->positionX = -6.1;
    this->positionY = 6.5;
    this->positionZ = 25.0;

    // Camera default lookAt
    this->lookAtX = 12.1;
    this->lookAtY = 4.1;
    this->lookAtZ = 0.0;

    // Camera default viewUp
    this->viewUpX = 0;
    this->viewUpY = 1;
    this->viewUpZ = 0;

    // de frente pegando arquibancada
    // Camera default position
    this->positionX = 12.1;
    this->positionY = 6.5;
    this->positionZ = 25.0;

    // Camera default lookAt
    this->lookAtX = 12.1;
    this->lookAtY = 4.1;
    this->lookAtZ = 0.0;

    // Camera default viewUp
    this->viewUpX = 0;
    this->viewUpY = 1;
    this->viewUpZ = 0;

    // de frente na rede
    // Camera default position
    this->positionX = 6.1;
    this->positionY = 6.5;
    this->positionZ = 25.0;

    // Camera default lookAt
    this->lookAtX = 6.1;
    this->lookAtY = 4.1;
    this->lookAtZ = 0.0;

    // Camera default viewUp
    this->viewUpX = 0;
    this->viewUpY = 1;
    this->viewUpZ = 0;

    //ABOVE
    // Camera default position
    this->positionX = 6.1;
    this->positionY = 76.5;
    this->positionZ = 12.0;

    // Camera default lookAt
    this->lookAtX = 6.1;
    this->lookAtY = 0.0;
    this->lookAtZ = 12.0;

    // Camera default viewUp
    this->viewUpX = 0;
    this->viewUpY = 0;
    this->viewUpZ = 1;

//    gluPerspective(80.0, width/height, 0.01, 100.0); /*Perspective defined*/
    gluPerspective(45.0, width/height, 0.01, 100.0); /*Perspective defined*/
//    gluLookAt(positionX, positionY, positionZ, lookAtX, lookAtY, lookAtZ, viewUpX, viewUpY, viewUpZ); /*Camera position defined*/
//    gluLookAt(-1.0, 6.5, 43.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0); /*Camera position defined*/
//    gluLookAt(4.1, 6.5, 50.0, 4.1, 4.1, 0.0, 0.0, 1.0, 0.0); /*Camera position defined*/
//    gluLookAt(-1.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); /*Camera position defined*/
    updateGL();
}

//QSize MyGLWidget::minimumSizeHint() const
//{
//    return QSize(50, 50);
//}

//QSize MyGLWidget::sizeHint() const
//{
//    return QSize(500, 350);
//}

//void MyGLWidget::mousePressEvent(QMouseEvent *event)
//{
//    m_lastPos = event->pos();
//}

//void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
//{
//    int dx = event->x() - m_lastPos.x();
//    int dy = event->y() - m_lastPos.y();

//    if (event->buttons() & Qt::LeftButton) {
//        setXRotation(m_xRot + 8 * dy);
//        setYRotation(m_yRot + 8 * dx);
//    } else if (event->buttons() & Qt::RightButton) {
//        setXRotation(m_xRot + 8 * dy);
//        setZRotation(m_zRot + 8 * dx);
//    }

//    m_lastPos = event->pos();
//}

//static void qNormalizeAngle(int &angle)
//{
//    while (angle < 0)
//        angle += 360 * 16;
//    while (angle > 360)
//        angle -= 360 * 16;
//}

//void MyGLWidget::setXRotation(int angle)
//{
//    qNormalizeAngle(angle);
//    if (angle != m_xRot) {
//        m_xRot = angle;
//        emit xRotationChanged(angle);
//        updateGL();
//    }
//}

//void MyGLWidget::setYRotation(int angle)
//{
//    qNormalizeAngle(angle);
//    if (angle != m_yRot) {
//        m_yRot = angle;
//        emit yRotationChanged(angle);
//        updateGL();
//    }
//}

//void MyGLWidget::setZRotation(int angle)
//{
//    qNormalizeAngle(angle);
//    if (angle != m_zRot) {
//        m_zRot = angle;
//        emit zRotationChanged(angle);
//        updateGL();
//    }
//}


