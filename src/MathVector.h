/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/

#ifndef MATHVECTOR_H
#define MATHVECTOR_H

#include "DrawingDefs.h"
#include "stdio.h"

using namespace DrawingDefines;

/*
***************************************************************
*
*  
*
***************************************************************
*/
class MathVector
{
public:
   MathVector(float x, float y, float z);
   MathVector(VertexCoordinate one, VertexCoordinate two);
   ~MathVector();

   void crossProduct(const MathVector* vector);
   void normalizeVector();

   float x() const;
   float y() const;
   float z() const;

   void setX(float x);
   void setY(float y);
   void setZ(float z);

private:
   bool isUnitVector_;
   float x_;
   float y_;
   float z_;

};

#endif
