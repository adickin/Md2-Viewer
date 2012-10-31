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
#include <QList>

//assignment
#include "md2.h"
#include "DrawingDefs.h"
#include "MathVector.h"

class MathVector;
using namespace DrawingDefines;

struct Dimensions
{
   int minX;
   int maxX;
   int minY;
   int maxY;
   int minZ;
   int maxZ;
};

/*
***************************************************************
*
*  Wrapper around the provided md2 reader that is much more
*  human readable.  
*
***************************************************************
*/
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
   Dimensions dimensions();
   QList<MathVector*>* faceNormals();
   QList<MathVector*>* vertexNormals();

   VertexCoordinate retrieveVertexCoordinatesAt(const int index);
   TextureCoordinate retrieveTextureCoordinateAt(const int index);
   void retrieveTriangleVertexIndicies(const int index, int* indexOne, 
                                       int* indexTwo, int* indexThree);
   void retrieveTriangleTextureIndicies(const int index, int* x, int* y, int* z);

private:
   void determineDimensions();
   void determineFaceNormals();
   void determineVertexNormals();
   Dimensions md2ImageDimensions_;
   QList<MathVector*> faceNormals_;
   QList<MathVector*> vertexNormals_;
   MD2* md2Reader_; 
};

#endif
