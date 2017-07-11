//==============================================================================
// Name        : MainWindow.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
// Description : Header file of the MainWindow class
//==============================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    virtual ~MainWindow();

public slots:
    void on_actionCharger_triggered();

private:
    Ui::MainWindow* ui;
};

#endif /* MAINWINDOW_H */
