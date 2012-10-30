/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/
#include <QObject>



class SideBar;

class AffineTransformer : public QObject
{
   Q_OBJECT
public:
   AffineTransformer(SideBar* sideBar);
   ~AffineTransformer();

   void performScalingOnModel();
   void performTranslationOnModel();
   void rollBallMoved(int valueChange);

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
};