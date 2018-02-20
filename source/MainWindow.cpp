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

    // Sliders to spin boxes (rotations)
    connect(this->ui->sliderRotationX, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationX,
            SLOT(setValue(int)));
    connect(this->ui->sliderRotationY, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationY,
            SLOT(setValue(int)));
    connect(this->ui->sliderRotationZ, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationZ,
            SLOT(setValue(int)));

    // Sliders to widget (rotations)
    connect(this->ui->sliderRotationX, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setYRotation(int)));
    connect(this->ui->sliderRotationY, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setXRotation(int)));
    connect(this->ui->sliderRotationZ, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setZRotation(int)));

    // Spin boxes to sliders (rotations)
    connect(this->ui->spinBoxRotationX, SIGNAL(valueChanged(int)), this->ui->sliderRotationX,
            SLOT(setValue(int)));
    connect(this->ui->spinBoxRotationY, SIGNAL(valueChanged(int)), this->ui->sliderRotationY,
            SLOT(setValue(int)));
    connect(this->ui->spinBoxRotationZ, SIGNAL(valueChanged(int)), this->ui->sliderRotationZ,
            SLOT(setValue(int)));

    // Spin boxes to widget (rotations)
    connect(this->ui->spinBoxRotationX, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setYRotation(int)));
    connect(this->ui->spinBoxRotationY, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setXRotation(int)));
    connect(this->ui->spinBoxRotationZ, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setZRotation(int)));

    // Widget to sliders (rotations)
    connect(this->ui->glWidget, SIGNAL(xRotationChanged(int)), this->ui->sliderRotationY,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(yRotationChanged(int)), this->ui->sliderRotationX,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(zRotationChanged(int)), this->ui->sliderRotationZ,
            SLOT(setValue(int)));

    // Widget to spin boxes (rotations)
    connect(this->ui->glWidget, SIGNAL(xRotationChanged(int)), this->ui->spinBoxRotationY,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(yRotationChanged(int)), this->ui->spinBoxRotationX,
            SLOT(setValue(int)));
    connect(this->ui->glWidget, SIGNAL(zRotationChanged(int)), this->ui->spinBoxRotationZ,
            SLOT(setValue(int)));

    // Sliders to spin boxes (scales)
    connect(this->ui->sliderZoom, SIGNAL(valueChanged(int)), this->ui->spinBoxZoom,
            SLOT(setValue(int)));

    // Sliders to widget (scales)
    connect(this->ui->sliderZoom, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setZoomScale(int)));

    // Spin boxes to sliders (scales)
    connect(this->ui->spinBoxZoom, SIGNAL(valueChanged(int)), this->ui->sliderZoom,
            SLOT(setValue(int)));

    // Spin boxes to widget (scales)
    connect(this->ui->spinBoxZoom, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setZoomScale(int)));

    // Widget to sliders (scales)
    connect(this->ui->glWidget, SIGNAL(zoomScaleChanged(int)), this->ui->sliderZoom,
            SLOT(setValue(int)));

    // Widget to spin boxes (scales)
    connect(this->ui->glWidget, SIGNAL(zoomScaleChanged(int)), this->ui->spinBoxZoom,
            SLOT(setValue(int)));

    // Sliders to spin boxes (sizes)
    connect(this->ui->sliderDisplayWidth, SIGNAL(valueChanged(int)), this->ui->spinBoxDisplayWidth,
            SLOT(setValue(int)));
    connect(this->ui->sliderDisplayHeight, SIGNAL(valueChanged(int)),
            this->ui->spinBoxDisplayHeight, SLOT(setValue(int)));
    connect(this->ui->sliderDisplayDepth, SIGNAL(valueChanged(int)), this->ui->spinBoxDisplayDepth,
            SLOT(setValue(int)));

    // Sliders to widget (sizes)
    connect(this->ui->sliderDisplayWidth, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayWidth(int)));
    connect(this->ui->sliderDisplayHeight, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayHeight(int)));
    connect(this->ui->sliderDisplayDepth, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayDepth(int)));

    // Spin boxes to sliders (sizes)
    connect(this->ui->spinBoxDisplayWidth, SIGNAL(valueChanged(int)), this->ui->sliderDisplayWidth,
            SLOT(setValue(int)));
    connect(this->ui->spinBoxDisplayHeight, SIGNAL(valueChanged(int)),
            this->ui->sliderDisplayHeight, SLOT(setValue(int)));
    connect(this->ui->spinBoxDisplayDepth, SIGNAL(valueChanged(int)), this->ui->sliderDisplayDepth,
            SLOT(setValue(int)));

    // Spin boxes to widget (sizes)
    connect(this->ui->spinBoxDisplayWidth, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayWidth(int)));
    connect(this->ui->spinBoxDisplayHeight, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayHeight(int)));
    connect(this->ui->spinBoxDisplayDepth, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayDepth(int)));
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
    this->ui->glWidget->setDisplayWidth(this->ui->spinBoxDisplayWidth->value());
    this->ui->glWidget->setDisplayHeight(this->ui->spinBoxDisplayHeight->value());
    this->ui->glWidget->setDisplayDepth(this->ui->spinBoxDisplayDepth->value());
    this->ui->glWidget->updateGL();
}
