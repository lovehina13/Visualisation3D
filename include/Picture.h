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
    int pictureWidth;
    int pictureHeight;
    int cropPictureWidth;
    int cropPictureHeight;
    double displayWidth;
    double displayHeight;
    double displayDepth;
    double displaySpacing;
    QImage textureImage;
    GLuint cubeMapTextureID;

    enum pictureFaces
    {
        FACE_RIGHT, FACE_LEFT, FACE_TOP, FACE_BOTTOM, FACE_FRONT, FACE_BACK
    };
};

#endif /* PICTURE_H */
