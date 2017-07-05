//==============================================================================
// Name        : SkyBox.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (DD/MM/YYYY)
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
};

#endif /* SKYBOX_H */
