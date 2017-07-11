//==============================================================================
// Name        : Picture.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
// Description : Source file of the Picture class
//==============================================================================

#include "Picture.h"
#include <QGLWidget>
#include <QImage>

Picture::Picture() :
        QGLFunctions(), width(0), height(0), depth(0), cubeMapTextureID(0)
{
    // initialize(QString());
}

Picture::~Picture()
{
    finalize();
}

void Picture::initialize(QString fileName)
{
    GLenum cubeMapTarget[6] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};

    QImage textureImage = QGLWidget::convertToGLFormat(QImage(fileName));

    glGenTextures(1, &cubeMapTextureID);

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    if (textureImage.bits())
    {
        width = textureImage.width();
        height = textureImage.height();
        depth = 2;
        for (int face = 0; face < 6; face++)
        {
            glTexImage2D(cubeMapTarget[face], 0, GL_RGBA, textureImage.width(),
                    textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits());
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
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
    return (float) width / (float) qMax(width, height);
}

float Picture::heightRatio()
{
    return (float) height / (float) qMax(width, height);
}

void Picture::drawPicture()
{
    float n = -8.0;
    float p = +8.0;
    float nw = n * widthRatio();
    float pw = p * widthRatio();
    float nh = n * heightRatio();
    float ph = p * heightRatio();
    float nd = (float) -depth / 2.0;
    float pd = (float) +depth / 2.0;

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS); // FACE_RIGHT
    glTexCoord3f(p, p, p); glVertex3f(pw, nh, pd);
    glTexCoord3f(p, n, p); glVertex3f(pw, ph, pd);
    glTexCoord3f(p, n, n); glVertex3f(pw, ph, nd);
    glTexCoord3f(p, p, n); glVertex3f(pw, nh, nd);
    glEnd();

    glBegin(GL_QUADS); // FACE_LEFT
    glTexCoord3f(n, p, n); glVertex3f(nw, nh, nd);
    glTexCoord3f(n, n, n); glVertex3f(nw, ph, nd);
    glTexCoord3f(n, n, p); glVertex3f(nw, ph, pd);
    glTexCoord3f(n, p, p); glVertex3f(nw, nh, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_TOP
    glTexCoord3f(n, p, n); glVertex3f(nw, ph, pd);
    glTexCoord3f(n, p, p); glVertex3f(nw, ph, nd);
    glTexCoord3f(p, p, p); glVertex3f(pw, ph, nd);
    glTexCoord3f(p, p, n); glVertex3f(pw, ph, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_BOTTOM
    glTexCoord3f(n, n, p); glVertex3f(nw, nh, nd);
    glTexCoord3f(n, n, n); glVertex3f(nw, nh, pd);
    glTexCoord3f(p, n, n); glVertex3f(pw, nh, pd);
    glTexCoord3f(p, n, p); glVertex3f(pw, nh, nd);
    glEnd();

    glBegin(GL_QUADS); // FACE_FRONT
    glTexCoord3f(n, p, p); glVertex3f(nw, nh, pd);
    glTexCoord3f(n, n, p); glVertex3f(nw, ph, pd);
    glTexCoord3f(p, n, p); glVertex3f(pw, ph, pd);
    glTexCoord3f(p, p, p); glVertex3f(pw, nh, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_BACK
    glTexCoord3f(p, p, n); glVertex3f(pw, nh, nd);
    glTexCoord3f(p, n, n); glVertex3f(pw, ph, nd);
    glTexCoord3f(n, n, n); glVertex3f(nw, ph, nd);
    glTexCoord3f(n, p, n); glVertex3f(nw, nh, nd);
    glEnd();
}
