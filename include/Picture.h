//==============================================================================
// Name        : Picture.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
// Description : Header file of the Picture class
//==============================================================================

#ifndef PICTURE_H
#define PICTURE_H

#include <QGLFunctions>
#include <QString>

class Picture : public QGLFunctions
{
public:
    explicit Picture();
    virtual ~Picture();

    void initialize(QString fileName);
    void paint();
    void finalize();

protected:
    float widthRatio();
    float heightRatio();

    void drawPicture();

private:
    int width;
    int height;
    GLuint textureID;
};

#endif /* PICTURE_H */
