
#include "MD2Wrapper.h"
#include "MathVector.h"

MD2Wrapper::MD2Wrapper()
{
   md2Reader_ = new MD2();
   faceNormals_.clear();
   vertexNormals_.clear();
}

MD2Wrapper::~MD2Wrapper()
{
   delete md2Reader_;
   foreach(MathVector* vect, faceNormals_)
   {
      delete vect;
   }
}

bool MD2Wrapper::loadModelFromFile(QString& fileName)
{
   bool success = md2Reader_->LoadModel(fileName.toAscii().constData());
   determineDimensions();
   determineFaceNormals();
   determineVertexNormals();

   return success;
}

int MD2Wrapper::numberOfFrames() const
{
   return md2Reader_->num_frames;
}

int MD2Wrapper::numberOfVertices() const
{
   return md2Reader_->num_xyz;
}

int MD2Wrapper::numberOfTriangles() const
{
   return md2Reader_->num_tris;
}

int MD2Wrapper::skinWidth() const
{
   return md2Reader_->skin_width;
}

int MD2Wrapper::skinHeight() const
{
   return md2Reader_->skin_height;
}

Dimensions MD2Wrapper::dimensions()
{
   return md2ImageDimensions_;
}

QList<MathVector*>* MD2Wrapper::faceNormals()
{
   return &faceNormals_;
}

QList<MathVector*>* MD2Wrapper::vertexNormals()
{
   return &vertexNormals_;
}

VertexCoordinate MD2Wrapper::retrieveVertexCoordinatesAt(const int index)
{
   VertexCoordinate coordinate;
   
   coordinate.x = md2Reader_->m_vertices[index][0];
   coordinate.y = md2Reader_->m_vertices[index][1];
   coordinate.z = md2Reader_->m_vertices[index][2];
   return coordinate;
}

TextureCoordinate MD2Wrapper::retrieveTextureCoordinateAt(const int index)
{
   TextureCoordinate coordinate;

   coordinate.u = md2Reader_->texs[index].u;
   coordinate.v = md2Reader_->texs[index].v;

   return coordinate;
}

void MD2Wrapper::retrieveTriangleVertexIndicies(const int index, int* indexOne,
                                                 int* indexTwo, int* indexThree)
{
   *indexOne = md2Reader_->tris[index].index_xyz[0];
   *indexTwo = md2Reader_->tris[index].index_xyz[1];
   *indexThree = md2Reader_->tris[index].index_xyz[2];
}

void MD2Wrapper::retrieveTriangleTextureIndicies(const int index, int* x, int* y, int* z)
{
   *x = md2Reader_->tris[index].index_st[0];
   *y = md2Reader_->tris[index].index_st[1];
   *z = md2Reader_->tris[index].index_st[2];
}

void MD2Wrapper::determineDimensions()
{
   md2ImageDimensions_.minX = 0;
   md2ImageDimensions_.maxX = 0;
   md2ImageDimensions_.minY = 0;
   md2ImageDimensions_.maxY = 0;
   md2ImageDimensions_.minZ = 0;
   md2ImageDimensions_.maxZ = 0;
   for(int i = 0; i < numberOfVertices(); i++)
   {
      VertexCoordinate vertex = retrieveVertexCoordinatesAt(i);

      if(vertex.x < md2ImageDimensions_.minX)
      {
         md2ImageDimensions_.minX = vertex.x;
      }
      else if(vertex.x > md2ImageDimensions_.maxX)
      {
         md2ImageDimensions_.maxX = vertex.x;
      }

      if(vertex.y < md2ImageDimensions_.minY)
      {
         md2ImageDimensions_.minY = vertex.y;
      }
      else if(vertex.y > md2ImageDimensions_.maxY)
      {
         md2ImageDimensions_.maxY = vertex.y;
      }

      if(vertex.z < md2ImageDimensions_.minZ)
      {
         md2ImageDimensions_.minZ = vertex.z;
      }
      else if(vertex.z > md2ImageDimensions_.maxZ)
      {
         md2ImageDimensions_.maxZ = vertex.z;
      }
   }
}

void MD2Wrapper::determineFaceNormals()
{
   for(int i = 0; i < numberOfTriangles(); ++i)
   {
      int indexOne = 0;
      int indexTwo = 0;
      int indexThree = 0;
      retrieveTriangleVertexIndicies(i, &indexOne,
                                              &indexTwo, &indexThree);

      VertexCoordinate vertexOne = retrieveVertexCoordinatesAt(indexOne);
      VertexCoordinate vertexTwo = retrieveVertexCoordinatesAt(indexTwo);
      VertexCoordinate vertexThree = retrieveVertexCoordinatesAt(indexThree);

      MathVector* vectorOne = new MathVector(vertexTwo, vertexOne);
      MathVector* vectorTwo = new MathVector(vertexThree, vertexOne);

      vectorOne->crossProduct(*vectorTwo);
      vectorOne->normalizeVector();

      faceNormals_.append(vectorOne);
      delete vectorTwo;
   }
}

void MD2Wrapper::determineVertexNormals()
{
   QList<MathVector*> faceNormalForVertexNormalCalculation;
   for(int i = 0; i < numberOfVertices(); ++i)
   {
      VertexCoordinate vertex = retrieveVertexCoordinatesAt(i);

      for(int currentTriangle = 0; currentTriangle < numberOfTriangles(); ++currentTriangle)
      {
         int indexOne = 0;
         int indexTwo = 0;
         int indexThree = 0;
         retrieveTriangleVertexIndicies(i, &indexOne,
                                              &indexTwo, &indexThree);
         
         VertexCoordinate vertexOne = retrieveVertexCoordinatesAt(indexOne);
         VertexCoordinate vertexTwo = retrieveVertexCoordinatesAt(indexTwo);
         VertexCoordinate vertexThree = retrieveVertexCoordinatesAt(indexThree);

         if(vertex.areVertexsEqual(vertexOne) ||
            vertex.areVertexsEqual(vertexTwo) ||
            vertex.areVertexsEqual(vertexThree))
         {
            faceNormalForVertexNormalCalculation.append(faceNormals_.at(currentTriangle));
         }
      }

      MathVector* vertexNormal = new MathVector(0, 0, 0); 
      foreach(MathVector* currentVector, faceNormalForVertexNormalCalculation)
      {
         vertexNormal->setX(vertexNormal->x() + currentVector->x());
         vertexNormal->setY(vertexNormal->y() + currentVector->y());
         vertexNormal->setZ(vertexNormal->z() + currentVector->z());
      }

      vertexNormal->normalizeVector();
      vertexNormals_.append(vertexNormal);
      faceNormalForVertexNormalCalculation.clear();
   }
}
