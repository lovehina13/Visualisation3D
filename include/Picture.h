//==============================================================================
// Name        : Picture.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/03/2018)
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

    void setDisplayWidth(float size);
    void setDisplayHeight(float size);
    void setDisplayDepth(float size);
    void setDisplaySpacing(float size);

    void initialize(QString fileName);
    void paint(int itPicture, int nbPictures);
    void finalize();

protected:
    float widthRatio();
    float heightRatio();
    float cropWidthRatio();
    float cropHeightRatio();

    void initializeFaces(int minWidth, int maxWidth, int minHeight, int maxHeight);
    void drawPicture(int itPicture, int nbPictures);

private:
    int pictureWidth;
    int pictureHeight;
    int cropPictureWidth;
    int cropPictureHeight;
    float displayWidth;
    float displayHeight;
    float displayDepth;
    float displaySpacing;
    QImage textureImage;
    GLuint cubeMapTextureID;

    enum pictureFaces
    {
        FACE_RIGHT, FACE_LEFT, FACE_TOP, FACE_BOTTOM, FACE_FRONT, FACE_BACK
    };
};

#endif /* PICTURE_H */
