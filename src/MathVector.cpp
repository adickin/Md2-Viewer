/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/
#include "MathVector.h"
#include "math.h"

/*
***************************************************************
*
* constructor  
*
***************************************************************
*/
MathVector::MathVector(float x, float y, float z)
:isUnitVector_(false)
,x_(x)
,y_(y)
,z_(z)
{

}

/*
***************************************************************
*
* Creates a vector from two coordinate points, Vertex one is always
* minused from vertex two.  
*
***************************************************************
*/
MathVector::MathVector(VertexCoordinate one, VertexCoordinate two)
:isUnitVector_(false)
{
   x_ = two.x - one.x;
   y_ = two.y - one.y;
   z_ = two.z - one.z;
}

/*
***************************************************************
*
*  destructor 
*
***************************************************************
*/
MathVector::~MathVector()
{
   //does nothing
}

/*
***************************************************************
*
*  Performs a cross product with this vector and \a vector and loads
*  the result into this. 
*
***************************************************************
*/
void MathVector::crossProduct(const MathVector* vector)
{
   float tempX = ((y_ * vector->z_) - (z_ * vector->y_));
   float tempY = ((z_ * vector->x_) - (x_ * vector->z_));
   float tempZ = ((x_ * vector->y_) - (y_ * vector->x_));

   x_ = tempX;
   y_ = tempY;
   z_ = tempZ;
}

/*
***************************************************************
*
*  Normalizes a vector so that its magnitude is 1.  
*
***************************************************************
*/
void MathVector::normalizeVector()
{
   float magnitude = sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));

   x_ = x_/magnitude;
   y_ = y_/magnitude;
   z_ = z_/magnitude;
   isUnitVector_ = true;
}

float MathVector::x() const
{
   return x_;
}

float MathVector::y() const
{
   return y_;
}

float MathVector::z() const
{
   return z_;
}

void MathVector::setX(float x)
{
   x_ = x;
}

void MathVector::setY(float y)
{
   y_ = y;
}

void MathVector::setZ(float z)
{
   z_ = z;
}
