//==============================================================================
// Name        : SkyBox.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
// Description : Source file of the SkyBox class
//==============================================================================

#include "SkyBox.h"
#include <QGLWidget>
#include <QImage>

SkyBox::SkyBox() :
        QGLFunctions(), cubeMapTextureID(0)
{
    // initialize();
}

SkyBox::~SkyBox()
{
    finalize();
}

void SkyBox::initialize()
{
    GLenum cubeMapTarget[6] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};

    QImage textureImage[6];
    textureImage[FACE_RIGHT] = QGLWidget::convertToGLFormat(QImage(":/skybox/skybox-right"));
    textureImage[FACE_LEFT] = QGLWidget::convertToGLFormat(QImage(":/skybox/skybox-left"));
    textureImage[FACE_TOP] = QGLWidget::convertToGLFormat(QImage(":/skybox/skybox-top"));
    textureImage[FACE_BOTTOM] = QGLWidget::convertToGLFormat(QImage(":/skybox/skybox-bottom"));
    textureImage[FACE_FRONT] = QGLWidget::convertToGLFormat(QImage(":/skybox/skybox-front"));
    textureImage[FACE_BACK] = QGLWidget::convertToGLFormat(QImage(":/skybox/skybox-back"));

    glGenTextures(1, &cubeMapTextureID);

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    for (int face = 0; face < 6; face++)
    {
        if (textureImage[face].bits())
        {
            glTexImage2D(cubeMapTarget[face], 0, GL_RGBA, textureImage[face].width(),
                    textureImage[face].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                    textureImage[face].bits());
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SkyBox::paint()
{
    glEnable(GL_TEXTURE_CUBE_MAP);

    drawSkyBox();

    glDisable(GL_TEXTURE_CUBE_MAP);
}

void SkyBox::finalize()
{
    glDeleteTextures(1, &cubeMapTextureID);
}

void SkyBox::drawSkyBox()
{
    // TODO void SkyBox::drawSkyBox()
}
