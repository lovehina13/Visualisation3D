//==============================================================================
// Name        : SkyBox.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.2 (28/05/2018)
// Description : Source file of the SkyBox class
//==============================================================================

#include "SkyBox.h"
#include <cmath>
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
    glDepthFunc(GL_LEQUAL);

    drawSkyBox();

    glDepthFunc(GL_GEQUAL);
    glDisable(GL_TEXTURE_CUBE_MAP);
}

void SkyBox::finalize()
{
    glDeleteTextures(1, &cubeMapTextureID);
}

void SkyBox::drawSkyBox()
{
    float n = -10.0 * sqrt(2.0);
    float p = +10.0 * sqrt(2.0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS); // FACE_RIGHT
    glTexCoord3f(p, p, p); glVertex3f(p, n, p);
    glTexCoord3f(p, n, p); glVertex3f(p, p, p);
    glTexCoord3f(p, n, n); glVertex3f(p, p, n);
    glTexCoord3f(p, p, n); glVertex3f(p, n, n);
    glEnd();

    glBegin(GL_QUADS); // FACE_LEFT
    glTexCoord3f(n, p, n); glVertex3f(n, n, n);
    glTexCoord3f(n, n, n); glVertex3f(n, p, n);
    glTexCoord3f(n, n, p); glVertex3f(n, p, p);
    glTexCoord3f(n, p, p); glVertex3f(n, n, p);
    glEnd();

    glBegin(GL_QUADS); // FACE_TOP
    glTexCoord3f(n, p, n); glVertex3f(n, p, p);
    glTexCoord3f(n, p, p); glVertex3f(n, p, n);
    glTexCoord3f(p, p, p); glVertex3f(p, p, n);
    glTexCoord3f(p, p, n); glVertex3f(p, p, p);
    glEnd();

    glBegin(GL_QUADS); // FACE_BOTTOM
    glTexCoord3f(n, n, p); glVertex3f(n, n, n);
    glTexCoord3f(n, n, n); glVertex3f(n, n, p);
    glTexCoord3f(p, n, n); glVertex3f(p, n, p);
    glTexCoord3f(p, n, p); glVertex3f(p, n, n);
    glEnd();

    glBegin(GL_QUADS); // FACE_FRONT
    glTexCoord3f(n, p, p); glVertex3f(n, n, p);
    glTexCoord3f(n, n, p); glVertex3f(n, p, p);
    glTexCoord3f(p, n, p); glVertex3f(p, p, p);
    glTexCoord3f(p, p, p); glVertex3f(p, n, p);
    glEnd();

    glBegin(GL_QUADS); // FACE_BACK
    glTexCoord3f(p, p, n); glVertex3f(p, n, n);
    glTexCoord3f(p, n, n); glVertex3f(p, p, n);
    glTexCoord3f(n, n, n); glVertex3f(n, p, n);
    glTexCoord3f(n, p, n); glVertex3f(n, n, n);
    glEnd();
}
