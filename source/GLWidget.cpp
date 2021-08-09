//==============================================================================
// Name        : GLWidget.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/03/2020)
// Description : Source file of the GLWidget class
//==============================================================================

#include "GLWidget.h"
#include <QString>

GLWidget::GLWidget(QWidget* parent) :
        QGLWidget(parent), _skyBox(new SkyBox())
{
}

GLWidget::~GLWidget()
{
    delete _skyBox;

    removePictures();
}

void GLWidget::addPicture(Picture* picture)
{
    _pictures.append(picture);
}

void GLWidget::removePictures()
{
    for (QList<Picture*>::const_iterator itPicture = _pictures.begin();
            itPicture != _pictures.end(); itPicture++)
    {
        delete (*itPicture);
    }

    _pictures.clear();
}

void GLWidget::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    _skyBox->initialize();

    for (QList<Picture*>::const_iterator itPicture = _pictures.begin();
            itPicture != _pictures.end(); itPicture++)
    {
        (*itPicture)->initialize(QString());
    }
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double zoom = static_cast<double>(_zoomScale) / 10.0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0 / zoom, +10.0 / zoom, -10.0 / zoom, +10.0 / zoom, -100.0, +100.0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslated(0.0, 0.0, -10.0);
    glRotated(static_cast<double>(_xRotation), 1.0, 0.0, 0.0);
    glRotated(static_cast<double>(_yRotation), 0.0, 1.0, 0.0);
    glRotated(static_cast<double>(_zRotation), 0.0, 0.0, 1.0);

    _skyBox->paint();

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

    if (_picturesDepth == DEPTH_X)
    {
        glRotated(90.0, 0.0, 1.0, 0.0);
    }
    else if (_picturesDepth == DEPTH_Y)
    {
        glRotated(270.0, 1.0, 0.0, 0.0);
    }
    else if (_picturesDepth == DEPTH_X_INV)
    {
        glRotated(270.0, 0.0, 1.0, 0.0);
    }
    else if (_picturesDepth == DEPTH_Y_INV)
    {
        glRotated(90.0, 1.0, 0.0, 0.0);
    }
    else if (_picturesDepth == DEPTH_Z_INV)
    {
        glRotated(180.0, 0.0, 1.0, 0.0);
    }

    if (_picturesRotation > 0)
    {
        glRotated(360.0 - static_cast<double>(_picturesRotation), 0.0, 0.0, 1.0);
    }

    for (QList<Picture*>::const_iterator itPicture = _pictures.begin();
            itPicture != _pictures.end(); itPicture++)
    {
        (*itPicture)->paint(_pictures.indexOf(*itPicture), _pictures.size());
    }
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    double zoom = static_cast<double>(_zoomScale) / 10.0;
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0 / zoom, +10.0 / zoom, -10.0 / zoom, +10.0 / zoom, -100.0, +100.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
    _lastPosition = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - _lastPosition.x();
    int dy = event->y() - _lastPosition.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(_xRotation - dy);
        setYRotation(_yRotation - dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        // setXRotation(xRotation - dy);
        setZRotation(_zRotation - dx);
    }

    _lastPosition = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0)
    {
        setZoomScale(_zoomScale + 1);
    }
    else if (event->angleDelta().y() < 0)
    {
        setZoomScale(_zoomScale - 1);
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
    if (static_cast<PicturesDepth>(depth) != _picturesDepth)
    {
        _picturesDepth = static_cast<PicturesDepth>(depth);
        emit picturesDepthChanged(depth);
        updateGL();
    }
}

void GLWidget::setPicturesRotation(int rotation)
{
    if (rotation != _picturesRotation)
    {
        _picturesRotation = rotation;
        emit picturesRotationChanged(rotation);
        updateGL();
    }
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _xRotation)
    {
        _xRotation = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _yRotation)
    {
        _yRotation = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _zRotation)
    {
        _zRotation = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZoomScale(int scale)
{
    qNormalizeScale(scale);
    if (scale != _zoomScale)
    {
        _zoomScale = scale;
        emit zoomScaleChanged(scale);
        updateGL();
    }
}

void GLWidget::setDisplayWidth(int size)
{
    for (QList<Picture*>::const_iterator itPicture = _pictures.begin();
            itPicture != _pictures.end(); itPicture++)
    {
        (*itPicture)->setDisplayWidth(static_cast<double>(size) / 10.0);
    }
    updateGL();
}

void GLWidget::setDisplayHeight(int size)
{
    for (QList<Picture*>::const_iterator itPicture = _pictures.begin();
            itPicture != _pictures.end(); itPicture++)
    {
        (*itPicture)->setDisplayHeight(static_cast<double>(size) / 10.0);
    }
    updateGL();
}

void GLWidget::setDisplayDepth(int size)
{
    for (QList<Picture*>::const_iterator itPicture = _pictures.begin();
            itPicture != _pictures.end(); itPicture++)
    {
        (*itPicture)->setDisplayDepth(static_cast<double>(size) / 10.0);
    }
    updateGL();
}

void GLWidget::setDisplaySpacing(int size)
{
    for (QList<Picture*>::const_iterator itPicture = _pictures.begin();
            itPicture != _pictures.end(); itPicture++)
    {
        (*itPicture)->setDisplaySpacing(static_cast<double>(size) / 100.0);
    }
    updateGL();
}
