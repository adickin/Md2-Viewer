/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/
#include <QObject>

#include "MD2Wrapper.h"

class SideBar;

/*
***************************************************************
*
*  Contains all functions related to the camera changes. 
*
***************************************************************
*/
class ViewChanger : public QObject
{
   Q_OBJECT
public:
   ViewChanger(SideBar* sideBar);
   ~ViewChanger();

   void setViewPosition();
   void setDirectionZValue(float value);

   void setPerspective(int windowWidth, int windowHeight);
   void setParallel(Dimensions modelDimensions);

   struct Values
   {
      float xValue;
      float yValue;
      float zValue;
   };

public slots:
   void updateViewLocationOfCamera();
   void updateViewDirectionOfCamera();
   void updateViewOrientationOfCamera();
   void resetView();
   
signals:
   void redraw();

private:
   SideBar* sideBar_;

   Values viewLocationValues_;
   Values viewDirectionValues_;
   Values viewOrientationValues_;
};