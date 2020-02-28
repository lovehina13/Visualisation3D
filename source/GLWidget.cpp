//==============================================================================
// Name        : GLWidget.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.2 (28/02/2020)
// Description : Source file of the GLWidget class
//==============================================================================

#include "GLWidget.h"
#include <QString>

GLWidget::GLWidget(QWidget* parent) :
        QGLWidget(parent), picturesDepth(DEPTH_Z), picturesRotation(0), xRotation(0), yRotation(0),
                zRotation(0), zoomScale(10), skyBox(new SkyBox())
{
}

GLWidget::~GLWidget()
{
    delete skyBox;

    removePictures();
}

void GLWidget::addPicture(Picture* picture)
{
    pictures.append(picture);
}

void GLWidget::removePictures()
{
    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        delete (*itPicture);
    }

    pictures.clear();
}

void GLWidget::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    skyBox->initialize();

    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        (*itPicture)->initialize(QString());
    }
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float zoom = (float) zoomScale / 10.0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0 / zoom, +10.0 / zoom, -10.0 / zoom, +10.0 / zoom, -100.0, +100.0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef((float) xRotation, 1.0, 0.0, 0.0);
    glRotatef((float) yRotation, 0.0, 1.0, 0.0);
    glRotatef((float) zRotation, 0.0, 0.0, 1.0);

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

    if (picturesDepth == DEPTH_X)
    {
        glRotatef(90.0, 0.0, 1.0, 0.0);
    }
    else if (picturesDepth == DEPTH_Y)
    {
        glRotatef(270.0, 1.0, 0.0, 0.0);
    }
    else if (picturesDepth == DEPTH_X_INV)
    {
        glRotatef(270.0, 0.0, 1.0, 0.0);
    }
    else if (picturesDepth == DEPTH_Y_INV)
    {
        glRotatef(90.0, 1.0, 0.0, 0.0);
    }
    else if (picturesDepth == DEPTH_Z_INV)
    {
        glRotatef(180.0, 0.0, 1.0, 0.0);
    }

    if (picturesRotation > 0)
    {
        glRotatef(360.0 - (float) picturesRotation, 0.0, 0.0, 1.0);
    }

    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        (*itPicture)->paint(pictures.indexOf(*itPicture), pictures.size());
    }
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    float zoom = (float) zoomScale / 10.0;
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0 / zoom, +10.0 / zoom, -10.0 / zoom, +10.0 / zoom, -100.0, +100.0);
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

void GLWidget::wheelEvent(QWheelEvent* event)
{
    if (event->delta() > 0)
    {
        setZoomScale(zoomScale + 1);
    }
    else if (event->delta() < 0)
    {
        setZoomScale(zoomScale - 1);
    }
}

static void qNormalizeAngle(int& angle)
{
    while (angle < 0)
        angle += 360;
    while (angle > 360)
        angle -= 360;
}

static void qNormalizeScale(int& scale)
{
    if (scale < 10)
        scale = 10;
    if (scale > 100)
        scale = 100;
}

void GLWidget::setPicturesDepth(int depth)
{
    if (depth != picturesDepth)
    {
        picturesDepth = depth;
        emit picturesDepthChanged(depth);
        updateGL();
    }
}

void GLWidget::setPicturesRotation(int rotation)
{
    if (rotation != picturesRotation)
    {
        picturesRotation = rotation;
        emit picturesRotationChanged(rotation);
        updateGL();
    }
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

void GLWidget::setZoomScale(int scale)
{
    qNormalizeScale(scale);
    if (scale != zoomScale)
    {
        zoomScale = scale;
        emit zoomScaleChanged(scale);
        updateGL();
    }
}

void GLWidget::setDisplayWidth(int size)
{
    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        (*itPicture)->setDisplayWidth((float) size / 10.0);
    }
    updateGL();
}

void GLWidget::setDisplayHeight(int size)
{
    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        (*itPicture)->setDisplayHeight((float) size / 10.0);
    }
    updateGL();
}

void GLWidget::setDisplayDepth(int size)
{
    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        (*itPicture)->setDisplayDepth((float) size / 10.0);
    }
    updateGL();
}

void GLWidget::setDisplaySpacing(int size)
{
    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        (*itPicture)->setDisplaySpacing((float) size / 100.0);
    }
    updateGL();
}
