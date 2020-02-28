//==============================================================================
// Name        : SkyBox.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.2 (28/02/2020)
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
    GLenum cubeMapTarget[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

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
    double n = -10.0 * sqrt(2.0);
    double p = +10.0 * sqrt(2.0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    glColor3d(1.0, 1.0, 1.0);

    glBegin(GL_QUADS); // FACE_RIGHT
    glTexCoord3d(p, p, p); glVertex3d(p, n, p);
    glTexCoord3d(p, n, p); glVertex3d(p, p, p);
    glTexCoord3d(p, n, n); glVertex3d(p, p, n);
    glTexCoord3d(p, p, n); glVertex3d(p, n, n);
    glEnd();

    glBegin(GL_QUADS); // FACE_LEFT
    glTexCoord3d(n, p, n); glVertex3d(n, n, n);
    glTexCoord3d(n, n, n); glVertex3d(n, p, n);
    glTexCoord3d(n, n, p); glVertex3d(n, p, p);
    glTexCoord3d(n, p, p); glVertex3d(n, n, p);
    glEnd();

    glBegin(GL_QUADS); // FACE_TOP
    glTexCoord3d(n, p, n); glVertex3d(n, p, p);
    glTexCoord3d(n, p, p); glVertex3d(n, p, n);
    glTexCoord3d(p, p, p); glVertex3d(p, p, n);
    glTexCoord3d(p, p, n); glVertex3d(p, p, p);
    glEnd();

    glBegin(GL_QUADS); // FACE_BOTTOM
    glTexCoord3d(n, n, p); glVertex3d(n, n, n);
    glTexCoord3d(n, n, n); glVertex3d(n, n, p);
    glTexCoord3d(p, n, n); glVertex3d(p, n, p);
    glTexCoord3d(p, n, p); glVertex3d(p, n, n);
    glEnd();

    glBegin(GL_QUADS); // FACE_FRONT
    glTexCoord3d(n, p, p); glVertex3d(n, n, p);
    glTexCoord3d(n, n, p); glVertex3d(n, p, p);
    glTexCoord3d(p, n, p); glVertex3d(p, p, p);
    glTexCoord3d(p, p, p); glVertex3d(p, n, p);
    glEnd();

    glBegin(GL_QUADS); // FACE_BACK
    glTexCoord3d(p, p, n); glVertex3d(p, n, n);
    glTexCoord3d(p, n, n); glVertex3d(p, p, n);
    glTexCoord3d(n, n, n); glVertex3d(n, p, n);
    glTexCoord3d(n, p, n); glVertex3d(n, n, n);
    glEnd();
}
