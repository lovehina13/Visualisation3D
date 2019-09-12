//==============================================================================
// Name        : GLWidget.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.1 (05/04/2019)
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
    void setPicturesDepth(int depth);
    void setPicturesRotation(int rotation);
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setZoomScale(int scale);
    void setDisplayWidth(int size);
    void setDisplayHeight(int size);
    void setDisplayDepth(int size);
    void setDisplaySpacing(int size);

signals:
    void picturesDepthChanged(int depth);
    void picturesRotationChanged(int rotation);
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void zoomScaleChanged(int scale);

private:
    int picturesDepth;
    int picturesRotation;
    int xRotation;
    int yRotation;
    int zRotation;
    int zoomScale;
    QPoint lastPosition;
    SkyBox* skyBox;
    QList<Picture*> pictures;

    enum picturesDepths
    {
        DEPTH_X, DEPTH_Y, DEPTH_Z, DEPTH_X_INV, DEPTH_Y_INV, DEPTH_Z_INV
    };
};

#endif /* GLWIDGET_H */
