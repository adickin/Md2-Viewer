/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/
#include <QObject>

struct Values
{
   float xValue;
   float yValue;
   float zValue;
};

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

public slots:
   void updateScalingOnModel();
   void updateTranslationOnModel();

signals:
   void redraw();

private:
   SideBar* sideBar_;

   Values translationValues_;
   Values scalingValues_;
};