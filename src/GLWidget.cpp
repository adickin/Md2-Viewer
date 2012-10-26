#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include "GLWidget.h"
#include <GL/glut.h>
#include "BMP.h"
#include "MathVector.h"

GLWidget::GLWidget(QWidget *parent) 
   :QGLWidget (parent) 
   ,displayMode_(DrawingDefines::WIREFRAME)
   ,textureLoadedForMd2Model_(false)
{
   texManager_ = new TextureManager();
   setMinimumSize(500, 500);
   scale = 1;
}

GLWidget::~GLWidget() { }

void GLWidget::initializeGL() 
{
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_RESCALE_NORMAL);
   //glEnable(GL_LIGHT0);
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
   openTextureFile(fileName2);
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


   //glPopMatrix();

   gluLookAt(0, 0, md2Reader_.dimensions().maxZ * 3,
            0, 0, 0,
            0, 1, 0);
   glScaled(scale,scale,scale);
    
   glPushMatrix();
   //Rotate the model to be upright.
   glRotatef(-90.0, 0.0, 0.0, 1.0);
   glRotatef(-90.0, 0.0, 1.0, 0.0);

   //glPushMatrix();
   drawModel();
   drawVertexNormals();
   glPopMatrix();
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
   textureLoadedForMd2Model_ = false;

   emit fileLoadSuccess(loadSuccessful);
}

void GLWidget::openTextureFile(QString& filePath)
{     
      texture_ = texManager_->loadTextureFromFile(filePath);
      textureLoadedForMd2Model_ = true;
      makeCurrent();
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

   updateGL();
}

void GLWidget::drawModel()
{
   switch(displayMode_)
   {
      case DrawingDefines::WIREFRAME:
      {
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         break;
      }
      case DrawingDefines::FLAT_SHADING:
      {
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glShadeModel(GL_FLAT);
         break;
      }
      case DrawingDefines::SMOOTH_SHADING:
      {
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glShadeModel(GL_SMOOTH);
         break;
      }
   }

   if(textureLoadedForMd2Model_)
   {
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texture_);
   }
   else
   {
      glColor3f(0.0, 1.0, 0.0);
   }

   glBegin(GL_TRIANGLES);

   for(int currentTriangle = 0; 
      currentTriangle < md2Reader_.numberOfTriangles(); currentTriangle++)
   {
      int indexOne = 0;
      int indexTwo = 0;
      int indexThree = 0;
      md2Reader_.retrieveTriangleVertexIndicies(currentTriangle, &indexOne,
                                              &indexTwo, &indexThree);

      int texOne = 0;
      int texTwo = 0;
      int texThree = 0;
      md2Reader_.retrieveTriangleTextureIndicies(currentTriangle, &texOne,
                                              &texTwo, &texThree);

      VertexCoordinate vertexOne = md2Reader_.retrieveVertexCoordinatesAt(indexOne);
      VertexCoordinate vertexTwo = md2Reader_.retrieveVertexCoordinatesAt(indexTwo);
      VertexCoordinate vertexThree = md2Reader_.retrieveVertexCoordinatesAt(indexThree);

      TextureCoordinate textureOne = md2Reader_.retrieveTextureCoordinateAt(texOne);
      TextureCoordinate textureTwo = md2Reader_.retrieveTextureCoordinateAt(texTwo);
      TextureCoordinate textureThree = md2Reader_.retrieveTextureCoordinateAt(texThree);

      MathVector* vector = md2Reader_.vertexNormals()->at(indexOne);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureOne.u/md2Reader_.skinWidth(),
                  (float) textureOne.v/md2Reader_.skinHeight());
      glVertex3f(vertexOne.x, vertexOne.y, vertexOne.z);

      vector = md2Reader_.vertexNormals()->at(indexTwo);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureTwo.u/md2Reader_.skinWidth(),
               (float) textureTwo.v/md2Reader_.skinHeight());
      glVertex3f(vertexTwo.x, vertexTwo.y, vertexTwo.z);

      vector = md2Reader_.vertexNormals()->at(indexThree);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureThree.u/md2Reader_.skinWidth(),
               (float) textureThree.v/md2Reader_.skinHeight());
      glVertex3f(vertexThree.x, vertexThree.y, vertexThree.z);
   }
   glEnd();

   glDisable(GL_TEXTURE_2D);
}

void GLWidget::drawVertexNormals()
{
   //glEnable(GL_TEXTURE_2D);
   glColor3f(1.0, 0.0, 0.0);
   for(int i = 0; i < md2Reader_.numberOfVertices(); i++)
   {
      MathVector* vertexNormal = md2Reader_.vertexNormals()->at(i);
      VertexCoordinate vertexCoordinate = md2Reader_.retrieveVertexCoordinatesAt(i);

      glBegin(GL_LINE);

      //fprintf(stderr, "normal %f, vertexcoord %f\n", vertexNormal->x(), vertexCoordinate.x);
      //fprintf(stderr, "%f, %f, %f,\n", vertexNormal->x()*vertexCoordinate.x,
      //   vertexNormal->y()*vertexCoordinate.y,vertexNormal->z()*vertexCoordinate.z);
      glVertex3f(vertexCoordinate.x, vertexCoordinate.y,
         vertexNormal->z());
      glVertex3f((vertexNormal->x())+vertexCoordinate.x, (vertexNormal->y())+vertexCoordinate.y,
         (vertexNormal->z())+vertexCoordinate.z);

      glEnd();

   }

   //

   glDisable(GL_TEXTURE_2D);
}
