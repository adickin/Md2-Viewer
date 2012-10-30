/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/

#include <QSlider>
#include <QGLWidget>

#include "AffineTransformer.h"
#include "SideBar.h"


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
}

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
