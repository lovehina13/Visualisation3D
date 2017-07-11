//==============================================================================
// Name        : GLWidget.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
// Description : Source file of the GLWidget class
//==============================================================================

#include "GLWidget.h"
#include <cmath>

GLWidget::GLWidget(QWidget* parent) :
        QGLWidget(parent), xRotation(0), yRotation(0), zRotation(0), skyBox(new SkyBox())
{
}

GLWidget::~GLWidget()
{
    delete skyBox;
}

void GLWidget::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    skyBox->initialize();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRotation, 1.0, 0.0, 0.0);
    glRotatef(yRotation, 0.0, 1.0, 0.0);
    glRotatef(zRotation, 0.0, 0.0, 1.0);

    skyBox->paint();

    glLineWidth(2.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glEnd();

    glLineWidth(2.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glEnd();

    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, +10.0, -10.0, +10.0, -10.0 * sqrt(2.0) - 1.0, +10.0 * sqrt(2.0) + 1.0);
    glMatrixMode(GL_MODELVIEW);
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
        // setXRotation(xRotation - dy);
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
