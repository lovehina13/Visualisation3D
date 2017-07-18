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
    textureImage = QImage(fileName);

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
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);

    // FACE_RIGHT and FACE_LEFT
    QImage imageFaceRight(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_RGB32);
    QImage imageFaceLeft(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_RGB32);
    for (int x = minWidth; x < maxWidth; x++)
    {
        for (int y = minHeight; y < maxHeight; y++)
        {
            imageFaceRight.setPixel(x - minWidth, y - minHeight,
                    textureImage.pixel((maxWidth - 1), y));
            imageFaceLeft.setPixel(x - minWidth, y - minHeight, textureImage.pixel(minWidth, y));
        }
    }
    imageFaceRight = QGLWidget::convertToGLFormat(imageFaceRight);
    imageFaceLeft = QGLWidget::convertToGLFormat(imageFaceLeft);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, imageFaceRight.width(),
            imageFaceRight.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFaceRight.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, imageFaceLeft.width(),
            imageFaceLeft.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFaceLeft.bits());

    // FACE_TOP and FACE_BOTTOM
    QImage imageFaceTop(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_RGB32);
    QImage imageFaceBottom(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_RGB32);
    for (int x = minWidth; x < maxWidth; x++)
    {
        for (int y = minHeight; y < maxHeight; y++)
        {
            imageFaceTop.setPixel((maxHeight - 1) - x, y - minHeight,
                    textureImage.pixel(x, minHeight));
            imageFaceBottom.setPixel((maxHeight - 1) - x, y - minHeight,
                    textureImage.pixel(x, (maxHeight - 1)));
        }
    }
    imageFaceTop = QGLWidget::convertToGLFormat(imageFaceTop);
    imageFaceBottom = QGLWidget::convertToGLFormat(imageFaceBottom);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, imageFaceTop.width(),
            imageFaceTop.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFaceTop.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, imageFaceBottom.width(),
            imageFaceBottom.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFaceBottom.bits());

    // FACE_FRONT and FACE_BACK
    QImage imageFaceFront(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_RGB32);
    QImage imageFaceBack(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_RGB32);
    for (int x = minWidth; x < maxWidth; x++)
    {
        for (int y = minHeight; y < maxHeight; y++)
        {
            imageFaceFront.setPixel((maxHeight - 1) - x, y - minHeight, textureImage.pixel(x, y));
            imageFaceBack.setPixel(x - minWidth, y - minHeight, textureImage.pixel(x, y));
        }
    }
    imageFaceFront = QGLWidget::convertToGLFormat(imageFaceFront);
    imageFaceBack = QGLWidget::convertToGLFormat(imageFaceBack);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, imageFaceFront.width(),
            imageFaceFront.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFaceFront.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, imageFaceBack.width(),
            imageFaceBack.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFaceBack.bits());

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
