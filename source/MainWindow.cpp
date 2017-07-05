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

    connect(this->ui->sliderRotationX, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationX,
            SLOT(setValue(int)));
    connect(this->ui->sliderRotationY, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationY,
            SLOT(setValue(int)));
    connect(this->ui->sliderRotationZ, SIGNAL(valueChanged(int)), this->ui->spinBoxRotationZ,
            SLOT(setValue(int)));

    connect(this->ui->spinBoxRotationX, SIGNAL(valueChanged(int)), this->ui->sliderRotationX,
            SLOT(setValue(int)));
    connect(this->ui->spinBoxRotationY, SIGNAL(valueChanged(int)), this->ui->sliderRotationY,
            SLOT(setValue(int)));
    connect(this->ui->spinBoxRotationZ, SIGNAL(valueChanged(int)), this->ui->sliderRotationZ,
            SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete this->ui;
}
