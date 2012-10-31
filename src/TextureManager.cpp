/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/

#include "TextureManager.h"
#include <GL/glut.h>
#include "pcx.h"

/*
***************************************************************
*
*  constructor  
*
***************************************************************
*/
TextureManager::TextureManager()
{

}

/*
***************************************************************
*
*  destructor 
*
***************************************************************
*/
TextureManager::~TextureManager()
{

}

/*
***************************************************************
*
* Takes in a filename that is either a bmp file or a PCX file
* and uses the correct loader for the particular filetype.  
*
***************************************************************
*/
GLuint TextureManager::loadTextureFromFile(const QString& fileName)
{
   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Linear Filtering
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
   glTexParameteri (GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
   glHint (GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);

   int loadSuccessful = 0;
   if(fileName.contains(QString("bmp"), Qt::CaseInsensitive))
   {
      loadSuccessful = bmpImageReader_.Load(fileName.toAscii().data());

      if(loadSuccessful == IMG_OK)
      {
         gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmpImageReader_.GetWidth(), bmpImageReader_.GetHeight()
            , GL_BGR, GL_UNSIGNED_BYTE, bmpImageReader_.GetImg() );
      }
   }
   else if(fileName.contains(QString("pcx"), Qt::CaseInsensitive))
   {
      unsigned char* pixels = NULL;
      pixels = new unsigned char[1];
      int width = 0;
      int height = 0;
      bool flip = true;

      loadSuccessful = LoadFilePCX(fileName.toAscii().data(), 
                                    &pixels, &width, &height, flip);

      if(1 == loadSuccessful)
      {
         gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
      }
   }

   return texture;
}


