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
   ,weaponLoaded_(false)
   ,textureLoadedForMd2Model_(false)
   ,textureLoadedForWeapon_(false)
   ,drawVertexNormals_(false)
   ,drawFaceNormals_(false)
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

   glClearColor(0.0,0.0,0.0,0.5);

   // glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0);

   // glEnable(GL_COLOR_MATERIAL);
   // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   // GLfloat position[] = {100, 100, 100, 1};
   // glLightfv(GL_LIGHT0, GL_POSITION, position);

   //temporary todo
   QString fileName("/work/assignment2/models-5/sephiroth/sephiroth.md2");
   openModelFile(fileName);
   
   QString fileName2("/work/assignment2/models-5/sephiroth/sephiroth.bmp");
   openModelTextureFile(fileName2);
}

void GLWidget::resizeGL(int width, int height) 
{
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

   gluLookAt(0, 0, modelReader_.dimensions().maxZ * 3,
            0, 0, 0,
            0, 1, 0);
   glScaled(scale,scale,scale);
    
   glPushMatrix();
   //Rotate the model to be upright.
   glRotatef(-90.0, 0.0, 0.0, 1.0);
   glRotatef(-90.0, 0.0, 1.0, 0.0);

   drawModel();

   if(drawVertexNormals_)
   {
      drawVertexNormals();
   }
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

void GLWidget::openModelFile(QString& filePath)
{
   modelReader_.loadModelFromFile(filePath);
   textureLoadedForMd2Model_ = false;
   weaponLoaded_ = false;
}

void GLWidget::openModelTextureFile(QString& filePath)
{     
   glDeleteTextures(1, &modelTexture_);
   modelTexture_ = texManager_->loadTextureFromFile(filePath);
   textureLoadedForMd2Model_ = true;
}

void GLWidget::openWeaponFile(QString& filePath)
{
   weaponReader_.loadModelFromFile(filePath);
   textureLoadedForWeapon_ = false;
   weaponLoaded_ = true;
}

void GLWidget::openWeaponTextureFile(QString& filePath)
{     
   glDeleteTextures(1, &weaponTexture_);
   weaponTexture_ = texManager_->loadTextureFromFile(filePath);
   textureLoadedForWeapon_ = true;
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

void GLWidget::showVertexNormals(int state)
{
   drawVertexNormals_ = (state == (int)Qt::Checked);
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
      glBindTexture(GL_TEXTURE_2D, modelTexture_);
   }
   else
   {
      glColor3f(0.0, 1.0, 0.0);
   }

   glBegin(GL_TRIANGLES);

   for(int currentTriangle = 0; 
      currentTriangle < modelReader_.numberOfTriangles(); currentTriangle++)
   {
      int indexOne = 0;
      int indexTwo = 0;
      int indexThree = 0;
      modelReader_.retrieveTriangleVertexIndicies(currentTriangle, &indexOne,
                                              &indexTwo, &indexThree);

      int texOne = 0;
      int texTwo = 0;
      int texThree = 0;
      modelReader_.retrieveTriangleTextureIndicies(currentTriangle, &texOne,
                                              &texTwo, &texThree);

      VertexCoordinate vertexOne = modelReader_.retrieveVertexCoordinatesAt(indexOne);
      VertexCoordinate vertexTwo = modelReader_.retrieveVertexCoordinatesAt(indexTwo);
      VertexCoordinate vertexThree = modelReader_.retrieveVertexCoordinatesAt(indexThree);

      TextureCoordinate textureOne = modelReader_.retrieveTextureCoordinateAt(texOne);
      TextureCoordinate textureTwo = modelReader_.retrieveTextureCoordinateAt(texTwo);
      TextureCoordinate textureThree = modelReader_.retrieveTextureCoordinateAt(texThree);

      MathVector* vector = modelReader_.vertexNormals()->at(indexOne);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureOne.u/modelReader_.skinWidth(),
                  (float) textureOne.v/modelReader_.skinHeight());
      glVertex3f(vertexOne.x, vertexOne.y, vertexOne.z);

      vector = modelReader_.vertexNormals()->at(indexTwo);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureTwo.u/modelReader_.skinWidth(),
               (float) textureTwo.v/modelReader_.skinHeight());
      glVertex3f(vertexTwo.x, vertexTwo.y, vertexTwo.z);

      vector = modelReader_.vertexNormals()->at(indexThree);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureThree.u/modelReader_.skinWidth(),
               (float) textureThree.v/modelReader_.skinHeight());
      glVertex3f(vertexThree.x, vertexThree.y, vertexThree.z);
   }
   glEnd();

   glDisable(GL_TEXTURE_2D);

   if(weaponLoaded_)
   {
      drawWeapon();
   }
}

void GLWidget::drawWeapon()
{
   if(textureLoadedForWeapon_)
   {
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, weaponTexture_);
   }
   else
   {
      glColor3f(1.0, 0.0, 0.0);
   }

   glBegin(GL_TRIANGLES);

   for(int currentTriangle = 0; 
      currentTriangle < weaponReader_.numberOfTriangles(); currentTriangle++)
   {
      int indexOne = 0;
      int indexTwo = 0;
      int indexThree = 0;
      weaponReader_.retrieveTriangleVertexIndicies(currentTriangle, &indexOne,
                                              &indexTwo, &indexThree);

      int texOne = 0;
      int texTwo = 0;
      int texThree = 0;
      weaponReader_.retrieveTriangleTextureIndicies(currentTriangle, &texOne,
                                              &texTwo, &texThree);

      VertexCoordinate vertexOne = weaponReader_.retrieveVertexCoordinatesAt(indexOne);
      VertexCoordinate vertexTwo = weaponReader_.retrieveVertexCoordinatesAt(indexTwo);
      VertexCoordinate vertexThree = weaponReader_.retrieveVertexCoordinatesAt(indexThree);

      TextureCoordinate textureOne = weaponReader_.retrieveTextureCoordinateAt(texOne);
      TextureCoordinate textureTwo = weaponReader_.retrieveTextureCoordinateAt(texTwo);
      TextureCoordinate textureThree = weaponReader_.retrieveTextureCoordinateAt(texThree);

      MathVector* vector = weaponReader_.vertexNormals()->at(indexOne);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureOne.u/weaponReader_.skinWidth(),
                  (float) textureOne.v/weaponReader_.skinHeight());
      glVertex3f(vertexOne.x, vertexOne.y, vertexOne.z);

      vector = weaponReader_.vertexNormals()->at(indexTwo);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureTwo.u/weaponReader_.skinWidth(),
               (float) textureTwo.v/weaponReader_.skinHeight());
      glVertex3f(vertexTwo.x, vertexTwo.y, vertexTwo.z);

      vector = weaponReader_.vertexNormals()->at(indexThree);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureThree.u/weaponReader_.skinWidth(),
               (float) textureThree.v/weaponReader_.skinHeight());
      glVertex3f(vertexThree.x, vertexThree.y, vertexThree.z);
   }
   glEnd();

   glDisable(GL_TEXTURE_2D);
}

void GLWidget::drawVertexNormals()
{
   glColor3f(1.0, 0.0, 0.0);
   for(int i = 0; i < modelReader_.numberOfVertices(); i++)
   {
      MathVector* vertexNormal = modelReader_.vertexNormals()->at(i);
      VertexCoordinate vertexCoordinate = modelReader_.retrieveVertexCoordinatesAt(i);

      glBegin(GL_LINE);
      glVertex3f(vertexCoordinate.x, vertexCoordinate.y,
         vertexCoordinate.z);
      glVertex3f((vertexNormal->x()*2)+vertexCoordinate.x, (vertexNormal->y()*2)+vertexCoordinate.y,
         (vertexNormal->z()*2)+vertexCoordinate.z);
      glEnd();
   }
}
