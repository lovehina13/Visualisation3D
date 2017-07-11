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
        QGLFunctions(), width(0), height(0), textureID(0)
{
    // initialize(QString());
}

Picture::~Picture()
{
    finalize();
}

void Picture::initialize(QString fileName)
{
    QImage textureImage = QGLWidget::convertToGLFormat(QImage(fileName));

    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    if (textureImage.bits())
    {
        width = textureImage.width();
        height = textureImage.height();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0,
                GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits());
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
}

void Picture::paint()
{
    glEnable(GL_TEXTURE_2D);

    drawPicture();

    glDisable(GL_TEXTURE_2D);
}

void Picture::finalize()
{
    glDeleteTextures(1, &textureID);
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
    float c = 0.0;
    float n = -8.0;
    float p = +8.0;
    float nw = n * widthRatio();
    float pw = p * widthRatio();
    float nh = n * heightRatio();
    float ph = p * heightRatio();

    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
    glTexCoord2f(n, p); glVertex3f(nw, c, ph);
    glTexCoord2f(n, n); glVertex3f(nw, c, nh);
    glTexCoord2f(p, n); glVertex3f(pw, c, nh);
    glTexCoord2f(p, p); glVertex3f(pw, c, ph);
    glEnd();
}
