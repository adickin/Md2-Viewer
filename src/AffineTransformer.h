/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/
#include <QObject>
#include <QMouseEvent>
#include <QGLWidget>



class SideBar;

/*
***************************************************************
*
*  Class that performs all of teh affine transformations  
*
***************************************************************
*/
class AffineTransformer : public QObject
{
   Q_OBJECT
public:
   AffineTransformer(SideBar* sideBar);
   ~AffineTransformer();

   void performScalingOnModel();
   void performTranslationOnModel();
   void rollBallMoved(int valueChange);
   void setWidthAndHeight(int width, int height);

   void findTrackPoint(int x, int y, double& sphereX, double& sphereY, double& sphereZ);

   void mousePressEvent(QMouseEvent* event);
   void mouseMoveEvent(QMouseEvent* event);

   GLfloat* matrix();

   struct Values
   {
      float xValue;
      float yValue;
      float zValue;
   };

public slots:
   void updateScalingOnModel();
   void updateTranslationOnModel();
   void resetTransformations();

signals:
   void redraw();

private:
   SideBar* sideBar_;

   Values translationValues_;
   Values scalingValues_;

   int width_;
   int height_;
   double oldX_;
   double oldY_;
   double oldZ_;

   GLfloat* matrix_;
};