//==============================================================================
// Name        : MainWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.1 (05/04/2019)
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
        QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    // Combo boxes to widget (positioning)
    connect(this->ui->comboBoxPicturesDepth, SIGNAL(currentIndexChanged(int)), this->ui->glWidget,
            SLOT(setPicturesDepth(int)));
    connect(this->ui->comboBoxPicturesRotation, SIGNAL(currentIndexChanged(int)),
            this->ui->glWidget, SLOT(setPicturesRotation(int)));

    // Widget to combo boxes (positioning)
    connect(this->ui->glWidget, SIGNAL(picturesDepthChanged(int)), this->ui->comboBoxPicturesDepth,
            SLOT(setCurrentIndex(int)));
    connect(this->ui->glWidget, SIGNAL(picturesRotationChanged(int)),
            this->ui->comboBoxPicturesRotation, SLOT(setCurrentIndex(int)));

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
    connect(this->ui->sliderDisplaySpacing, SIGNAL(valueChanged(int)),
            this->ui->spinBoxDisplaySpacing, SLOT(setValue(int)));

    // Sliders to widget (sizes)
    connect(this->ui->sliderDisplayWidth, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayWidth(int)));
    connect(this->ui->sliderDisplayHeight, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayHeight(int)));
    connect(this->ui->sliderDisplayDepth, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayDepth(int)));
    connect(this->ui->sliderDisplaySpacing, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplaySpacing(int)));

    // Spin boxes to sliders (sizes)
    connect(this->ui->spinBoxDisplayWidth, SIGNAL(valueChanged(int)), this->ui->sliderDisplayWidth,
            SLOT(setValue(int)));
    connect(this->ui->spinBoxDisplayHeight, SIGNAL(valueChanged(int)),
            this->ui->sliderDisplayHeight, SLOT(setValue(int)));
    connect(this->ui->spinBoxDisplayDepth, SIGNAL(valueChanged(int)), this->ui->sliderDisplayDepth,
            SLOT(setValue(int)));
    connect(this->ui->spinBoxDisplaySpacing, SIGNAL(valueChanged(int)),
            this->ui->sliderDisplaySpacing, SLOT(setValue(int)));

    // Spin boxes to widget (sizes)
    connect(this->ui->spinBoxDisplayWidth, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayWidth(int)));
    connect(this->ui->spinBoxDisplayHeight, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayHeight(int)));
    connect(this->ui->spinBoxDisplayDepth, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplayDepth(int)));
    connect(this->ui->spinBoxDisplaySpacing, SIGNAL(valueChanged(int)), this->ui->glWidget,
            SLOT(setDisplaySpacing(int)));
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

void MainWindow::on_actionLoad_triggered()
{
    QList<QString> fileNames = QFileDialog::getOpenFileNames(this,
            QString::fromUtf8("Sélection des fichiers image"), 0,
            QString::fromUtf8("Fichier image (*.bmp *.jpg *.jpeg *.png)"));

    this->ui->glWidget->removePictures();
    for (QList<QString>::const_iterator itFileName = fileNames.begin();
            itFileName != fileNames.end(); itFileName++)
    {
        Picture* picture = new Picture();
        picture->initialize(*itFileName);
        this->ui->glWidget->addPicture(picture);
    }
    this->ui->glWidget->setDisplayWidth(this->ui->spinBoxDisplayWidth->value());
    this->ui->glWidget->setDisplayHeight(this->ui->spinBoxDisplayHeight->value());
    this->ui->glWidget->setDisplayDepth(this->ui->spinBoxDisplayDepth->value());
    this->ui->glWidget->setDisplaySpacing(this->ui->spinBoxDisplaySpacing->value());
    this->ui->glWidget->updateGL();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
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
            QString::fromUtf8("Visualisation3D - Version 1.1.1 (05/04/2019).\n"
                    "Réalisée par Alexis Foerster (alexis.foerster@gmail.com)."), QMessageBox::Ok,
            this);
    messageBox->exec();
}
