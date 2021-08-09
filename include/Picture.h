//==============================================================================
// Name        : Picture.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/03/2020)
// Description : Header file of the Picture class
//==============================================================================

#ifndef PICTURE_H
#define PICTURE_H

#include <QGLFunctions>
#include <QImage>
#include <QString>

class Picture : public QGLFunctions
{
public:
    Picture();
    virtual ~Picture();

    void setDisplayWidth(double size);
    void setDisplayHeight(double size);
    void setDisplayDepth(double size);
    void setDisplaySpacing(double size);

    void initialize(QString fileName);
    void paint(int itPicture, int nbPictures);
    void finalize();

protected:
    double widthRatio();
    double heightRatio();
    double cropWidthRatio();
    double cropHeightRatio();

    void initializeFaces(int minWidth, int maxWidth, int minHeight, int maxHeight);
    void drawPicture(int itPicture, int nbPictures);

private:
    enum PictureFace
    {
        FACE_RIGHT, FACE_LEFT, FACE_TOP, FACE_BOTTOM, FACE_FRONT, FACE_BACK
    };

    int _pictureWidth { 0 };
    int _pictureHeight { 0 };
    int _cropPictureWidth { 0 };
    int _cropPictureHeight { 0 };
    double _displayWidth { 0.0 };
    double _displayHeight { 0.0 };
    double _displayDepth { 0.0 };
    double _displaySpacing { 0.0 };
    QImage _textureImage;
    GLuint _cubeMapTextureID { 0 };
};

#endif /* PICTURE_H */
