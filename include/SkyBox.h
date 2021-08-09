//==============================================================================
// Name        : SkyBox.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.3.0 (09/08/2021)
// Description : Header file of the SkyBox class
//==============================================================================

#ifndef SKYBOX_H
#define SKYBOX_H

#include <QGLFunctions>

class SkyBox : public QGLFunctions
{
public:
    SkyBox();
    virtual ~SkyBox();

    void initialize();
    void paint();
    void finalize();

protected:
    void drawSkyBox();

private:
    enum SkyBoxFace
    {
        FACE_RIGHT, FACE_LEFT, FACE_TOP, FACE_BOTTOM, FACE_FRONT, FACE_BACK
    };

    GLuint _cubeMapTextureID { 0 };
};

#endif /* SKYBOX_H */
