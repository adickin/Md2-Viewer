
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtGui>
#include "GLWidget.h"

class SideBar;
class AffineTransformer;
class QGLWidget;

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

};

#endif