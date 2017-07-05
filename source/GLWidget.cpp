//==============================================================================
// Name        : GLWidget.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
// Description : Source file of the GLWidget class
//==============================================================================

#include "GLWidget.h"

GLWidget::GLWidget(QWidget* parent) :
        QGLWidget(parent), xRotation(0), yRotation(0), zRotation(0)
{
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    // TODO void GLWidget::initializeGL()
}

void GLWidget::paintGL()
{
    // TODO void GLWidget::paintGL()
}

void GLWidget::resizeGL(int width, int height)
{
    // TODO void GLWidget::resizeGL(int width, int height)
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
    lastPosition = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastPosition.x();
    int dy = event->y() - lastPosition.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(xRotation - dy);
        setYRotation(yRotation - dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        setXRotation(xRotation - dy);
        setZRotation(zRotation - dx);
    }

    lastPosition = event->pos();
}

static void qNormalizeAngle(int& angle)
{
    while (angle < 0)
        angle += 360;
    while (angle > 360)
        angle -= 360;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRotation)
    {
        xRotation = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRotation)
    {
        yRotation = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRotation)
    {
        zRotation = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}
