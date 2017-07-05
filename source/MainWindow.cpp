//==============================================================================
// Name        : MainWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
// Description : Source file of the MainWindow class
//==============================================================================

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    // Sliders to spin boxes
    connect(this->ui->sliderRotationX, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationX,
            SLOT(setValue(int)));
    connect(this->ui->sliderRotationY, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationY,
            SLOT(setValue(int)));
    connect(this->ui->sliderRotationZ, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationZ,
            SLOT(setValue(int)));

    // Sliders to widget
    connect(this->ui->sliderRotationX, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setXRotation(int)));
    connect(this->ui->sliderRotationY, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setYRotation(int)));
    connect(this->ui->sliderRotationZ, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setZRotation(int)));

    // Spin boxes to sliders
    connect(this->ui->spinBoxRotationX, SIGNAL(valueChanged(int)), this->ui->sliderRotationX,
            SLOT(setValue(int)));
    connect(this->ui->spinBoxRotationY, SIGNAL(valueChanged(int)), this->ui->sliderRotationY,
            SLOT(setValue(int)));
    connect(this->ui->spinBoxRotationZ, SIGNAL(valueChanged(int)), this->ui->sliderRotationZ,
            SLOT(setValue(int)));

    // Spin boxes to widget
    connect(this->ui->spinBoxRotationX, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setXRotation(int)));
    connect(this->ui->spinBoxRotationY, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setYRotation(int)));
    connect(this->ui->spinBoxRotationZ, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setZRotation(int)));

    // Widget to sliders
    connect(this->ui->glWidget, SIGNAL(xRotationChanged(int)), this->ui->sliderRotationX,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(yRotationChanged(int)), this->ui->sliderRotationY,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(zRotationChanged(int)), this->ui->sliderRotationZ,
            SLOT(setValue(int)));

    // Widget to spin boxes
    connect(this->ui->glWidget, SIGNAL(xRotationChanged(int)), this->ui->spinBoxRotationX,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(yRotationChanged(int)), this->ui->spinBoxRotationY,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(zRotationChanged(int)), this->ui->spinBoxRotationZ,
            SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete this->ui;
}
