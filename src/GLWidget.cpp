#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include <GL/glut.h>

#include "GLWidget.h"
#include "BMP.h"
#include "MathVector.h"
#include "math.h"
#include "AffineTransformer.h"
#include "ViewChanger.h"

/*
***************************************************************
*
* Constructor for GLWidget  
*
***************************************************************
*/
GLWidget::GLWidget(AffineTransformer* transformer, ViewChanger* viewChanger, QWidget *parent) 
   :QGLWidget (parent) 
   ,displayMode_(DrawingDefines::WIREFRAME)
   ,weaponLoaded_(false)
   ,textureLoadedForMd2Model_(false)
   ,textureLoadedForWeapon_(false)
   ,drawVertexNormals_(false)
   ,drawFaceNormals_(false)
   ,drawGroundSheet_(true)
   ,transformer_(transformer)
   ,viewChanger_(viewChanger)
   ,projectionSelected_(QString("Perspective"))
{
   texManager_ = new TextureManager();
   setMinimumSize(500, 500);
}

/*
***************************************************************
*
* Destructor  
*
***************************************************************
*/
GLWidget::~GLWidget() 
{
   delete texManager_;
}

/*
***************************************************************
*
* Called once when the GLWidget is created.
*
***************************************************************
*/
void GLWidget::initializeGL() 
{
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_RESCALE_NORMAL);

   glClearColor(0.3,0.6,0.5,0.5);
   enableLighting();
}

/*
***************************************************************
*
* Enables GL lighting effects  
*
***************************************************************
*/
void GLWidget::enableLighting()
{
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   GLfloat position[] = {5, 5, 5, 1};
   glLightfv(GL_LIGHT0, GL_POSITION, position);
}

/*
***************************************************************
*
*  Called everytime the GL window is resized.  
*
***************************************************************
*/
void GLWidget::resizeGL(int width, int height) 
{
   windowWidth_ = width;
   windowHeight_ = height;
   transformer_->setWidthAndHeight(width, height);
   glViewport(0,0,width, height);
}

/*
***************************************************************
*
*  Function called everytime updateGL() is called.  Draws the
*  models with textures, as well as vertex's, ground sheets if 
*  enabled.  
*
***************************************************************
*/
void GLWidget::paintGL() 
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   if(QString("Perspective") == projectionSelected_)
   {
      viewChanger_->setPerspective(windowWidth_, windowHeight_);
   }
   else if(QString("Parallel") == projectionSelected_)
   {
      viewChanger_->setParallel(modelReader_.dimensions());
   }

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   if(QString("Perspective") == projectionSelected_)
   {
      viewChanger_->setViewPosition();
   }

   glPushMatrix();

   if(drawGroundSheet_)
   {
      glPushMatrix();
         drawGroundSheet();
      glPopMatrix();
   }
   
   //Rotate the model to be upright.
   glRotatef(-90.0, 0.0, 0.0, 1.0);
   glRotatef(-90.0, 0.0, 1.0, 0.0);

   transformer_->performScalingOnModel();
   transformer_->performTranslationOnModel();
   glMultMatrixf(transformer_->matrix());
   drawModel();

   if(drawVertexNormals_)
   {  
      glPushMatrix();
         drawModelVertexNormals();
      glPopMatrix();
   }
   if(drawFaceNormals_)
   {
      glPushMatrix();
         drawModelFaceNormals();
      glPopMatrix();
   }
   glPopMatrix();


   glFlush();
}

/*
***************************************************************
*
*  Called whenever a mouse button is clicked  
*
***************************************************************
*/
void GLWidget::mousePressEvent(QMouseEvent *event) 
{
   if (event->button() == Qt::LeftButton) 
   {
      transformer_->mousePressEvent(event);
   }
}

/*
***************************************************************
*
*  Called whenever a mouse moves on top of the widget  
*
***************************************************************
*/
void GLWidget::mouseMoveEvent(QMouseEvent *event) 
{
   transformer_->mouseMoveEvent(event);

   updateGL();
}

/*
***************************************************************
*
*   Called whenever a keyboard key is pressed
*
***************************************************************
*/
void GLWidget::keyPressEvent(QKeyEvent *event) 
{
   if (event->key() == Qt::Key_Q) 
   {
      close();
   }
}

/*
***************************************************************
*
*  Called whever the mouse wheel is moved forward or back,
*  performs uniform scaling on the model.  
*
***************************************************************
*/
void GLWidget::wheelEvent(QWheelEvent *event) 
{
   if (event->orientation() == Qt::Vertical) 
   {
      if (event->delta() > 0)
      {
         int valueChange = 1;
         transformer_->rollBallMoved(valueChange);
      }
      else
      {
         int valueChange = -1;
         transformer_->rollBallMoved(valueChange);
      }

      updateGL();
   }
}

/*
***************************************************************
*
*  Opens a MD2 file for a model so that they can be drawn  
*
***************************************************************
*/
void GLWidget::openModelFile(QString& filePath)
{
   modelReader_.loadModelFromFile(filePath);
   textureLoadedForMd2Model_ = false;
   weaponLoaded_ = false;
   viewChanger_->setDirectionZValue((modelReader_.dimensions().maxZ+fabs(modelReader_.dimensions().minZ))*2);
}

/*
***************************************************************
*
*  Opens a texture file for a model, sets the modelTexture to
*  bind while drawing the model
*
***************************************************************
*/
void GLWidget::openModelTextureFile(QString& filePath)
{     
   glDeleteTextures(1, &modelTexture_);
   modelTexture_ = texManager_->loadTextureFromFile(filePath);
   textureLoadedForMd2Model_ = true;
}

/*
***************************************************************
*
* Opens a MD2 file for a weapon model so taht it can be drawn  
*
***************************************************************
*/
void GLWidget::openWeaponFile(QString& filePath)
{
   weaponReader_.loadModelFromFile(filePath);
   textureLoadedForWeapon_ = false;
   weaponLoaded_ = true;
}

/*
***************************************************************
*
*  Opens a texture for a weapon model, sets the weaponTexture
*  to bind while drawing the weapon  
*
***************************************************************
*/
void GLWidget::openWeaponTextureFile(QString& filePath)
{     
   glDeleteTextures(1, &weaponTexture_);
   weaponTexture_ = texManager_->loadTextureFromFile(filePath);
   textureLoadedForWeapon_ = true;
}

/*
***************************************************************
*
*  Changes teh display mode between wireframe, flat, or smooth  
*
***************************************************************
*/
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

/*
***************************************************************
*
*  Sets if the vertex normals will be drawn according to the 
*  \a state.  
*
***************************************************************
*/
void GLWidget::showVertexNormals(int state)
{
   drawVertexNormals_ = (state == (int)Qt::Checked);
   updateGL();
}

/*
***************************************************************
*
*  Sets if the face normals will be drawn according to the 
*  \a state.  
*
***************************************************************
*/
void GLWidget::showFaceNormals(int state)
{
   drawFaceNormals_ = (state == (int)Qt::Checked);
   updateGL();
}

/*
***************************************************************
*
*  Sets if the ground sheet will be drawn according to the 
*  \a state.  
*
***************************************************************
*/
void GLWidget::showGroundSheet(int state)
{
   drawGroundSheet_ = (state == (int)Qt::Checked);
   updateGL();
}

/*
***************************************************************
*
*  Sets the projection type based on \a selection 
*
***************************************************************
*/
void GLWidget::setProjectionType(const QString& selection)
{
   projectionSelected_ = selection;
   updateGL();
}

/*
***************************************************************
*
*  Draws the ground the model stands on  
*
***************************************************************
*/
void GLWidget::drawGroundSheet()
{
   QString groundTexturePath("./src/ground.bmp");
   groundTexture_ = texManager_->loadTextureFromFile(groundTexturePath);
   glEnable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBindTexture(GL_TEXTURE_2D, groundTexture_);
   glColor3f(1, 1, 1);

   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-25, modelReader_.dimensions().minZ-1, -25 );

   glTexCoord2f(1.0, 0.0);
   glVertex3f(25, modelReader_.dimensions().minZ-1, -25);

   glTexCoord2f(1.0, 1.0);
   glVertex3f(25, modelReader_.dimensions().minZ-1, 25);

   glTexCoord2f(0.0, 1.0);
   glVertex3f(-25, modelReader_.dimensions().minZ-1, 25);

   glEnd();

   glDisable(GL_TEXTURE_2D);
   glEnable(GL_LIGHTING);
}

/*
***************************************************************
*
*  Draws the model based on the opened MD2 model file 
*
***************************************************************
*/
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

      //Point One.
      MathVector* vector;
      if(displayMode_== DrawingDefines::FLAT_SHADING)
      {
         vector = modelReader_.faceNormals()->at(currentTriangle);
      }
      else
      {
         vector = modelReader_.vertexNormals()->at(indexOne);
      }
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureOne.u/modelReader_.skinWidth(),
                  (float) textureOne.v/modelReader_.skinHeight());
      glVertex3f(vertexOne.x, vertexOne.y, vertexOne.z);

      //Point Two
      if(displayMode_== DrawingDefines::FLAT_SHADING)
      {
         vector = modelReader_.faceNormals()->at(currentTriangle);
      }
      else
      {
         vector = modelReader_.vertexNormals()->at(indexTwo);
      }
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureTwo.u/modelReader_.skinWidth(),
               (float) textureTwo.v/modelReader_.skinHeight());
      glVertex3f(vertexTwo.x, vertexTwo.y, vertexTwo.z);

      //Point Three
      if(displayMode_== DrawingDefines::FLAT_SHADING)
      {
         vector = modelReader_.faceNormals()->at(currentTriangle);
      }
      else
      {
         vector = modelReader_.vertexNormals()->at(indexThree);
      }
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

/*
***************************************************************
*
*  Draws the weapon model that is currently opened in the weaponReader_ 
*
***************************************************************
*/
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

      //Point One.
      MathVector* vector;
      if(displayMode_== DrawingDefines::FLAT_SHADING)
      {
         vector = weaponReader_.faceNormals()->at(currentTriangle);
      }
      else
      {
         vector = weaponReader_.vertexNormals()->at(indexOne);
      }
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureOne.u/weaponReader_.skinWidth(),
                  (float) textureOne.v/weaponReader_.skinHeight());
      glVertex3f(vertexOne.x, vertexOne.y, vertexOne.z);

      //Point Two
      if(displayMode_== DrawingDefines::FLAT_SHADING)
      {
         vector = weaponReader_.faceNormals()->at(currentTriangle);
      }
      else
      {
         vector = weaponReader_.vertexNormals()->at(indexTwo);
      }
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureTwo.u/weaponReader_.skinWidth(),
               (float) textureTwo.v/weaponReader_.skinHeight());
      glVertex3f(vertexTwo.x, vertexTwo.y, vertexTwo.z);

      //Point Three
      if(displayMode_== DrawingDefines::FLAT_SHADING)
      {
         vector = weaponReader_.faceNormals()->at(currentTriangle);
      }
      else
      {
         vector = weaponReader_.vertexNormals()->at(indexThree);
      }
      vector = weaponReader_.vertexNormals()->at(indexThree);
      glNormal3f(vector->x(), vector->y(), vector->z());
      glTexCoord2f((float) textureThree.u/weaponReader_.skinWidth(),
               (float) textureThree.v/weaponReader_.skinHeight());
      glVertex3f(vertexThree.x, vertexThree.y, vertexThree.z);
   }
   glEnd();

   glDisable(GL_TEXTURE_2D);
}

/*
***************************************************************
*
* Draws the vertex normals on the model  
*
***************************************************************
*/
void GLWidget::drawModelVertexNormals()
{
   glDisable(GL_LIGHTING);
   glColor3f(1.0, 0.0, 0.0);
   for(int i = 0; i < modelReader_.numberOfVertices(); i++)
   {
      MathVector* vertexNormal = modelReader_.vertexNormals()->at(i);
      VertexCoordinate vertexCoordinate = modelReader_.retrieveVertexCoordinatesAt(i);

      glBegin(GL_LINES);
      glVertex3f(vertexCoordinate.x, vertexCoordinate.y,
         vertexCoordinate.z);
      glVertex3f((vertexNormal->x()*2)+vertexCoordinate.x, (vertexNormal->y()*2)+vertexCoordinate.y,
         (vertexNormal->z()*2)+vertexCoordinate.z);
      glEnd();
   }
   glEnable(GL_LIGHTING);
   if(weaponLoaded_)
   {
      drawWeaponVertexNormals();
   }
}

/*
***************************************************************
*
* Draws the vertex normals on the weapon model  
*
***************************************************************
*/
void GLWidget::drawWeaponVertexNormals()
{
   glDisable(GL_LIGHTING);
   glColor3f(1.0, 0.0, 0.0);
   for(int i = 0; i < weaponReader_.numberOfVertices(); i++)
   {
      MathVector* vertexNormal = weaponReader_.vertexNormals()->at(i);
      VertexCoordinate vertexCoordinate = weaponReader_.retrieveVertexCoordinatesAt(i);

      glBegin(GL_LINES);
      glVertex3f(vertexCoordinate.x, vertexCoordinate.y,
         vertexCoordinate.z);
      glVertex3f((vertexNormal->x()*2)+vertexCoordinate.x, (vertexNormal->y()*2)+vertexCoordinate.y,
         (vertexNormal->z()*2)+vertexCoordinate.z);
      glEnd();
   }
   glEnable(GL_LIGHTING);
}

/*
***************************************************************
*
*  Draws the face normals on the model 
*
***************************************************************
*/
void GLWidget::drawModelFaceNormals()
{
   glDisable(GL_LIGHTING);
   glColor3f(0.0, 0.0, 1.0);

   for(int i = 0; i < modelReader_.numberOfTriangles(); i++)
   {
      int indexOne = 0;
      int indexTwo = 0;
      int indexThree = 0;
      modelReader_.retrieveTriangleVertexIndicies(i, &indexOne,
                                              &indexTwo, &indexThree);

      MathVector* faceNormals = modelReader_.faceNormals()->at(i);


      VertexCoordinate vertexOne = modelReader_.retrieveVertexCoordinatesAt(indexOne);
      VertexCoordinate vertexTwo = modelReader_.retrieveVertexCoordinatesAt(indexTwo);
      VertexCoordinate vertexThree = modelReader_.retrieveVertexCoordinatesAt(indexThree);

      VertexCoordinate middleOfTriangle;
      middleOfTriangle.x = ((vertexOne.x + vertexTwo.x + vertexThree.x)/3);
      middleOfTriangle.y = ((vertexOne.y + vertexTwo.y + vertexThree.y)/3);
      middleOfTriangle.z = ((vertexOne.z + vertexTwo.z + vertexThree.z)/3);

      glBegin(GL_LINES);
      glVertex3f(middleOfTriangle.x, middleOfTriangle.y,
         middleOfTriangle.z);
      glVertex3f((faceNormals->x()*2)+middleOfTriangle.x, (faceNormals->y()*2)+middleOfTriangle.y,
         (faceNormals->z()*2)+middleOfTriangle.z);
      glEnd();
   }
   glEnable(GL_LIGHTING);

   if(weaponLoaded_)
   {
      drawWeaponFaceNormals();
   }
}

/*
***************************************************************
*
* Draws the face normals on the weapon model  
*
***************************************************************
*/
void GLWidget::drawWeaponFaceNormals()
{
   glDisable(GL_LIGHTING);
   glColor3f(0.0, 0.0, 1.0);
   for(int i = 0; i < weaponReader_.numberOfTriangles(); i++)
   {
      int indexOne = 0;
      int indexTwo = 0;
      int indexThree = 0;
      weaponReader_.retrieveTriangleVertexIndicies(i, &indexOne,
                                              &indexTwo, &indexThree);

      MathVector* faceNormals = weaponReader_.faceNormals()->at(i);


      VertexCoordinate vertexOne = weaponReader_.retrieveVertexCoordinatesAt(indexOne);
      VertexCoordinate vertexTwo = weaponReader_.retrieveVertexCoordinatesAt(indexTwo);
      VertexCoordinate vertexThree = weaponReader_.retrieveVertexCoordinatesAt(indexThree);

      VertexCoordinate middleOfTriangle;
      middleOfTriangle.x = ((vertexOne.x + vertexTwo.x + vertexThree.x)/3);
      middleOfTriangle.y = ((vertexOne.y + vertexTwo.y + vertexThree.y)/3);
      middleOfTriangle.z = ((vertexOne.z + vertexTwo.z + vertexThree.z)/3);

      glBegin(GL_LINES);
      glVertex3f(middleOfTriangle.x, middleOfTriangle.y,
         middleOfTriangle.z);
      glVertex3f((faceNormals->x()*2)+middleOfTriangle.x, (faceNormals->y()*2)+middleOfTriangle.y,
         (faceNormals->z()*2)+middleOfTriangle.z);
      glEnd();
   }
   glEnable(GL_LIGHTING);
}
