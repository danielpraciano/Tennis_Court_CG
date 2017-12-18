#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

#include <GL/glu.h>

#include <iostream>

using namespace std;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);

    double positionX;
    double positionY;
    double positionZ;

    double lookAtX;
    double lookAtY;
    double lookAtZ;

    double viewUpX;
    double viewUpY;
    double viewUpZ;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

//    QSize minimumSizeHint() const;
//    QSize sizeHint() const;
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);

signals:
//    // signaling rotation from mouse movement
//    void xRotationChanged(int angle);
//    void yRotationChanged(int angle);
//    void zRotationChanged(int angle);

public slots:
//    // slots for xyz-rotation slider
//    void setXRotation(int angle);
//    void setYRotation(int angle);
//    void setZRotation(int angle);

private:
//    int m_xRot;
//    int m_yRot;
//    int m_zRot;

//    QPoint m_lastPos;

};

#endif // MYGLWIDGET_H
