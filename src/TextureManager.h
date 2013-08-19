#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QGLWidget>
#include <QString>

#include "BMP.h"

/*
***************************************************************
*
*  Class that manages textures. Wraps around loading a BMP image
*  as well as the pcx.h file.  
*
***************************************************************
*/
class TextureManager
{

public:
   TextureManager();
   ~TextureManager();

   GLuint loadTextureFromFile(const QString& fileName);

private:
   BMPImg bmpImageReader_;
};

#endif