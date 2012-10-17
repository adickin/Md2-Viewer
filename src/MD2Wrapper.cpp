
#include "MD2Wrapper.h"

MD2Wrapper::MD2Wrapper()
{
   md2Reader_ = new MD2();
}

MD2Wrapper::~MD2Wrapper()
{
   delete md2Reader_;
}

bool MD2Wrapper::loadModelFromFile(QString& fileName)
{
   bool success = md2Reader_->LoadModel(fileName.toAscii().constData());
   determineDimensions();
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
   fprintf(stderr, "%d, %d, %d, %d, %d, %d\n",md2ImageDimensions_.minX, md2ImageDimensions_.maxX
                                             ,md2ImageDimensions_.minY, md2ImageDimensions_.maxY
                                             ,md2ImageDimensions_.minZ, md2ImageDimensions_.maxZ);
}