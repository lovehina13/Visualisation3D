//==============================================================================
// Name        : GLWidget.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.3.0 (09/08/2021)
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
    explicit GLWidget(QWidget* parent = nullptr);
    virtual ~GLWidget() override;

    void addPicture(Picture* picture);
    void removePictures();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

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
    enum PicturesDepth
    {
        DEPTH_X, DEPTH_Y, DEPTH_Z, DEPTH_X_INV, DEPTH_Y_INV, DEPTH_Z_INV
    };

    PicturesDepth _picturesDepth { DEPTH_Z };
    int _picturesRotation { 0 };
    int _xRotation { 0 };
    int _yRotation { 0 };
    int _zRotation { 0 };
    int _zoomScale { 0 };
    QPoint _lastPosition;
    SkyBox* _skyBox { nullptr };
    QList<Picture*> _pictures;
};

#endif /* GLWIDGET_H */
