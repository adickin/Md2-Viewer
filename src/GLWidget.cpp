#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include "GLWidget.h"
#include <GL/glut.h>
#include "BMP.h"

GLWidget::GLWidget(QWidget *parent) 
   :QGLWidget (parent) 
   ,displayMode_(DrawingDefines::TEXTURE)
{
   setMinimumSize(500, 500);
   scale = 1;
}

GLWidget::~GLWidget() { }

void GLWidget::initializeGL() 
{
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_LIGHT0);
   glShadeModel(GL_SMOOTH);
   glClearColor(0.0,0.0,0.0,0.5);

   // glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0);

   // glEnable(GL_COLOR_MATERIAL);
   // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   // GLfloat position[] = {100, 100, 100, 1};
   // glLightfv(GL_LIGHT0, GL_POSITION, position);



   //temporary todo
   QString fileName("/work/assignment2/models-5/sephiroth/sephiroth.md2");
   openMd2File(fileName);

   
   QString fileName2("/work/assignment2/models-5/sephiroth/sephiroth.bmp");
   openTextureFileBMP(fileName2);
}

void GLWidget::resizeGL(int width, int height) 
{
   //glEnable(GL_DEPTH_TEST);
   windowWidth_ = width;
   windowHeight_ = height;
   glViewport(0,0,width, height);
}

void GLWidget::paintGL() 
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);   

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60, (GLfloat)windowWidth_/windowHeight_, 1.0, 1000.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(md2Reader_.dimensions().maxZ * 3, 0, 0,
            0, 0, 0,
            0, 0, 1);
   glScaled(scale,scale,scale);
    
   switch(displayMode_)
   {
      case DrawingDefines::WIREFRAME:
      {
         drawWireFrame();
         break;
      }
      case DrawingDefines::FLAT_SHADING:
      {
         break;
      }
      case DrawingDefines::SMOOTH_SHADING:
      {
         break;
      }
      case DrawingDefines::TEXTURE:
      {
         drawModel();
         break;
      }

   }
   glFlush();
}

void GLWidget::mousePressEvent(QMouseEvent *event) 
{
   if (event->button() == Qt::MidButton) 
   {
      close();
   }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) 
{
   x = event->x();
   y = event->y();

   x = ((x-(windowWidth_/2.0))/windowWidth_)*2.0;
   y = ((y-(windowHeight_/2.0))/windowHeight_)*2.0;

   updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event) 
{
   if (event->key() == Qt::Key_Q) 
   {
      close();
   }
}

void GLWidget::wheelEvent(QWheelEvent *event) 
{
   if (event->orientation() == Qt::Vertical) 
   {
      if (event->delta() > 0) scale += 0.1;
      else scale -= 0.1;

      updateGL();
   }
}

void GLWidget::openMd2File(QString& filePath)
{
   bool loadSuccessful = md2Reader_.loadModelFromFile(filePath);
   resizeGL(windowWidth_, windowHeight_);
   emit fileLoadSuccess(loadSuccessful);
}

void GLWidget::openTextureFileBMP(QString& filePath)
{

   int loadSuccessful = bmpImageReader_.Load(filePath.toAscii().data());

   if(IMG_OK == loadSuccessful)
   {

      glGenTextures(1, &texture_);

      glBindTexture(GL_TEXTURE_2D, texture_);

      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Linear Filtering
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
      glTexParameteri (GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
      glHint (GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);


      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmpImageReader_.GetWidth(), bmpImageReader_.GetHeight()
         , GL_BGR, GL_UNSIGNED_BYTE, bmpImageReader_.GetImg() );
   }
}

void GLWidget::changeDisplayMode(const QString& newMode)
{
   if(DrawingDefines::WIREFRAME_STRING == newMode)
   {
      displayMode_ = DrawingDefines::WIREFRAME;
   }
   else if(DrawingDefines::FLAT_SHADING_STRING == newMode)
   {
      displayMode_ = DrawingDefines::FLAT_SHADING;
   }
   else if(DrawingDefines::SMOOTH_SHADING_STRING == newMode)
   {
      displayMode_ = DrawingDefines::SMOOTH_SHADING;
   }
   else if(DrawingDefines::TEXTURE_STRING == newMode)
   {
      displayMode_ = DrawingDefines::TEXTURE;
   }

   updateGL();
}

void GLWidget::drawWireFrame()
{
   glBindTexture(GL_TEXTURE_2D, 0);
   glColor3f(0.0, 1.0, 0.0);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_TRIANGLES);
   for (int i = 0; i < md2Reader_.numberOfTriangles(); ++i)
   {
      int indexOne = 0;
      int indexTwo = 0;
      int indexThree = 0;
      md2Reader_.retrieveTriangleVertexIndicies(i, &indexOne,
                                              &indexTwo, &indexThree);

      VertexCoordinate vertexOne = md2Reader_.retrieveVertexCoordinatesAt(indexOne);
      VertexCoordinate vertexTwo = md2Reader_.retrieveVertexCoordinatesAt(indexTwo);
      VertexCoordinate vertexThree = md2Reader_.retrieveVertexCoordinatesAt(indexThree);

      glVertex3f(vertexOne.x,
         vertexOne.y,
         vertexOne.z);
      glVertex3f(vertexTwo.x,
         vertexTwo.y,
         vertexTwo.z);
      glVertex3f(vertexThree.x,
         vertexThree.y,
         vertexThree.z);
   }
   glEnd();

}

void GLWidget::drawModel()
{
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   glBindTexture(GL_TEXTURE_2D, texture_);

   for (int i = 0; i < md2Reader_.numberOfTriangles(); ++i)
   {
      glBegin(GL_TRIANGLES);
      int indexOne = 0;
      int indexTwo = 0;
      int indexThree = 0;
      md2Reader_.retrieveTriangleVertexIndicies(i, &indexOne,
                                              &indexTwo, &indexThree);

      int texOne = 0;
      int texTwo = 0;
      int texThree = 0;
      md2Reader_.retrieveTriangleTextureIndicies(i, &texOne,
                                              &texTwo, &texThree);

      VertexCoordinate vertexOne = md2Reader_.retrieveVertexCoordinatesAt(indexOne);
      VertexCoordinate vertexTwo = md2Reader_.retrieveVertexCoordinatesAt(indexTwo);
      VertexCoordinate vertexThree = md2Reader_.retrieveVertexCoordinatesAt(indexThree);

      TextureCoordinate textureOne = md2Reader_.retrieveTextureCoordinateAt(texOne);
      TextureCoordinate textureTwo = md2Reader_.retrieveTextureCoordinateAt(texTwo);
      TextureCoordinate textureThree = md2Reader_.retrieveTextureCoordinateAt(texThree);

      //CALCULATING NORMAL VECTOR HERE BEFORE REFACTORING WHICH IS NEEDED BADLy
      VertexCoordinate u;
      u.x = vertexTwo.x - vertexOne.x;
      u.y = vertexTwo.y - vertexOne.y;
      u.z = vertexTwo.z - vertexOne.z;

      VertexCoordinate v;
      v.x = vertexThree.x - vertexOne.x;
      v.y = vertexThree.y - vertexOne.y;
      v.z = vertexThree.z - vertexOne.z;

      float normalX = (float) ((u.y * v.z) - (u.z * v.y));
      float normalY = (float) ((u.z * v.x) - (u.x * v.z));
      float normalZ = (float) ((u.x * v.y) - (u.y * v.x));
      //END CROSS************************************************************


      glNormal3f(normalX, normalY, normalZ);

      glTexCoord2f((float) textureOne.u/md2Reader_.skinWidth(),
                  (float) textureOne.v/md2Reader_.skinHeight());
      glVertex3f(vertexOne.x, vertexOne.y, vertexOne.z);

      glTexCoord2f((float) textureTwo.u/md2Reader_.skinWidth(),
               (float) textureTwo.v/md2Reader_.skinHeight());
      glVertex3f(vertexTwo.x, vertexTwo.y, vertexTwo.z);

      glTexCoord2f((float) textureThree.u/md2Reader_.skinWidth(),
               (float) textureThree.v/md2Reader_.skinHeight());
      glVertex3f(vertexThree.x, vertexThree.y, vertexThree.z);
      glEnd();
   }

}
