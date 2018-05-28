//==============================================================================
// Name        : DocumentationWindow.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.2 (28/05/2018)
// Description : Header file of the DocumentationWindow class
//==============================================================================

#ifndef DOCUMENTATIONWINDOW_H
#define DOCUMENTATIONWINDOW_H

#include <QDialog>
#include <QWidget>

namespace Ui
{
class DocumentationWindow;
}

class DocumentationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DocumentationWindow(QWidget* parent = NULL);
    virtual ~DocumentationWindow();

private:
    Ui::DocumentationWindow* ui;
};

#endif /* DOCUMENTATIONWINDOW_H */
