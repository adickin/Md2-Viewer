#pragma once
#include <QWidget>
#include <QtGui>
#include "GLWidget.h"
#include "SideBar.h"
#include "ui_MainWindow.h"


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

   Ui::MainWindow ui_;

   SideBar* sideBar_;

   QToolBar* toolBar_;
   
};
