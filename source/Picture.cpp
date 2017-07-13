//==============================================================================
// Name        : Picture.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
// Description : Source file of the Picture class
//==============================================================================

#include "Picture.h"
#include <QGLWidget>

Picture::Picture() :
        QGLFunctions(), pictureWidth(0), pictureHeight(0), displayWidth(0.0), displayHeight(0.0),
                displayDepth(0.0), cubeMapTextureID(0)
{
    // initialize(QString());
}

Picture::~Picture()
{
    finalize();
}

void Picture::setDisplayWidth(float size)
{
    displayWidth = size;
}

void Picture::setDisplayHeight(float size)
{
    displayHeight = size;
}

void Picture::setDisplayDepth(float size)
{
    displayDepth = size;
}

void Picture::initialize(QString fileName)
{
    textureImage = QGLWidget::convertToGLFormat(QImage(fileName));

    glGenTextures(1, &cubeMapTextureID);

    if (textureImage.bits())
    {
        pictureWidth = textureImage.width();
        pictureHeight = textureImage.height();
        initializeFaces(0, pictureWidth, 0, pictureHeight);
    }
}

void Picture::paint()
{
    glEnable(GL_TEXTURE_CUBE_MAP);

    drawPicture();

    glDisable(GL_TEXTURE_CUBE_MAP);
}

void Picture::finalize()
{
    glDeleteTextures(1, &cubeMapTextureID);
}

float Picture::widthRatio()
{
    return (float) pictureWidth / (float) qMax(pictureWidth, pictureHeight);
}

float Picture::heightRatio()
{
    return (float) pictureHeight / (float) qMax(pictureWidth, pictureHeight);
}

void Picture::initializeFaces(int minWidth, int maxWidth, int minHeight, int maxHeight)
{
    GLenum cubeMapTarget[6] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    for (int face = 0; face < 6; face++)
    {
        glTexImage2D(cubeMapTarget[face], 0, GL_RGBA, textureImage.width(), textureImage.height(),
                0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
}

void Picture::drawPicture()
{
    float n = -1.0;
    float p = +1.0;
    float nw = -displayWidth * widthRatio();
    float pw = +displayWidth * widthRatio();
    float nh = -displayHeight * heightRatio();
    float ph = +displayHeight * heightRatio();
    float nd = -displayDepth;
    float pd = +displayDepth;

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS); // FACE_RIGHT
    glTexCoord3f(p, p, p); glVertex3f(pw, nh, nd);
    glTexCoord3f(p, n, p); glVertex3f(pw, ph, nd);
    glTexCoord3f(p, n, n); glVertex3f(pw, ph, pd);
    glTexCoord3f(p, p, n); glVertex3f(pw, nh, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_LEFT
    glTexCoord3f(n, p, n); glVertex3f(nw, nh, pd);
    glTexCoord3f(n, n, n); glVertex3f(nw, ph, pd);
    glTexCoord3f(n, n, p); glVertex3f(nw, ph, nd);
    glTexCoord3f(n, p, p); glVertex3f(nw, nh, nd);
    glEnd();

    glBegin(GL_QUADS); // FACE_TOP
    glTexCoord3f(n, p, n); glVertex3f(pw, ph, pd);
    glTexCoord3f(n, p, p); glVertex3f(pw, ph, nd);
    glTexCoord3f(p, p, p); glVertex3f(nw, ph, nd);
    glTexCoord3f(p, p, n); glVertex3f(nw, ph, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_BOTTOM
    glTexCoord3f(n, n, p); glVertex3f(pw, nh, nd);
    glTexCoord3f(n, n, n); glVertex3f(pw, nh, pd);
    glTexCoord3f(p, n, n); glVertex3f(nw, nh, pd);
    glTexCoord3f(p, n, p); glVertex3f(nw, nh, nd);
    glEnd();

    glBegin(GL_QUADS); // FACE_FRONT
    glTexCoord3f(n, p, p); glVertex3f(pw, nh, pd);
    glTexCoord3f(n, n, p); glVertex3f(pw, ph, pd);
    glTexCoord3f(p, n, p); glVertex3f(nw, ph, pd);
    glTexCoord3f(p, p, p); glVertex3f(nw, nh, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_BACK
    glTexCoord3f(p, p, n); glVertex3f(nw, nh, nd);
    glTexCoord3f(p, n, n); glVertex3f(nw, ph, nd);
    glTexCoord3f(n, n, n); glVertex3f(pw, ph, nd);
    glTexCoord3f(n, p, n); glVertex3f(pw, nh, nd);
    glEnd();
}
