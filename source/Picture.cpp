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
        QGLFunctions(), _pictureWidth(0), _pictureHeight(0), _cropPictureWidth(0),
                _cropPictureHeight(0), _displayWidth(0.0), _displayHeight(0.0), _displayDepth(0.0),
                _displaySpacing(0.0), _cubeMapTextureID(0)
{
    // initialize(QString());
}

Picture::~Picture()
{
    finalize();
}

void Picture::setDisplayWidth(double size)
{
    _displayWidth = size;
}

void Picture::setDisplayHeight(double size)
{
    _displayHeight = size;
}

void Picture::setDisplayDepth(double size)
{
    _displayDepth = size;
}

void Picture::setDisplaySpacing(double size)
{
    _displaySpacing = size;
}

void Picture::initialize(QString fileName)
{
    _textureImage = QImage(fileName);

    glGenTextures(1, &_cubeMapTextureID);

    if (_textureImage.bits())
    {
        QPixmap pixmap = QPixmap::fromImage(_textureImage);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
        int width = static_cast<int>(item->opaqueArea().boundingRect().width());
        int height = static_cast<int>(item->opaqueArea().boundingRect().height());
        int minWidth = static_cast<int>(item->opaqueArea().boundingRect().left());
        int maxWidth = static_cast<int>(item->opaqueArea().boundingRect().right());
        int minHeight = static_cast<int>(item->opaqueArea().boundingRect().top());
        int maxHeight = static_cast<int>(item->opaqueArea().boundingRect().bottom());

        _pictureWidth = _textureImage.width();
        _pictureHeight = _textureImage.height();
        _cropPictureWidth = width;
        _cropPictureHeight = height;
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
    glDeleteTextures(1, &_cubeMapTextureID);
}

double Picture::widthRatio()
{
    return static_cast<double>(_pictureWidth)
            / static_cast<double>(qMax(_pictureWidth, _pictureHeight));
}

double Picture::heightRatio()
{
    return static_cast<double>(_pictureHeight)
            / static_cast<double>(qMax(_pictureWidth, _pictureHeight));
}

double Picture::cropWidthRatio()
{
    return static_cast<double>(_cropPictureWidth) / static_cast<double>(_pictureWidth);
}

double Picture::cropHeightRatio()
{
    return static_cast<double>(_cropPictureHeight) / static_cast<double>(_pictureHeight);
}

void Picture::initializeFaces(int minWidth, int maxWidth, int minHeight, int maxHeight)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapTextureID);

    // FACE_RIGHT and FACE_LEFT
    QImage imageFaceRight(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_ARGB32);
    QImage imageFaceLeft(maxWidth - minWidth, maxHeight - minHeight, QImage::Format_ARGB32);
    for (int x = minWidth; x < maxWidth; x++)
    {
        for (int y = minHeight; y < maxHeight; y++)
        {
            imageFaceRight.setPixel(x - minWidth, y - minHeight,
                    _textureImage.pixel((maxWidth - 1), y));
            imageFaceLeft.setPixel(x - minWidth, y - minHeight, _textureImage.pixel(minWidth, y));
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
                    _textureImage.pixel((minWidth + maxWidth - 1) - x, minHeight));
            imageFaceBottom.setPixel(x - minWidth, y - minHeight,
                    _textureImage.pixel((minWidth + maxWidth - 1) - x, (maxHeight - 1)));
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
                    _textureImage.pixel((minWidth + maxWidth - 1) - x, y));
            imageFaceBack.setPixel(x - minWidth, y - minHeight, _textureImage.pixel(x, y));
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
    double nw = -_displayWidth * widthRatio() * cropWidthRatio();
    double pw = +_displayWidth * widthRatio() * cropWidthRatio();
    double nh = -_displayHeight * heightRatio() * cropHeightRatio();
    double ph = +_displayHeight * heightRatio() * cropHeightRatio();
    double nd = -_displayDepth;
    double pd = +_displayDepth;

    if (nbPictures > 1)
    {
        double subDepth = (_displayDepth * 2.0) / static_cast<double>(nbPictures);
        double subSpacing = _displaySpacing * subDepth;
        nd = -_displayDepth + subDepth * itPicture + (subSpacing / 2.0);
        pd = -_displayDepth + subDepth * (itPicture + 1) - (subSpacing / 2.0);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapTextureID);
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
