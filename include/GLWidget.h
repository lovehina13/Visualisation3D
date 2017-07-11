//==============================================================================
// Name        : GLWidget.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
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

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    int xRotation;
    int yRotation;
    int zRotation;
    QPoint lastPosition;
    SkyBox* skyBox;
    QList<Picture*> pictures;
};

#endif /* GLWIDGET_H */
