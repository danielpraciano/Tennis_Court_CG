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
    // Color: SkyBlue
    glClearColor(0.529, 0.808, 0.922, 1.0);

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

    // White
    GLfloat ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {0.0, 500.0, 0.0, 0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.);

    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);

//    glEnable(GL_COLOR_MATERIAL);
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    // Camera default values
//    gluLookAt( 0.0,20.0,35.0, 0,0,0, 0,1,0 );

//    // Camera default position
//    this->positionX = 10.974/2;
//    this->positionY = -10.0;
//    this->positionZ = 1.0;

//    // Camera default lookAt
//    this->lookAtX = 10.974/2;
//    this->lookAtY = 23.77/2;
//    this->lookAtZ = 0.0;

//    // Camera default viewUp
//    this->viewUpX = 10.974/2 - this->positionX;
//    this->viewUpY = 23.77/2 - this->positionY;
//    this->viewUpZ = 3.0 - this->positionZ;

//    //Above
//    // Camera default position
//    this->positionX = 10.974/2;
//    this->positionY = 23.77/2;
//    this->positionZ = 55.0;

//    // Camera default lookAt
//    this->lookAtX = 10.974/2;
//    this->lookAtY = 23.77/2;
//    this->lookAtZ = 0.0;

//    // Camera default viewUp
//    this->viewUpX = 10.974/2 - this->positionX;
//    this->viewUpY = 20.0 - this->positionY;
//    this->viewUpZ = 0.0 - this->positionZ;

    // Camera default position
    this->positionX = 0.0;
    this->positionY = 0.0; //20
    this->positionZ = 50.0; //35

    // Camera default lookAt
    this->lookAtX = 0.0;
    this->lookAtY = 0.0;
    this->lookAtZ = 0.0;

    // Camera default viewUp
    this->viewUpX = 0.0;
    this->viewUpY = 1.0;
    this->viewUpZ = 0.0;
}

void add_cube(GLfloat *k_amb, GLfloat *k_dif, GLfloat *k_spec, GLfloat m,
              double factor_x, double factor_y, double factor_z, GLfloat final_pos_x, GLfloat final_pos_y, GLfloat final_pos_z) {
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_spec);
    glMaterialf (GL_FRONT, GL_SHININESS, m);
    glTranslatef(final_pos_x, final_pos_y, final_pos_z);
    glTranslatef(0, 0, 0);
    glScalef(factor_x, factor_y, factor_z);

    glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
    glNormalPointer(GL_FLOAT, 0, cubeNormals);
    glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

    glPopMatrix();
}

void MyGLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( this->positionX,this->positionY,this->positionZ, this->lookAtX,this->lookAtY,this->lookAtZ, this->viewUpX,this->viewUpY,this->viewUpZ );

    // ----- Objects -----

    //ground
    GLfloat k_a_ground[] = {1.0, 0.0, 0.0};
    GLfloat k_d_ground[] = {1.0, 0.0, 0.0};
    GLfloat k_s_ground[] = {1.0, 0.0, 0.0};
    GLfloat m_ground     = 10.0;

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_ground);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_ground);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_ground);
    glMaterialf (GL_FRONT, GL_SHININESS, m_ground);
//    glTranslatef(-10.974*1.5, -23.77/2, -0.002);
    glTranslatef(0, 0, -0.002);
    glTranslatef(0, 0, 0);
    glScalef(4 * 10.974, 2 * 23.77, 0.001);

    glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
    glNormalPointer(GL_FLOAT, 0, cubeNormals);
    glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

    glPopMatrix();

    //court
    GLfloat k_a_court[] = {0.0, 1.0, 0.0};
    GLfloat k_d_court[] = {0.0, 1.0, 0.0};
    GLfloat k_s_court[] = {0.0, 1.0, 0.0};
    GLfloat m_court     = 10.0;

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_court);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_court);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_court);
    glMaterialf (GL_FRONT, GL_SHININESS, m_court);
    glTranslatef(0.0, 0.0, -0.001);
    glTranslatef(0, 0, 0);
    glScalef(10.974, 23.77, 0.001);

    glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
    glNormalPointer(GL_FLOAT, 0, cubeNormals);
    glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

    glPopMatrix();

    //left_doubles_sideline
    GLfloat k_a_line[] = {1.0, 1.0, 1.0};
    GLfloat k_d_line[] = {1.0, 1.0, 1.0};
    GLfloat k_s_line[] = {1.0, 1.0, 1.0};
    GLfloat m_line     = 10.0;

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, k_a_line);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, k_d_line);
    glMaterialfv(GL_FRONT, GL_SPECULAR, k_s_line);
    glMaterialf (GL_FRONT, GL_SHININESS, m_line);
//    glTranslatef(0.0, 0.0, -0.001);
    glTranslatef(0, 0, 0);
    //7.62/100
    glScalef(7.62/100, 23.77, 0.001);

    glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
    glNormalPointer(GL_FLOAT, 0, cubeNormals);
    glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

    glPopMatrix();


//    GLfloat k_a[]  = {0.0, 1.0, 0.0};
//    GLfloat k_d[]  = {0.0, 1.0, 0.0};
//    GLfloat k_s[] = {0.0, 1.0, 0.0};

//    add_cube(k_a, k_d, k_s, m, 10.974, 23.77, 0.01, 0, 23.77, 0);

//    // Terrain
//    glPushMatrix();

//    // Color: LawnGreen
////    glColor3f(0.486, 0.988, 0.000);

//    glMaterialfv(GL_FRONT, GL_AMBIENT, new GLfloat[3] { 1.0, 0.0, 0.0 });
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, new GLfloat[3] { 1.0, 0.0, 0.0 });
//    glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[3] { 1.0, 0.0, 0.0 });
//    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

//    glTranslatef(0.0, 23.77, 0.0);
//    glScalef(10.974, 23.77, 0.01);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
//    glNormalPointer(GL_FLOAT, 0, cubeNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, cubeNumVerts);

//    glPopMatrix();

    // ------------------------------------------------------------

//    // Fence 1 - North
//    glPushMatrix();

//    glMaterialfv(GL_FRONT, GL_AMBIENT, new GLfloat[3] { 0.0, 1.0, 0.0 });
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, new GLfloat[3] { 0.0, 1.0, 0.0 });
//    glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[3] { 0.0, 1.0, 0.0 });
//    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

//    // Color: BurlyWood
////    glColor3f(0.871, 0.722, 0.529);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(10.0, 5.0, 5.0);
//    glTranslatef(-1.0, 0.25, -3.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, FenceVerts);
//    glNormalPointer(GL_FLOAT, 0, FenceNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, FenceTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, FenceNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Fence 2 - South
//    glPushMatrix();

//    // Color: BurlyWood
//    glColor3f(0.871, 0.722, 0.529);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(10.0, 5.0, 5.0);
//    glTranslatef(-1.0, 0.25, -1.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, FenceVerts);
//    glNormalPointer(GL_FLOAT, 0, FenceNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, FenceTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, FenceNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Fence 3 - East
//    glPushMatrix();

//    // Color: BurlyWood
//    glColor3f(0.871, 0.722, 0.529);
//    glTranslatef(0.0, 0.0, 0.0);
//    glRotatef(90.0, 0.0, 1.0, 0.0);
//    glScalef(10.0, 5.0, 5.0);
//    glTranslatef(1.0, 0.25, -1.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, FenceVerts);
//    glNormalPointer(GL_FLOAT, 0, FenceNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, FenceTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, FenceNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Fence 4 - West
//    glPushMatrix();

//    // Color: BurlyWood
//    glColor3f(0.871, 0.722, 0.529);
//    glTranslatef(0.0, 0.0, 0.0);
//    glRotatef(90.0, 0.0, 1.0, 0.0);
//    glScalef(10.0, 5.0, 5.0);
//    glTranslatef(1.0, 0.25, -3.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, FenceVerts);
//    glNormalPointer(GL_FLOAT, 0, FenceNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, FenceTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, FenceNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Cow 1 - Big
//    glPushMatrix();

//    // Color: White
//    glColor3f(1.0, 1.0, 1.0);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(4.0, 4.0, 4.0);
//    glTranslatef(-3.25, 0.5, -3.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, CowVerts);
//    glTexCoordPointer(2, GL_FLOAT, 0, CowTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, CowNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Cow 2 - Big
//    glPushMatrix();

//    // Color: Black
//    glColor3f(0.0, 0.0, 0.0);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(4.0, 4.0, 4.0);
//    glTranslatef(-2.75, 0.5, -2.5);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, CowVerts);
//    glTexCoordPointer(2, GL_FLOAT, 0, CowTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, CowNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Cow 3 - Small
//    glPushMatrix();

//    // Color: Maroon
//    glColor3f(0.502, 0.502, 0.502);
//    glTranslatef(0.0, 0.0, 0.0);
//    glRotatef(45.0, 0.0, 1.0, 0.0);
//    glScalef(2.5, 2.5, 2.5);
//    glTranslatef(0.5, 0.5, -5.5);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, CowVerts);
//    glTexCoordPointer(2, GL_FLOAT, 0, CowTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, CowNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Cow 4 - Small
//    glPushMatrix();

//    // Maroon
//    glColor3f(0.502, 0.502, 0.502);
//    glTranslatef(0.0, 0.0, 0.0);
//    glRotatef(-45.0, 0.0, 1.0, 0.0);
//    glScalef(2.5, 2.5, 2.5);
//    glTranslatef(-4.0, 0.5, -0.25);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, CowVerts);
//    glTexCoordPointer(2, GL_FLOAT, 0, CowTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, CowNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Hay 1 - Big block - Level 0 - Northwest
//    glPushMatrix();

//    // Color: Khaki
//    glColor3f(0.941, 0.902, 0.549);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(1.5, 1.5, 1.5);
//    glTranslatef(-9.0, 0.75, -2.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, HayVerts);
//    glNormalPointer(GL_FLOAT, 0, HayNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, HayNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Hay 2 - Big block - Level 0 - SouthWest
//    glPushMatrix();

//    // Color: Khaki
//    glColor3f(0.941, 0.902, 0.549);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(1.5, 1.5, 1.5);
//    glTranslatef(-9.0, 0.75, -0.75);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, HayVerts);
//    glNormalPointer(GL_FLOAT, 0, HayNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, HayNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Hay 3 - Big block - Level 0 - East
//    glPushMatrix();

//    // Color: Khaki
//    glColor3f(0.941, 0.902, 0.549);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(1.5, 1.5, 1.5);
//    glTranslatef(-8.0, 0.75, -1.25);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, HayVerts);
//    glNormalPointer(GL_FLOAT, 0, HayNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, HayNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Hay 4 - Big block - Level +1 - Center
//    glPushMatrix();

//    // Color: Khaki
//    glColor3f(0.941, 0.902, 0.549);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(1.5, 1.5, 1.5);
//    glTranslatef(-8.5, 1.75, -1.25);
//    glRotatef(-30.0, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, HayVerts);
//    glNormalPointer(GL_FLOAT, 0, HayNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, HayNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Hay 5 - Small block - Level 0 - Center
//    glPushMatrix();

//    // Color: Khaki
//    glColor3f(0.941, 0.902, 0.549);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(1.5, 1.5, 1.5);
//    glTranslatef(-6.0, 0.75, -1.25);
//    glRotatef(30.0, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, HayVerts);
//    glNormalPointer(GL_FLOAT, 0, HayNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, HayNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Tree 1 - North
//    glPushMatrix();

//    // Color: ForestGreen
//    glColor3f(0.133, 0.545, 0.133);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(8, 8, 8);
//    glTranslatef(-0.5, 0.5625, -1.5);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, TreeVerts);
//    glNormalPointer(GL_FLOAT, 0, TreeNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, TreeTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, TreeNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Tree 2 - West
//    glPushMatrix();

//    // Color: ForestGreen
//    glColor3f(0.133, 0.545, 0.133);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(6, 6, 6);
//    glTranslatef(-1.0, 0.625, -0.375);
//    glRotatef(-45.0, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, TreeVerts);
//    glNormalPointer(GL_FLOAT, 0, TreeNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, TreeTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, TreeNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Tree 3 - East
//    glPushMatrix();

//    // Color: ForestGreen
//    glColor3f(0.133, 0.545, 0.133);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(7, 7, 7);
//    glTranslatef(0.25, 0.625, -0.75);
//    glRotatef(135.0, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, TreeVerts);
//    glNormalPointer(GL_FLOAT, 0, TreeNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, TreeTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, TreeNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Mill
//    glPushMatrix();

//    // Color: Sienna
//    glColor3f(0.627, 0.322, 0.176);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(12.5, 12.5, 12.5);
//    glTranslatef(0.625, 0.375, -0.5);
//    glRotatef(22.5, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, MillVerts);
//    glNormalPointer(GL_FLOAT, 0, MillNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, MillTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, MillNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Barn
//    glPushMatrix();

//    // Color: FireBrick
//    glColor3f(0.698, 0.133, 0.133);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(9.0, 9.0, 9.0);
//    glTranslatef(0.75, 0.5, 0.625);
//    glRotatef(-125.0, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, BarnVerts);
//    glNormalPointer(GL_FLOAT, 0, BarnNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, BarnTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, BarnNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Silo
//    glPushMatrix();

//    // Color: Silver
//    glColor3f(0.753, 0.753, 0.753);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(9.0, 9.0, 9.0);
//    glTranslatef(0.5, 0.75, 1.25);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, SiloVerts);
//    glNormalPointer(GL_FLOAT, 0, SiloNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, SiloTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, SiloNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Lamp 1 - North
//    glPushMatrix();

//    // Color: Black
//    glColor3f(0.000, 0.000, 0.000);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(8.0, 6.0, 8.0);
//    glTranslatef(-0.375, 0.625, -0.75);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, LampVerts);
//    glNormalPointer(GL_FLOAT, 0, LampNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, LampNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Lamp 2 - Northeast
//    glPushMatrix();

//    // Color: Black
//    glColor3f(0.000, 0.000, 0.000);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(8.0, 6.0, 8.0);
//    glTranslatef(0.5, 0.625, -1.375);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, LampVerts);
//    glNormalPointer(GL_FLOAT, 0, LampNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, LampNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Lamp 3 - East
//    glPushMatrix();

//    // Color: Black
//    glColor3f(0.000, 0.000, 0.000);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(8.0, 6.0, 8.0);
//    glTranslatef(0.875, 0.625, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, LampVerts);
//    glNormalPointer(GL_FLOAT, 0, LampNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, LampNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Lamp 4 - Southeast
//    glPushMatrix();

//    // Color: Black
//    glColor3f(0.000, 0.000, 0.000);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(8.0, 6.0, 8.0);
//    glTranslatef(0.125, 0.625, 1.125);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, LampVerts);
//    glNormalPointer(GL_FLOAT, 0, LampNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, LampNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Lamp 5 - West
//    glPushMatrix();

//    // Color: Black
//    glColor3f(0.000, 0.000, 0.000);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(8.0, 6.0, 8.0);
//    glTranslatef(-1.75, 0.625, 0.25);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, LampVerts);
//    glNormalPointer(GL_FLOAT, 0, LampNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, LampNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Farmer
//    glPushMatrix();

//    // Color: Blue
//    glColor3f(0.000, 0.0, 1.000);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(4.0, 3.75, 4.0);
//    glTranslatef(-2.25, 0.75, 1.5);
//    glRotatef(115.0, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, FarmerVerts);
//    glTexCoordPointer(2, GL_FLOAT, 0, FarmerTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, FarmerNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Dog 1 - Away from farmer
//    glPushMatrix();

//    // Color: SandyBrown
//    glColor3f(0.957, 0.643, 0.376);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(4.0, 3.5, 4.0);
//    glTranslatef(-0.375, 0.5, 1.0);
//    glRotatef(135.0, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, DogVerts);
//    glNormalPointer(GL_FLOAT, 0, DogNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, DogTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, DogNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Dog 2 - Near the farmer
//    glPushMatrix();

//    // Color: SandyBrown
//    glColor3f(0.957, 0.643, 0.376);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(3.0, 3.0, 3.0);
//    glTranslatef(-2.75, 0.5, 2.75);
//    glRotatef(100.0, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, DogVerts);
//    glNormalPointer(GL_FLOAT, 0, DogNormals);
//    glTexCoordPointer(2, GL_FLOAT, 0, DogTexCoords);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, DogNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Cloud 1 - Northwest
//    glPushMatrix();

//    // Color: White
//    glColor3f(1.000, 1.000, 1.000);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(8.0, 8.0, 8.0);
//    glTranslatef(-0.625, 2.75, -0.75);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, CloudVerts);
//    glNormalPointer(GL_FLOAT, 0, CloudNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, CloudNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Cloud 2 - Northeast
//    glPushMatrix();

//    // Color: White
//    glColor3f(1.000, 1.000, 1.000);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(5.0, 5.0, 5.0);
//    glTranslatef(1.25, 4.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, CloudVerts);
//    glNormalPointer(GL_FLOAT, 0, CloudNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, CloudNumVerts);

//    glPopMatrix();

//    // ------------------------------------------------------------

//    // Cloud 3 - Southwest
//    glPushMatrix();

//    // Color: White
//    glColor3f(1.000, 1.000, 1.000);
//    glTranslatef(0.0, 0.0, 0.0);
//    glScalef(9.0, 4.0, 4.0);
//    glTranslatef(-0.625, 5.5, 2.0);
//    glRotatef(180.0, 0.0, 1.0, 0.0);

//    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, CloudVerts);
//    glNormalPointer(GL_FLOAT, 0, CloudNormals);

//    // draw data
//    glDrawArrays(GL_TRIANGLES, 0, CloudNumVerts);

//    glPopMatrix();

    // ------------------------------------------------------------
}

void MyGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, width/height, 0.01, 1000 );
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
