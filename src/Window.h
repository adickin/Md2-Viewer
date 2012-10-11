#pragma once
#include <QWidget>
#include <QtGui>
#include "GLWidget.h"
#include "SideBar.h"
#include "ui_MainWindow.h"

/*
***************************************************************
*
*   
*
***************************************************************
*/
class Window : public QMainWindow {
   Q_OBJECT

public:
   Window(QWidget *parent = NULL);
   ~Window();

public slots:
   void postSuccessMessageToScreen(bool success);

private://methods
   void interfaceSetup();
   void setupSignalsAndSlots();

private://members
   GLWidget* glWidget_;
   QToolBar* toolBar_;
   Ui::MainWindow ui_;
   SideBar* sideBar_;

};
