#pragma once
#include <QWidget>
#include <QtGui>
#include "GLWidget.h"
#include "ui_MainWindow.h"
#include "ui_SideBar.h"

class Window : public QMainWindow {
   Q_OBJECT

public:
   Window(QWidget *parent = NULL);
   ~Window();

public slots:

private slots:

private:
   GLWidget* widget;

   QMenuBar* menuBar;
   QMenu* fileMenu;

   QStatusBar* statusBar;

   QToolBar* toolBar;

   QFrame* frame_;
   Ui::MainWindow mainWindow_;

   QTabWidget* tabWidget_;
   Ui::TabWidget sideBar_;

   QToolBar* toolBar_;
   
   // QDockWidget* dock;
   // QDockWidget* dock2;
   // QDockWidget* dock3;

   // QPushButton* button;
   // QPushButton* button2;
   // QPushButton* button3;
};
