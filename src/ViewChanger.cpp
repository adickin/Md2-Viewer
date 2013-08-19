#include <QSlider>
#include <QGLWidget>

#include "ViewChanger.h"
#include "SideBar.h"
#include "GL/glut.h"

/*
***************************************************************
*
*  Constructor 
*
***************************************************************
*/
ViewChanger::ViewChanger(SideBar* sideBar)
{
   sideBar_ = sideBar;
   Q_ASSERT(sideBar_ != NULL);

   viewDirectionValues_.xValue = 0;
   viewDirectionValues_.yValue = 0;
   viewDirectionValues_.zValue = 80;

   viewLocationValues_.xValue = 0;
   viewLocationValues_.yValue = 0;
   viewLocationValues_.zValue = 0;

   viewOrientationValues_.xValue = 0;
   viewOrientationValues_.yValue = 1;
   viewOrientationValues_.zValue = 0;
   sideBar_->ui_.yOrientationSlider->setValue((int)viewOrientationValues_.yValue);
}

/*
***************************************************************
*
*  Destructor 
*
***************************************************************
*/
ViewChanger::~ViewChanger()
{
   sideBar_ = NULL;
}

/*
***************************************************************
*
*  Sets the view position by calling gluLookAt. 
*
***************************************************************
*/
void ViewChanger::setViewPosition()
{
   gluLookAt(viewDirectionValues_.xValue, viewDirectionValues_.yValue, viewDirectionValues_.zValue,
             viewLocationValues_.xValue, viewLocationValues_.yValue, viewLocationValues_.zValue,
             viewOrientationValues_.xValue, viewOrientationValues_.yValue, viewOrientationValues_.zValue);
}

/*
***************************************************************
*
*  Sets the z Direction Value to be the size of the model so that
*  it fits nicely. 
*
***************************************************************
*/
void ViewChanger::setDirectionZValue(float value)
{
   viewDirectionValues_.zValue = value;
   sideBar_->ui_.zDirectionSlider->setValue((int)viewDirectionValues_.zValue);
}

/*
***************************************************************
*
*  Sets view to be in perspective mode 
*
***************************************************************
*/
void ViewChanger::setPerspective(int windowWidth, int windowHeight)
{
   gluPerspective(60, (GLfloat)windowWidth/windowHeight, 1.0, 1000.0);
}

/*
***************************************************************
*
*  Sets view to be in parallel mode. 
*
***************************************************************
*/
void ViewChanger::setParallel(Dimensions modelDimensions)
{
   glOrtho(modelDimensions.minX, modelDimensions.maxX
         , modelDimensions.minY, modelDimensions.maxY
         , modelDimensions.minZ, modelDimensions.maxZ);
}

/*
***************************************************************
*
*  Updates the view location of the camera based on what is
*  currently selected in the location sliders
*
***************************************************************
*/
void ViewChanger::updateViewLocationOfCamera()
{
   if(NULL != this->sender())
   {
      QSlider* currentSlider = static_cast<QSlider*>(this->sender());

      if(currentSlider->objectName() == sideBar_->ui_.xLocationSlider->objectName())
      {
         viewLocationValues_.xValue = currentSlider->value();
      }
      else if(currentSlider->objectName() == sideBar_->ui_.yLocationSlider->objectName())
      {
         viewLocationValues_.yValue = currentSlider->value();
      }
      else if(currentSlider->objectName() == sideBar_->ui_.zLocationSlider->objectName())
      {
         viewLocationValues_.zValue = currentSlider->value();
      }
   }
   emit redraw();
}

/*
***************************************************************
*
*  Updates the view direction of the camera based on what is
*  currently selected in the direction sliders
*
***************************************************************
*/
void ViewChanger::updateViewDirectionOfCamera()
{
   if(NULL != this->sender())
   {
      QSlider* currentSlider = static_cast<QSlider*>(this->sender());

      if(currentSlider->objectName() == sideBar_->ui_.xDirectionSlider->objectName())
      {
         viewDirectionValues_.xValue = currentSlider->value();
      }
      else if(currentSlider->objectName() == sideBar_->ui_.yDirectionSlider->objectName())
      {
         viewDirectionValues_.yValue = currentSlider->value();
      }
      else if(currentSlider->objectName() == sideBar_->ui_.zDirectionSlider->objectName())
      {
         viewDirectionValues_.zValue = currentSlider->value();
      }
   }
   emit redraw();
}

/*
***************************************************************
*
*  Updates the view orientation of the camera based on what is
*  currently selected in the orientation sliders
*
***************************************************************
*/
void ViewChanger::updateViewOrientationOfCamera()
{
   if(NULL != this->sender())
   {
      QSlider* currentSlider = static_cast<QSlider*>(this->sender());

      if(currentSlider->objectName() == sideBar_->ui_.xOrientationSlider->objectName())
      {
         viewOrientationValues_.xValue = currentSlider->value();
      }
      else if(currentSlider->objectName() == sideBar_->ui_.yOrientationSlider->objectName())
      {
         viewOrientationValues_.yValue = currentSlider->value();
      }
      else if(currentSlider->objectName() == sideBar_->ui_.zOrientationSlider->objectName())
      {
         viewOrientationValues_.zValue = currentSlider->value();
      }
   }
   emit redraw();
}

/*
***************************************************************
*
*  Resets the view 
*
***************************************************************
*/
void ViewChanger::resetView()
{
   viewDirectionValues_.xValue = 0;
   viewDirectionValues_.yValue = 0;
   viewDirectionValues_.zValue = 80;

   sideBar_->ui_.xDirectionSlider->setValue((int)viewDirectionValues_.xValue);
   sideBar_->ui_.yDirectionSlider->setValue((int)viewDirectionValues_.yValue);
   sideBar_->ui_.zDirectionSlider->setValue((int)viewDirectionValues_.zValue);

   viewLocationValues_.xValue = 0;
   viewLocationValues_.yValue = 0;
   viewLocationValues_.zValue = 0;

   sideBar_->ui_.xLocationSlider->setValue((int)viewLocationValues_.xValue);
   sideBar_->ui_.yLocationSlider->setValue((int)viewLocationValues_.yValue);
   sideBar_->ui_.zLocationSlider->setValue((int)viewLocationValues_.zValue);

   viewOrientationValues_.xValue = 0;
   viewOrientationValues_.yValue = 1;
   viewOrientationValues_.zValue = 0;

   sideBar_->ui_.xOrientationSlider->setValue((int)viewOrientationValues_.xValue);
   sideBar_->ui_.yOrientationSlider->setValue((int)viewOrientationValues_.yValue);
   sideBar_->ui_.zOrientationSlider->setValue((int)viewOrientationValues_.zValue);

}
