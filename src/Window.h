
#ifndef WINDOW_H
#define WINDOW_H

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

private slots://members
   void exitApplication(bool exit);

private:

   GLWidget* glWidget_;
   QToolBar* toolBar_;
   Ui::MainWindow ui_;
   SideBar* sideBar_;

};

#endif