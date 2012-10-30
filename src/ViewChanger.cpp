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

#include "ViewChanger.h"
#include "SideBar.h"
#include "GL/glut.h"

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

ViewChanger::~ViewChanger()
{
   sideBar_ = NULL;
}

void ViewChanger::setViewPosition()
{
   gluLookAt(viewDirectionValues_.xValue, viewDirectionValues_.yValue, viewDirectionValues_.zValue,
             viewLocationValues_.xValue, viewLocationValues_.yValue, viewLocationValues_.zValue,
             viewOrientationValues_.xValue, viewOrientationValues_.yValue, viewOrientationValues_.zValue);
}

void ViewChanger::setDirectionZValue(float value)
{
   viewDirectionValues_.zValue = value;
   sideBar_->ui_.zDirectionSlider->setValue((int)viewDirectionValues_.zValue);
}

void ViewChanger::setPerspective(int windowWidth, int windowHeight)
{
   gluPerspective(60, (GLfloat)windowWidth/windowHeight, 1.0, 1000.0);
}

void ViewChanger::setParallel(Dimensions modelDimensions)
{
   glOrtho(modelDimensions.minX, modelDimensions.maxX
         , modelDimensions.minY, modelDimensions.maxY
         , modelDimensions.minZ, modelDimensions.maxZ);
}

/*
***************************************************************
*
*  Center  
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
*  EYE  
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
*  view orientation  
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
