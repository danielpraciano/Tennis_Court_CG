#include <QtWidgets>
#include <QtOpenGL>
#include <main/include/myglwidget.h>
#include <core/include/io_module.h>

#include <scenario/include/object/transformation.h>
#include <scenario/include/scenario.h>
#include <scenario/include/object/vertex.h>
#include <scenario/include/object/face.h>
#include <scenario/include/object/object.h>
#include <scenario/include/light/light.h>
#include <scenario/include/object/material.h>
#include <scenario/include/light/punctual_light.h>
#include <render/include/raycasting/camera.h>
#include <render/include/raycasting/color.h>
#include <render/include/raycasting/ray.h>
#include <render/include/raycasting/ray_casting.h>
#include <render/include/raycasting/projection_type.h>

#include <scenario/include/object/texture.h>

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    m_xRot = 0;
    m_yRot = 0;
    m_zRot = 0;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(500, 350);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{
    glClearColor(0.529, 0.808, 0.922, 1.0);

    glEnable( GL_DEPTH_TEST );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    GLfloat ambient[] = {0.4,0.4,0.4,1};
    GLfloat diffuse[] = {1,1,1,1};
    GLfloat specular[] = {1,1,1,1};
    GLfloat position[] = {100,0,0,1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawUnitCube() {
  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glVertex3f(0.0f,0.0f, 1.0f);
  glVertex3f( 1.0f,0.0f, 1.0f);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 1.0f,0.0f);
  glVertex3f( 1.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(0.0f, 1.0f,0.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glVertex3f( 1.0f,0.0f, 1.0f);
  glVertex3f( 1.0f,0.0f,0.0f);
  glVertex3f( 1.0f, 1.0f,0.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 1.0f,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 1.0f,0.0f);
  glVertex3f(0.0f, 1.0f,0.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f,0.0f);
  glVertex3f( 1.0f, 0.0f,0.0f);
  glEnd();
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 2,2,2, 1,1,1, 0,1,0 );

    render::raycasting::Color color_orange { 1.0, 140.0/255.0, 0.0 };

    std::shared_ptr<scenario::object::Material> material_orange {
    new scenario::object::Material { 100.0, color_orange, color_orange, color_orange } };

    core::io_module::ObjReader reader;
    auto obj = reader.read("/Users/leonardo/Developer/Tennis_Court_CG/Scenario_CG/cube2.obj", material_orange);

    for (const auto &face: obj->get_faces()) {
        GLfloat ambi[3] = {face.get_material().get_k_ambient().get_values()(0), face.get_material().get_k_ambient().get_values()(1), face.get_material().get_k_ambient().get_values()(2)};
        GLfloat diffuse[3] = {face.get_material().get_k_diffuse().get_values()(0), face.get_material().get_k_diffuse().get_values()(1), face.get_material().get_k_diffuse().get_values()(2)};
        GLfloat specular[3] = {face.get_material().get_k_specular().get_values()(0), face.get_material().get_k_specular().get_values()(1), face.get_material().get_k_specular().get_values()(2)};
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, face.get_material().get_reflexive_coef());

        glBegin(GL_POLYGON);
        for (const auto &vertex: obj->get_vertices()) {
            GLfloat normal[3] = {vertex->get_normal()(0), vertex->get_normal()(1), vertex->get_normal()(2)};
            GLfloat coord[3] = {vertex->get_coordinates()(0), vertex->get_coordinates()(1), vertex->get_coordinates()(2)};
            glNormal3fv(normal);
            glVertex3fv(coord);
        }
        glEnd();
    }




//    drawUnitCube();

//    glLoadIdentity();
//    glTranslatef(0, -0.5, -10.0);
//    glRotatef(m_xRot / 16.0, 1.0, 0.0, 0.0);
//    glRotatef(m_yRot / 16.0, 0.0, 1.0, 0.0);
//    glRotatef(m_zRot / 16.0, 0.0, 0.0, 1.0);
//    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, width/height, 0.01, 1000 );
    updateGL();
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }

    m_lastPos = event->pos();
}

void MyGLWidget::draw()
{
}
