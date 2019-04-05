//==============================================================================
// Name        : SkyBox.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.1 (05/04/2019)
// Description : Header file of the SkyBox class
//==============================================================================

#ifndef SKYBOX_H
#define SKYBOX_H

#include <QGLFunctions>

class SkyBox : public QGLFunctions
{
public:
    explicit SkyBox();
    virtual ~SkyBox();

    void initialize();
    void paint();
    void finalize();

protected:
    void drawSkyBox();

private:
    GLuint cubeMapTextureID;

    enum skyBoxFaces
    {
        FACE_RIGHT, FACE_LEFT, FACE_TOP, FACE_BOTTOM, FACE_FRONT, FACE_BACK
    };
};

#endif /* SKYBOX_H */
