//==============================================================================
// Name        : Picture.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.2 (28/02/2020)
// Description : Source file of the Picture class
//==============================================================================

#include "Picture.h"
#include <QGLWidget>
#include <QGraphicsPixmapItem>
#include <QPixmap>

Picture::Picture() :
        QGLFunctions(), pictureWidth(0), pictureHeight(0), cropPictureWidth(0),
                cropPictureHeight(0), displayWidth(0.0), displayHeight(0.0), displayDepth(0.0),
                displaySpacing(0.0), cubeMapTextureID(0)
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

void Picture::setDisplaySpacing(float size)
{
    displaySpacing = size;
}

void Picture::initialize(QString fileName)
{
    textureImage = QImage(fileName);

    glGenTextures(1, &cubeMapTextureID);

    if (textureImage.bits())
    {
        QPixmap pixmap = QPixmap::fromImage(textureImage);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
        int width = item->opaqueArea().boundingRect().width();
        int height = item->opaqueArea().boundingRect().height();
        int minWidth = item->opaqueArea().boundingRect().left();
        int maxWidth = item->opaqueArea().boundingRect().right();
        int minHeight = item->opaqueArea().boundingRect().top();
        int maxHeight = item->opaqueArea().boundingRect().bottom();

        pictureWidth = textureImage.width();
        pictureHeight = textureImage.height();
        cropPictureWidth = width;
        cropPictureHeight = height;
        initializeFaces(minWidth, maxWidth, minHeight, maxHeight);

        delete item;
    }
}

void Picture::paint(int itPicture, int nbPictures)
{
    glEnable(GL_TEXTURE_CUBE_MAP);

    drawPicture(itPicture, nbPictures);

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

float Picture::cropWidthRatio()
{
    return (float) cropPictureWidth / (float) pictureWidth;
}

float Picture::cropHeightRatio()
{
    return (float) cropPictureHeight / (float) pictureHeight;
}

void Picture::initializeFaces(int minWidth, int maxWidth, int minHeight, int maxHeight)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);

    // FACE_RIGHT and FACE_LEFT
    QImage imageFaceRight(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_ARGB32);
    QImage imageFaceLeft(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_ARGB32);
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
    QImage imageFaceTop(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_ARGB32);
    QImage imageFaceBottom(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_ARGB32);
    for (int x = minWidth; x < maxWidth; x++)
    {
        for (int y = minHeight; y < maxHeight; y++)
        {
            imageFaceTop.setPixel(x - minWidth, y - minHeight,
                    textureImage.pixel((minWidth + maxWidth - 1) - x, minHeight));
            imageFaceBottom.setPixel(x - minWidth, y - minHeight,
                    textureImage.pixel((minWidth + maxWidth - 1) - x, (maxHeight - 1)));
        }
    }
    imageFaceTop = QGLWidget::convertToGLFormat(imageFaceTop);
    imageFaceBottom = QGLWidget::convertToGLFormat(imageFaceBottom);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, imageFaceTop.width(),
            imageFaceTop.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFaceTop.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, imageFaceBottom.width(),
            imageFaceBottom.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFaceBottom.bits());

    // FACE_FRONT and FACE_BACK
    QImage imageFaceFront(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_ARGB32);
    QImage imageFaceBack(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_ARGB32);
    for (int x = minWidth; x < maxWidth; x++)
    {
        for (int y = minHeight; y < maxHeight; y++)
        {
            imageFaceFront.setPixel(x - minWidth, y - minHeight,
                    textureImage.pixel((minWidth + maxWidth - 1) - x, y));
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

void Picture::drawPicture(int itPicture, int nbPictures)
{
    float n = -1.0;
    float p = +1.0;
    float nx = n;
    float px = p;
    float ny = n;
    float py = p;
    float nz = n;
    float pz = p;
    float nw = -displayWidth * widthRatio() * cropWidthRatio();
    float pw = +displayWidth * widthRatio() * cropWidthRatio();
    float nh = -displayHeight * heightRatio() * cropHeightRatio();
    float ph = +displayHeight * heightRatio() * cropHeightRatio();
    float nd = -displayDepth;
    float pd = +displayDepth;

    if (nbPictures > 1)
    {
        float subDepth = (displayDepth * 2.0) / (float) nbPictures;
        float subSpacing = displaySpacing * subDepth;
        nd = -displayDepth + subDepth * itPicture + (subSpacing / 2.0);
        pd = -displayDepth + subDepth * (itPicture + 1) - (subSpacing / 2.0);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS); // FACE_RIGHT
    glTexCoord3f(px, py, pz); glVertex3f(pw, nh, nd);
    glTexCoord3f(px, ny, pz); glVertex3f(pw, ph, nd);
    glTexCoord3f(px, ny, nz); glVertex3f(pw, ph, pd);
    glTexCoord3f(px, py, nz); glVertex3f(pw, nh, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_LEFT
    glTexCoord3f(nx, py, nz); glVertex3f(nw, nh, pd);
    glTexCoord3f(nx, ny, nz); glVertex3f(nw, ph, pd);
    glTexCoord3f(nx, ny, pz); glVertex3f(nw, ph, nd);
    glTexCoord3f(nx, py, pz); glVertex3f(nw, nh, nd);
    glEnd();

    glBegin(GL_QUADS); // FACE_TOP
    glTexCoord3f(nx, py, nz); glVertex3f(pw, ph, pd);
    glTexCoord3f(nx, py, pz); glVertex3f(pw, ph, nd);
    glTexCoord3f(px, py, pz); glVertex3f(nw, ph, nd);
    glTexCoord3f(px, py, nz); glVertex3f(nw, ph, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_BOTTOM
    glTexCoord3f(nx, ny, pz); glVertex3f(pw, nh, nd);
    glTexCoord3f(nx, ny, nz); glVertex3f(pw, nh, pd);
    glTexCoord3f(px, ny, nz); glVertex3f(nw, nh, pd);
    glTexCoord3f(px, ny, pz); glVertex3f(nw, nh, nd);
    glEnd();

    glBegin(GL_QUADS); // FACE_FRONT
    glTexCoord3f(nx, py, pz); glVertex3f(pw, nh, pd);
    glTexCoord3f(nx, ny, pz); glVertex3f(pw, ph, pd);
    glTexCoord3f(px, ny, pz); glVertex3f(nw, ph, pd);
    glTexCoord3f(px, py, pz); glVertex3f(nw, nh, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_BACK
    glTexCoord3f(px, py, nz); glVertex3f(nw, nh, nd);
    glTexCoord3f(px, ny, nz); glVertex3f(nw, ph, nd);
    glTexCoord3f(nx, ny, nz); glVertex3f(pw, ph, nd);
    glTexCoord3f(nx, py, nz); glVertex3f(pw, nh, nd);
    glEnd();

    glDisable(GL_BLEND);
}
