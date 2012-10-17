#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include "GLWidget.h"
#include <GL/glut.h>

GLWidget::GLWidget(QWidget *parent) : QGLWidget (parent) 
{
   setMinimumSize(500, 500);
   scale = 1;
}

GLWidget::~GLWidget() { }

void GLWidget::initializeGL() 
{
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHT0);

   glClearColor(0.0,0.0,0.0,0.0);
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
   gluLookAt(md2Reader_.dimensions().maxZ * 3, 0, 0,
            0, 0, 0,
            0, 0, 1);
    
   drawWireFrame();

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
