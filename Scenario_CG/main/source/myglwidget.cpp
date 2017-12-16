#include <QtWidgets>
#include <QtOpenGL>
#include <main/include/myglwidget.h>

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

    drawUnitCube();

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
