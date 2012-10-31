#include<QApplication>
#include"GLWidget.h"
#include"Window.h"

/*
***************************************************************
*
*  Main starting point for the application.  Creates the main
*  QApplication  
*
***************************************************************
*/
int main (int argc, char **argv) 
{
   QApplication app (argc, argv);

   Window* w = new Window();
   w->resize(1000, 750);
   w->show(); 

   return app.exec();
}