//==============================================================================
// Name        : MainWindow.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.2 (28/02/2020)
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
    explicit MainWindow(QWidget* parent = NULL);
    virtual ~MainWindow();

public slots:
    void on_actionLoad_triggered();
    void on_actionQuit_triggered();
    void on_actionDocumentation_triggered();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow* ui;
};

#endif /* MAINWINDOW_H */
