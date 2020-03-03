//==============================================================================
// Name        : GLWidget.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/03/2020)
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

    double zoom = static_cast<double>(zoomScale) / 10.0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0 / zoom, +10.0 / zoom, -10.0 / zoom, +10.0 / zoom, -100.0, +100.0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslated(0.0, 0.0, -10.0);
    glRotated(static_cast<double>(xRotation), 1.0, 0.0, 0.0);
    glRotated(static_cast<double>(yRotation), 0.0, 1.0, 0.0);
    glRotated(static_cast<double>(zRotation), 0.0, 0.0, 1.0);

    skyBox->paint();

    glLineWidth(2.0);
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(10.0, 0.0, 0.0);
    glEnd();

    glLineWidth(2.0);
    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 10.0, 0.0);
    glEnd();

    glLineWidth(2.0);
    glColor3d(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 10.0);
    glEnd();

    if (picturesDepth == DEPTH_X)
    {
        glRotated(90.0, 0.0, 1.0, 0.0);
    }
    else if (picturesDepth == DEPTH_Y)
    {
        glRotated(270.0, 1.0, 0.0, 0.0);
    }
    else if (picturesDepth == DEPTH_X_INV)
    {
        glRotated(270.0, 0.0, 1.0, 0.0);
    }
    else if (picturesDepth == DEPTH_Y_INV)
    {
        glRotated(90.0, 1.0, 0.0, 0.0);
    }
    else if (picturesDepth == DEPTH_Z_INV)
    {
        glRotated(180.0, 0.0, 1.0, 0.0);
    }

    if (picturesRotation > 0)
    {
        glRotated(360.0 - static_cast<double>(picturesRotation), 0.0, 0.0, 1.0);
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
    double zoom = static_cast<double>(zoomScale) / 10.0;
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
        (*itPicture)->setDisplayWidth(static_cast<double>(size) / 10.0);
    }
    updateGL();
}

void GLWidget::setDisplayHeight(int size)
{
    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        (*itPicture)->setDisplayHeight(static_cast<double>(size) / 10.0);
    }
    updateGL();
}

void GLWidget::setDisplayDepth(int size)
{
    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        (*itPicture)->setDisplayDepth(static_cast<double>(size) / 10.0);
    }
    updateGL();
}

void GLWidget::setDisplaySpacing(int size)
{
    for (QList<Picture*>::const_iterator itPicture = pictures.begin(); itPicture != pictures.end();
            itPicture++)
    {
        (*itPicture)->setDisplaySpacing(static_cast<double>(size) / 100.0);
    }
    updateGL();
}
