//==============================================================================
// Name        : GLWidget.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.2 (28/05/2018)
// Description : Header file of the GLWidget class
//==============================================================================

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "Picture.h"
#include "SkyBox.h"
#include <QGLWidget>
#include <QList>
#include <QMouseEvent>
#include <QPoint>
#include <QWheelEvent>
#include <QWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget* parent = 0);
    virtual ~GLWidget();

    void addPicture(Picture* picture);
    void removePictures();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setZoomScale(int scale);
    void setDisplayWidth(int size);
    void setDisplayHeight(int size);
    void setDisplayDepth(int size);
    void setDisplaySpacing(int size);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void zoomScaleChanged(int scale);

private:
    int xRotation;
    int yRotation;
    int zRotation;
    int zoomScale;
    QPoint lastPosition;
    SkyBox* skyBox;
    QList<Picture*> pictures;
};

#endif /* GLWIDGET_H */
