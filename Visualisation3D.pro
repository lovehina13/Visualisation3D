#===============================================================================
# Name        : Visualisation3D.pro
# Author      : Alexis Foerster (alexis.foerster@gmail.com)
# Version     : 1.0.0 (DD/MM/YYYY)
# Description : Qt project file of the Visualisation3D project
#===============================================================================

TEMPLATE = app
TARGET = Visualisation3D
DEPENDPATH += . include source
INCLUDEPATH += . include
OBJECTS_DIR = objects
MOC_DIR = objects
RCC_DIR = objects
UI_DIR = objects
QT += opengl

HEADERS += include/GLWidget.h \
           include/MainWindow.h \
           include/Picture.h \
           include/SkyBox.h
SOURCES += source/GLWidget.cpp \
           source/MainWindow.cpp \
           source/Picture.cpp \
           source/SkyBox.cpp \
           source/Visualisation3D.cpp
FORMS += interfaces/MainWindow.ui
RESOURCES += ressources/Ressources.qrc

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
