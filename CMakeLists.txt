cmake_minimum_required(VERSION 2.6)

project(Visualisation3D)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS interfaces)

find_package(Qt5 5.15.2 REQUIRED Core Widgets OpenGL)

qt5_wrap_cpp(MOC_FILES
    include/DocumentationWindow.h
    include/GLWidget.h
    include/MainWindow.h)

add_executable(Visualisation3D
    source/DocumentationWindow.cpp
    source/GLWidget.cpp
    source/MainWindow.cpp
    source/Picture.cpp
    source/SkyBox.cpp
    source/Visualisation3D.cpp
    interfaces/DocumentationWindow.ui
    interfaces/MainWindow.ui
    resources/Ressources.qrc
    ${MOC_FILES})

target_link_libraries(Visualisation3D PUBLIC Qt5::Core Qt5::Gui Qt5::OpenGL GL)

target_include_directories(Visualisation3D PUBLIC include)

install(TARGETS Visualisation3D DESTINATION bin)
