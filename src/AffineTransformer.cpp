#include <QSlider>
#include <QGLWidget>

#include "AffineTransformer.h"
#include "SideBar.h"
#include "math.h"
#include "MathVector.h"


/*
***************************************************************
*
* Constructor  
*
***************************************************************
*/
AffineTransformer::AffineTransformer(SideBar* sideBar)
{
   sideBar_ = sideBar;
   Q_ASSERT(sideBar_ != NULL);

   scalingValues_.xValue = 1;
   scalingValues_.yValue = 1;
   scalingValues_.zValue = 1;

   translationValues_.xValue = 0;
   translationValues_.yValue = 0;
   translationValues_.zValue = 0;

   matrix_ = new GLfloat[16];

}

/*
***************************************************************
*
*  Destructor 
*
***************************************************************
*/
AffineTransformer::~AffineTransformer()
{
   sideBar_ = NULL;
}

/*
***************************************************************
*
*  Scales the model!
*
*  Since the md2 files load in with the model on its side
*
*  x = z;
*  y = x;
*  z = y;  
*
*  This is so that scaling changes look normal to the user.
*
***************************************************************
*/
void AffineTransformer::performScalingOnModel()
{
   glScaled(scalingValues_.zValue, scalingValues_.xValue, scalingValues_.yValue);
}

/*
***************************************************************
*
*  Translates the model!
*
*  Since the md2 files load in with the model on its side
*
*  x = z;
*  y = x;
*  z = y;  
*
*  This is so that scaling changes look normal to the user.
*
***************************************************************
*/
void AffineTransformer::performTranslationOnModel()
{
   glTranslatef(translationValues_.zValue, translationValues_.xValue, translationValues_.yValue);
}

/*
***************************************************************
*
*  Sets the values in scalingValues_ according to whats the current
*  value in each slider
*
***************************************************************
*/
void AffineTransformer::updateScalingOnModel()
{
   if(NULL != this->sender())
   {
      QSlider* currentSlider = static_cast<QSlider*>(this->sender());

      if(currentSlider->objectName() == sideBar_->ui_.xScaleSlider->objectName())
      {
         scalingValues_.xValue = currentSlider->value()/50.0;
      }
      else if(currentSlider->objectName() == sideBar_->ui_.yScaleSlider->objectName())
      {
         scalingValues_.yValue = currentSlider->value()/50.0;
      }
      else if(currentSlider->objectName() == sideBar_->ui_.zScaleSlider->objectName())
      {
         scalingValues_.zValue = currentSlider->value()/50.0;
      }
      else if(currentSlider->objectName() == sideBar_->ui_.allScaleSlider->objectName())
      {
         scalingValues_.xValue = currentSlider->value()/50.0;
         scalingValues_.yValue = currentSlider->value()/50.0;
         scalingValues_.zValue = currentSlider->value()/50.0;
         sideBar_->ui_.xScaleSlider->setValue(currentSlider->value());
         sideBar_->ui_.yScaleSlider->setValue(currentSlider->value());
         sideBar_->ui_.zScaleSlider->setValue(currentSlider->value());
      }
   }
   emit redraw();
}

/*
***************************************************************
*
*  Sets the values in the transformationValues_ according to whats
*  the current value in each slider  
*
***************************************************************
*/
void AffineTransformer::updateTranslationOnModel()
{
   if(NULL != this->sender())
   {
      QSlider* currentSlider = static_cast<QSlider*>(this->sender());

      if(currentSlider->objectName() == sideBar_->ui_.xTranslationSlider->objectName())
      {
         translationValues_.xValue = currentSlider->value();
      }
      else if(currentSlider->objectName() == sideBar_->ui_.yTranslationSlider->objectName())
      {
         translationValues_.yValue = currentSlider->value();
      }
      else if(currentSlider->objectName() == sideBar_->ui_.zTranslationSlider->objectName())
      {
         translationValues_.zValue = currentSlider->value();
      }
      else if(currentSlider->objectName() == sideBar_->ui_.allTranslationSlider->objectName())
      {
         translationValues_.xValue = currentSlider->value();
         translationValues_.yValue = currentSlider->value();
         translationValues_.zValue = currentSlider->value();
         sideBar_->ui_.xTranslationSlider->setValue(currentSlider->value());
         sideBar_->ui_.yTranslationSlider->setValue(currentSlider->value());
         sideBar_->ui_.zTranslationSlider->setValue(currentSlider->value());
      }
   }
   emit redraw();
}

/*
***************************************************************
*
*  Allows the user to use the scroll wheel on their mouse to
*  scale the model  
*
***************************************************************
*/
void AffineTransformer::rollBallMoved(int valueChange)
{
   float change = valueChange/50.0;
   scalingValues_.xValue += change;
   scalingValues_.yValue += change;
   scalingValues_.zValue += change;

   //ensure model cant go bigger than double size
   if(2 < scalingValues_.xValue)
   {
      scalingValues_.xValue = 2;
   }
   if(2 < scalingValues_.yValue)
   {
      scalingValues_.yValue = 2;
   }
   if(2 < scalingValues_.zValue)
   {
      scalingValues_.zValue = 2;
   }

   //ensure model cant go smaller than 0
   if(0 > scalingValues_.xValue)
   {
      scalingValues_.xValue = 0;
   }
   if(0 > scalingValues_.yValue)
   {
      scalingValues_.yValue = 0;
   }
   if(0 > scalingValues_.zValue)
   {
      scalingValues_.zValue = 0;
   }

   sideBar_->ui_.xScaleSlider->setValue((int)(scalingValues_.xValue*50.0));
   sideBar_->ui_.yScaleSlider->setValue((int)(scalingValues_.yValue*50.0));
   sideBar_->ui_.zScaleSlider->setValue((int)(scalingValues_.zValue*50.0));
   emit redraw();
}

/*
***************************************************************
*
*  Resets all trasnformations done on the model 
*
***************************************************************
*/
void AffineTransformer::resetTransformations()
{
   scalingValues_.xValue = 1;
   scalingValues_.yValue = 1;
   scalingValues_.zValue = 1;

   sideBar_->ui_.xScaleSlider->setValue((int)(scalingValues_.xValue*50.0));
   sideBar_->ui_.yScaleSlider->setValue((int)(scalingValues_.yValue*50.0));
   sideBar_->ui_.zScaleSlider->setValue((int)(scalingValues_.zValue*50.0));

   translationValues_.xValue = 0;
   translationValues_.yValue = 0;
   translationValues_.zValue = 0;

   sideBar_->ui_.xTranslationSlider->setValue((int)translationValues_.xValue);
   sideBar_->ui_.yTranslationSlider->setValue((int)translationValues_.yValue);
   sideBar_->ui_.zTranslationSlider->setValue((int)translationValues_.zValue);

   glPushMatrix();
      glLoadIdentity();
      glGetFloatv(GL_MODELVIEW_MATRIX, matrix_);
   glPopMatrix();

   emit redraw();
}

/*
***************************************************************
*
*  Sets the width/height of the current GLWidget. 
*
***************************************************************
*/
void AffineTransformer::setWidthAndHeight(int width, int height)
{
   width_ = width;
   height_ = height;
}

/*
***************************************************************
*
*  Finds the trackpoint for the trackball rotation  
*
***************************************************************
*/
void AffineTransformer::findTrackPoint(int x, int y, double& sphereX, double& sphereY, double& sphereZ)
{
   sphereX = ((double)x/(double)width_) * 2.0 - 1.0;
   sphereY = ((double)y/(double)height_) * 2.0 - 1.0;

   double sqr = sphereX*sphereX + sphereY*sphereY;
   if(sqr > 1.0)
   {
      sphereZ = 0.0;
   }
   else
   {
      sphereZ = sqrt(1 - sqr);
   }
}

/*
***************************************************************
*
*  Called for a mouse press event
*
***************************************************************
*/
void AffineTransformer::mousePressEvent(QMouseEvent* event)
{
   findTrackPoint(event->x(), event->y(), oldX_, oldY_, oldZ_);
}

/*
***************************************************************
*
*  Called for a mouse move event 
*
***************************************************************
*/
void AffineTransformer::mouseMoveEvent(QMouseEvent* event)
{
   double newX, newY, newZ;
   findTrackPoint(event->x(), event->y(), newX, newY, newZ);

   // find cross product
   double cX = newY * oldZ_ - oldY_ * newZ;
   double cY = newX * oldZ_ - oldX_ * newZ;
   double cZ = newX * oldY_ - oldX_ * newY;
   double A = cX * cX + cY * cY + cZ * cZ;

   // find the angle
   double theta = asin ( A ) * 180.0 / M_PI; // convert to radians

   // ignore regions outside our trackball
   if (oldZ_ == 0.0 || newZ == 0.0)
   {
      theta = 0.0;
   }

   // save the old matrix so we don't mess anythin gup
   glPushMatrix();
   glLoadIdentity();

   // our newly calculated rotation
   glRotatef(theta*10.0, cZ, cX, cY); // * 10 as rotation is small otherwise

   // let OpenGL do our matrix multiplication for us
   glMultMatrixf(matrix_);
   glGetFloatv(GL_MODELVIEW_MATRIX, matrix_);

   // return transformations to their old value
   glPopMatrix();

   // update old values
   findTrackPoint(event->x(), event->y(), oldX_, oldY_, oldZ_);

   // request a redraw
   emit redraw();
}

/*
***************************************************************
*
*  Returns the current rotation matrix 
*
***************************************************************
*/
GLfloat* AffineTransformer::matrix()
{
   static bool happened = false;
   if(!happened)
   {
      glPushMatrix();
         glLoadIdentity();
         glGetFloatv(GL_MODELVIEW_MATRIX, matrix_);
      glPopMatrix();
      happened = true;
   }
   return matrix_;
}
