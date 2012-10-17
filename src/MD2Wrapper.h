/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/

#ifndef MD2WRAPPER_H
#define MD2WRAPPER_H

//QT
#include <QString>

//assignment
#include "md2.h"

struct VertexCoordinate
{
   float x;
   float y;
   float z;
};

struct TextureCoordinate
{
   float u;
   float v;
};

class MD2Wrapper
{
public:
   MD2Wrapper();
   ~MD2Wrapper();

   bool loadModelFromFile(QString& fileName);
   int numberOfFrames() const;
   int numberOfVertices() const;
   int numberOfTriangles() const;
   int skinWidth() const;
   int skinHeight() const;

   VertexCoordinate retrieveVertexCoordinatesAt(const int index);
   TextureCoordinate retrieveTextureCoordinateAt(const int index);
   void retrieveTriangleVertexIndicies(const int index, int* indexOne, 
                                       int* indexTwo, int* indexThree);
   void retrieveTriangleTextureIndicies(const int index, int* x, int* y, int* z);

private:
   MD2* md2Reader_; 
};

#endif