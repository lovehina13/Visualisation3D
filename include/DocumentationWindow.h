//==============================================================================
// Name        : DocumentationWindow.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/03/2020)
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
    explicit DocumentationWindow(QWidget* parent = nullptr);
    virtual ~DocumentationWindow();

private:
    Ui::DocumentationWindow* ui;
};

#endif /* DOCUMENTATIONWINDOW_H */
