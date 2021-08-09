//==============================================================================
// Name        : DocumentationWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/03/2020)
// Description : Source file of the DocumentationWindow class
//==============================================================================

#include "DocumentationWindow.h"
#include "ui_DocumentationWindow.h"

DocumentationWindow::DocumentationWindow(QWidget* parent) :
        QDialog(parent), _ui(new Ui::DocumentationWindow)
{
    _ui->setupUi(this);
}

DocumentationWindow::~DocumentationWindow()
{
    delete _ui;
}
