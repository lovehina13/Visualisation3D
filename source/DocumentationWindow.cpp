//==============================================================================
// Name        : DocumentationWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/03/2020)
// Description : Source file of the DocumentationWindow class
//==============================================================================

#include "DocumentationWindow.h"
#include "ui_DocumentationWindow.h"

DocumentationWindow::DocumentationWindow(QWidget* parent) :
        QDialog(parent), ui(new Ui::DocumentationWindow)
{
    this->ui->setupUi(this);
}

DocumentationWindow::~DocumentationWindow()
{
    delete this->ui;
}
