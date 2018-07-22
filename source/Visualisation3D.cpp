//==============================================================================
// Name        : Visualisation3D.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.0 (22/07/2018)
// Description : Main file of the Visualisation3D project
//==============================================================================

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
