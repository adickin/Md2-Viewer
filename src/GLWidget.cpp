#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include "GLWidget.h"
#include <GL/glut.h>

GLWidget::GLWidget(QWidget *parent) : QGLWidget (parent) 
{
    scale = 1;
    QString fileName("./models-5/stormtrooper/stormtrooperweapon.md2");
    bool loadSuccessful = md2Reader_.loadModelFromFile(fileName);

    emit fileLoadSuccess(loadSuccessful);
}

GLWidget::~GLWidget() { }

void GLWidget::initializeGL() 
{
    glClearColor(1.0,1.0,1.0,1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
}

void GLWidget::resizeGL(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    this->width = width;
    this->height = height;

    glViewport(0,0,width, height);

    glOrtho(-10, 10, -10, 10, -20, 20);
    //float ratio;
    // if (width > height) {
    //     ratio = (float)width/(float)height;
    //     glOrtho(-ratio, ratio, -1, 1, -1, 1);
    // } else {
    //     ratio = (float)height/(float)width;
    //     glOrtho(-1, 1, -ratio, ratio, -1, 1);
    // }

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL() 
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
   glLoadIdentity();

   drawWireFrame();
    
   glFlush();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MidButton) {
        close();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    x = event->x();
    y = event->y();

    x = ((x-(width/2.0))/width)*2.0;
    y = ((y-(height/2.0))/height)*2.0;

    updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Q) {
        close();
    }
}

void GLWidget::wheelEvent(QWheelEvent *event) {
    if (event->orientation() == Qt::Vertical) {
        if (event->delta() > 0) scale += 0.1;
        else scale -= 0.1;

        updateGL();
    }
}

void GLWidget::drawWireFrame()
{
   glColor3f(0.0, 0.0, 1.0);

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
