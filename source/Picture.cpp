//==============================================================================
// Name        : Picture.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/03/2020)
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

void Picture::setDisplayWidth(double size)
{
    displayWidth = size;
}

void Picture::setDisplayHeight(double size)
{
    displayHeight = size;
}

void Picture::setDisplayDepth(double size)
{
    displayDepth = size;
}

void Picture::setDisplaySpacing(double size)
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
        int width = static_cast<int>(item->opaqueArea().boundingRect().width());
        int height = static_cast<int>(item->opaqueArea().boundingRect().height());
        int minWidth = static_cast<int>(item->opaqueArea().boundingRect().left());
        int maxWidth = static_cast<int>(item->opaqueArea().boundingRect().right());
        int minHeight = static_cast<int>(item->opaqueArea().boundingRect().top());
        int maxHeight = static_cast<int>(item->opaqueArea().boundingRect().bottom());

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

double Picture::widthRatio()
{
    return static_cast<double>(pictureWidth)
            / static_cast<double>(qMax(pictureWidth, pictureHeight));
}

double Picture::heightRatio()
{
    return static_cast<double>(pictureHeight)
            / static_cast<double>(qMax(pictureWidth, pictureHeight));
}

double Picture::cropWidthRatio()
{
    return static_cast<double>(cropPictureWidth) / static_cast<double>(pictureWidth);
}

double Picture::cropHeightRatio()
{
    return static_cast<double>(cropPictureHeight) / static_cast<double>(pictureHeight);
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
    double n = -1.0;
    double p = +1.0;
    double nx = n;
    double px = p;
    double ny = n;
    double py = p;
    double nz = n;
    double pz = p;
    double nw = -displayWidth * widthRatio() * cropWidthRatio();
    double pw = +displayWidth * widthRatio() * cropWidthRatio();
    double nh = -displayHeight * heightRatio() * cropHeightRatio();
    double ph = +displayHeight * heightRatio() * cropHeightRatio();
    double nd = -displayDepth;
    double pd = +displayDepth;

    if (nbPictures > 1)
    {
        double subDepth = (displayDepth * 2.0) / static_cast<double>(nbPictures);
        double subSpacing = displaySpacing * subDepth;
        nd = -displayDepth + subDepth * itPicture + (subSpacing / 2.0);
        pd = -displayDepth + subDepth * (itPicture + 1) - (subSpacing / 2.0);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    glColor3d(1.0, 1.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS); // FACE_RIGHT
    glTexCoord3d(px, py, pz); glVertex3d(pw, nh, nd);
    glTexCoord3d(px, ny, pz); glVertex3d(pw, ph, nd);
    glTexCoord3d(px, ny, nz); glVertex3d(pw, ph, pd);
    glTexCoord3d(px, py, nz); glVertex3d(pw, nh, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_LEFT
    glTexCoord3d(nx, py, nz); glVertex3d(nw, nh, pd);
    glTexCoord3d(nx, ny, nz); glVertex3d(nw, ph, pd);
    glTexCoord3d(nx, ny, pz); glVertex3d(nw, ph, nd);
    glTexCoord3d(nx, py, pz); glVertex3d(nw, nh, nd);
    glEnd();

    glBegin(GL_QUADS); // FACE_TOP
    glTexCoord3d(nx, py, nz); glVertex3d(pw, ph, pd);
    glTexCoord3d(nx, py, pz); glVertex3d(pw, ph, nd);
    glTexCoord3d(px, py, pz); glVertex3d(nw, ph, nd);
    glTexCoord3d(px, py, nz); glVertex3d(nw, ph, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_BOTTOM
    glTexCoord3d(nx, ny, pz); glVertex3d(pw, nh, nd);
    glTexCoord3d(nx, ny, nz); glVertex3d(pw, nh, pd);
    glTexCoord3d(px, ny, nz); glVertex3d(nw, nh, pd);
    glTexCoord3d(px, ny, pz); glVertex3d(nw, nh, nd);
    glEnd();

    glBegin(GL_QUADS); // FACE_FRONT
    glTexCoord3d(nx, py, pz); glVertex3d(pw, nh, pd);
    glTexCoord3d(nx, ny, pz); glVertex3d(pw, ph, pd);
    glTexCoord3d(px, ny, pz); glVertex3d(nw, ph, pd);
    glTexCoord3d(px, py, pz); glVertex3d(nw, nh, pd);
    glEnd();

    glBegin(GL_QUADS); // FACE_BACK
    glTexCoord3d(px, py, nz); glVertex3d(nw, nh, nd);
    glTexCoord3d(px, ny, nz); glVertex3d(nw, ph, nd);
    glTexCoord3d(nx, ny, nz); glVertex3d(pw, ph, nd);
    glTexCoord3d(nx, py, nz); glVertex3d(pw, nh, nd);
    glEnd();

    glDisable(GL_BLEND);
}
