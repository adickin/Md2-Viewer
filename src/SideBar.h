/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/
#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QString>
#include "ui_SideBar.h"

/*
***************************************************************
*
*  SideBar for the application, seen beside the glwidget.
*  Mainly loads a UI file created in QT Designer  
*
***************************************************************
*/
class SideBar : public QWidget
{
   Q_OBJECT

public:
   SideBar( QWidget* parent = NULL);
   ~SideBar();

   Ui::SideBar ui_;
};

#endif