/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtGui>
#include "GLWidget.h"

class SideBar;
class AffineTransformer;
class ViewChanger;
class QGLWidget;

/*
***************************************************************
*
*  Main window of the application, sets up all the UI elements
*  as well as the glWidget_.  Sets up all neccasary signals
*  and slots.
*
***************************************************************
*/
class Window : public QMainWindow {
   Q_OBJECT

public:
   Window(QWidget *parent = NULL);
   ~Window();

public:

signals:
   void modelFileOpened(const QString&);
   void modelTextureFileOpened(const QString&);
   void weaponFileLoaded(const QString&);
   void weaponTextureLoaded(const QString&);

private://methods
   void interfaceSetup();
   void setupSignalsAndSlots();

private slots://members
   void openMd2ModelFileBrowser();
   void openModelTextureFileBrowser();
   void openWeaponFileBrowser();
   void openWeaponTextureFileBrowser();

   void exitApplication(bool exit);

private:

//Menu Bar
   QMenuBar* menuBar_;
   QMenu* fileMenu_;
   QAction* saveAction_;
   QAction* quitAction_;

//Layouts
   QWidget* centralWidget_;
   QHBoxLayout* horizontalLayout_;

   GLWidget* glWidget_;
   SideBar* sideBar_;

//Affine Transformations object
   AffineTransformer* affineTransformations_;

   //view changer object
   ViewChanger* viewChanger_;

};

#endif