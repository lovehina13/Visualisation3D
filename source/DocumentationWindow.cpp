//==============================================================================
// Name        : DocumentationWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.0 (22/07/2018)
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
