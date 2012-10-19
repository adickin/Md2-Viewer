
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtGui>
#include "GLWidget.h"
#include "SideBar.h"

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

signals:
   void md2FileOpened(const QString&);
   void textureFileOpened(const QString&);

private://methods
   void interfaceSetup();
   void setupSignalsAndSlots();

private slots://members
   void openBrowseMd2FileBrowser();
   void openTextureFileBrowser();
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

};

#endif