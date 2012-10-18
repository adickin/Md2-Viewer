#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include "GLWidget.h"
#include <GL/glut.h>
#include "BMP.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget (parent) 
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

}

void GLWidget::resizeGL(int width, int height) 
{
   //glEnable(GL_DEPTH_TEST);
   windowWidth_ = width;
   windowHeight_ = height;
   glViewport(0,0,width, height);

   // glMatrixMode(GL_PROJECTION);
   // glLoadIdentity();
   // gluPerspective(60, (GLfloat)windowWidth_/windowHeight_, 0.1, 10000.0);

   // glMatrixMode(GL_MODELVIEW);
   // glLoadIdentity();
   // gluLookAt(0, 0, -50,
   //             0, 0, 0,
   //             0, 0, 1);
   
   
}

void GLWidget::paintGL() 
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60, (GLfloat)windowWidth_/windowHeight_, 1.0, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(md2Reader_.dimensions().maxZ * 2, 0, 0,
            0, 0, 0,
            0, 0, 1);
    
   drawModel();

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

void GLWidget::drawWireFrame()
{
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
   //glColor3f(0.0, 1.0, 0.0);


   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   //QString fileName("./models-5/sephiroth/sephiroth.bmp");
   QString fileName("./models-5/stormtrooper/Storm.bmp");
   BMPImg image;
   int retVal = image.Load(fileName.toAscii().data());
   if(retVal != IMG_OK)
   {
   }

   unsigned char* imageVector = image.GetImg();

   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Linear Filtering
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
   glTexParameteri (GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
   glHint (GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);

   // glTexImage2D(GL_TEXTURE_2D, 0, 3, image.GetWidth(), image.GetHeight(), 0, GL_RGB,
   //             GL_UNSIGNED_BYTE, imageVector);


   gluBuild2DMipmaps(GL_TEXTURE_2D, 3,image.GetWidth(), image.GetHeight()
         , GL_BGR, GL_UNSIGNED_BYTE, imageVector );

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
