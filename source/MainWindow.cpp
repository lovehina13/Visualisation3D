//==============================================================================
// Name        : MainWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
// Description : Source file of the MainWindow class
//==============================================================================

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Picture.h"
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    connect(this->ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));

    // Sliders to spin boxes
    connect(this->ui->sliderRotationX, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationX,
            SLOT(setValue(int)));
    connect(this->ui->sliderRotationY, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationY,
            SLOT(setValue(int)));
    connect(this->ui->sliderRotationZ, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationZ,
            SLOT(setValue(int)));

    // Sliders to widget
    connect(this->ui->sliderRotationX, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setYRotation(int)));
    connect(this->ui->sliderRotationY, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setXRotation(int)));
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
            SLOT(setYRotation(int)));
    connect(this->ui->spinBoxRotationY, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setXRotation(int)));
    connect(this->ui->spinBoxRotationZ, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setZRotation(int)));

    // Widget to sliders
    connect(this->ui->glWidget, SIGNAL(xRotationChanged(int)), this->ui->sliderRotationY,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(yRotationChanged(int)), this->ui->sliderRotationX,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(zRotationChanged(int)), this->ui->sliderRotationZ,
            SLOT(setValue(int)));

    // Widget to spin boxes
    connect(this->ui->glWidget, SIGNAL(xRotationChanged(int)), this->ui->spinBoxRotationY,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(yRotationChanged(int)), this->ui->spinBoxRotationX,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(zRotationChanged(int)), this->ui->spinBoxRotationZ,
            SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

void MainWindow::on_actionCharger_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            QString::fromUtf8("Sélection d'un fichier image"), 0,
            QString::fromUtf8("Fichier image (*.bmp *.jpg *.jpeg *.png)"));
    if (fileName.isEmpty())
        return;

    Picture* picture = new Picture();
    picture->initialize(fileName);

    this->ui->glWidget->removePictures();
    this->ui->glWidget->addPicture(picture);
    this->ui->glWidget->updateGL();
}
