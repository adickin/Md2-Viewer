
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QGLWidget>
#include <QString>

#include "BMP.h"

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