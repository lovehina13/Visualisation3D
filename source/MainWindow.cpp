//==============================================================================
// Name        : MainWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.3.0 (09/08/2021)
// Description : Source file of the MainWindow class
//==============================================================================

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DocumentationWindow.h"
#include "Picture.h"
#include <QFileDialog>
#include <QList>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    // Combo boxes and spin boxes to widget (positioning)
    connect(_ui->comboBoxPicturesDepth, SIGNAL(currentIndexChanged(int)), _ui->glWidget,
            SLOT(setPicturesDepth(int)));
    connect(_ui->spinBoxPicturesRotation, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setPicturesRotation(int)));

    // Widget to combo boxes and spin boxes (positioning)
    connect(_ui->glWidget, SIGNAL(picturesDepthChanged(int)), _ui->comboBoxPicturesDepth,
            SLOT(setCurrentIndex(int)));
    connect(_ui->glWidget, SIGNAL(picturesRotationChanged(int)), _ui->spinBoxPicturesRotation,
            SLOT(setValue(int)));

    // Sliders to spin boxes (rotations)
    connect(_ui->sliderRotationX, SIGNAL(valueChanged(int)), _ui->spinBoxRotationX,
            SLOT(setValue(int)));
    connect(_ui->sliderRotationY, SIGNAL(valueChanged(int)), _ui->spinBoxRotationY,
            SLOT(setValue(int)));
    connect(_ui->sliderRotationZ, SIGNAL(valueChanged(int)), _ui->spinBoxRotationZ,
            SLOT(setValue(int)));

    // Sliders to widget (rotations)
    connect(_ui->sliderRotationX, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setYRotation(int)));
    connect(_ui->sliderRotationY, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setXRotation(int)));
    connect(_ui->sliderRotationZ, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setZRotation(int)));

    // Spin boxes to sliders (rotations)
    connect(_ui->spinBoxRotationX, SIGNAL(valueChanged(int)), _ui->sliderRotationX,
            SLOT(setValue(int)));
    connect(_ui->spinBoxRotationY, SIGNAL(valueChanged(int)), _ui->sliderRotationY,
            SLOT(setValue(int)));
    connect(_ui->spinBoxRotationZ, SIGNAL(valueChanged(int)), _ui->sliderRotationZ,
            SLOT(setValue(int)));

    // Spin boxes to widget (rotations)
    connect(_ui->spinBoxRotationX, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setYRotation(int)));
    connect(_ui->spinBoxRotationY, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setXRotation(int)));
    connect(_ui->spinBoxRotationZ, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setZRotation(int)));

    // Widget to sliders (rotations)
    connect(_ui->glWidget, SIGNAL(xRotationChanged(int)), _ui->sliderRotationY,
            SLOT(setValue(int)));
    connect(_ui->glWidget, SIGNAL(yRotationChanged(int)), _ui->sliderRotationX,
            SLOT(setValue(int)));
    connect(_ui->glWidget, SIGNAL(zRotationChanged(int)), _ui->sliderRotationZ,
            SLOT(setValue(int)));

    // Widget to spin boxes (rotations)
    connect(_ui->glWidget, SIGNAL(xRotationChanged(int)), _ui->spinBoxRotationY,
            SLOT(setValue(int)));
    connect(_ui->glWidget, SIGNAL(yRotationChanged(int)), _ui->spinBoxRotationX,
            SLOT(setValue(int)));
    connect(_ui->glWidget, SIGNAL(zRotationChanged(int)), _ui->spinBoxRotationZ,
            SLOT(setValue(int)));

    // Sliders to spin boxes (scales)
    connect(_ui->sliderZoom, SIGNAL(valueChanged(int)), _ui->spinBoxZoom, SLOT(setValue(int)));

    // Sliders to widget (scales)
    connect(_ui->sliderZoom, SIGNAL(valueChanged(int)), _ui->glWidget, SLOT(setZoomScale(int)));

    // Spin boxes to sliders (scales)
    connect(_ui->spinBoxZoom, SIGNAL(valueChanged(int)), _ui->sliderZoom, SLOT(setValue(int)));

    // Spin boxes to widget (scales)
    connect(_ui->spinBoxZoom, SIGNAL(valueChanged(int)), _ui->glWidget, SLOT(setZoomScale(int)));

    // Widget to sliders (scales)
    connect(_ui->glWidget, SIGNAL(zoomScaleChanged(int)), _ui->sliderZoom, SLOT(setValue(int)));

    // Widget to spin boxes (scales)
    connect(_ui->glWidget, SIGNAL(zoomScaleChanged(int)), _ui->spinBoxZoom, SLOT(setValue(int)));

    // Sliders to spin boxes (sizes)
    connect(_ui->sliderDisplayWidth, SIGNAL(valueChanged(int)), _ui->spinBoxDisplayWidth,
            SLOT(setValue(int)));
    connect(_ui->sliderDisplayHeight, SIGNAL(valueChanged(int)), _ui->spinBoxDisplayHeight,
            SLOT(setValue(int)));
    connect(_ui->sliderDisplayDepth, SIGNAL(valueChanged(int)), _ui->spinBoxDisplayDepth,
            SLOT(setValue(int)));
    connect(_ui->sliderDisplaySpacing, SIGNAL(valueChanged(int)), _ui->spinBoxDisplaySpacing,
            SLOT(setValue(int)));

    // Sliders to widget (sizes)
    connect(_ui->sliderDisplayWidth, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setDisplayWidth(int)));
    connect(_ui->sliderDisplayHeight, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setDisplayHeight(int)));
    connect(_ui->sliderDisplayDepth, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setDisplayDepth(int)));
    connect(_ui->sliderDisplaySpacing, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setDisplaySpacing(int)));

    // Spin boxes to sliders (sizes)
    connect(_ui->spinBoxDisplayWidth, SIGNAL(valueChanged(int)), _ui->sliderDisplayWidth,
            SLOT(setValue(int)));
    connect(_ui->spinBoxDisplayHeight, SIGNAL(valueChanged(int)), _ui->sliderDisplayHeight,
            SLOT(setValue(int)));
    connect(_ui->spinBoxDisplayDepth, SIGNAL(valueChanged(int)), _ui->sliderDisplayDepth,
            SLOT(setValue(int)));
    connect(_ui->spinBoxDisplaySpacing, SIGNAL(valueChanged(int)), _ui->sliderDisplaySpacing,
            SLOT(setValue(int)));

    // Spin boxes to widget (sizes)
    connect(_ui->spinBoxDisplayWidth, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setDisplayWidth(int)));
    connect(_ui->spinBoxDisplayHeight, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setDisplayHeight(int)));
    connect(_ui->spinBoxDisplayDepth, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setDisplayDepth(int)));
    connect(_ui->spinBoxDisplaySpacing, SIGNAL(valueChanged(int)), _ui->glWidget,
            SLOT(setDisplaySpacing(int)));
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::on_actionLoad_triggered()
{
    QList<QString> fileNames = QFileDialog::getOpenFileNames(this,
            QString::fromUtf8("Sélection des fichiers image"), nullptr,
            QString::fromUtf8("Fichier image (*.bmp *.jpg *.jpeg *.png)"));

    _ui->glWidget->removePictures();
    for (QList<QString>::const_iterator itFileName = fileNames.begin();
            itFileName != fileNames.end(); itFileName++)
    {
        Picture* picture = new Picture();
        picture->initialize(*itFileName);
        _ui->glWidget->addPicture(picture);
    }
    _ui->glWidget->setDisplayWidth(_ui->spinBoxDisplayWidth->value());
    _ui->glWidget->setDisplayHeight(_ui->spinBoxDisplayHeight->value());
    _ui->glWidget->setDisplayDepth(_ui->spinBoxDisplayDepth->value());
    _ui->glWidget->setDisplaySpacing(_ui->spinBoxDisplaySpacing->value());
    _ui->glWidget->updateGL();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionDocumentation_triggered()
{
    DocumentationWindow* documentationWindow = new DocumentationWindow(this);
    documentationWindow->exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox* messageBox = new QMessageBox(QMessageBox::Information,
            QString::fromUtf8("Visualisation3D"),
            QString::fromUtf8("Visualisation3D - Version 1.3.0 (09/08/2021).\n"
                    "Réalisée par Alexis Foerster (alexis.foerster@gmail.com)."), QMessageBox::Ok,
            this);
    messageBox->exec();
}
