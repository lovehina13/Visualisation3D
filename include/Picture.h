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
    explicit Picture();
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
    int _pictureWidth;
    int _pictureHeight;
    int _cropPictureWidth;
    int _cropPictureHeight;
    double _displayWidth;
    double _displayHeight;
    double _displayDepth;
    double _displaySpacing;
    QImage _textureImage;
    GLuint _cubeMapTextureID;

    enum pictureFaces
    {
        FACE_RIGHT, FACE_LEFT, FACE_TOP, FACE_BOTTOM, FACE_FRONT, FACE_BACK
    };
};

#endif /* PICTURE_H */
