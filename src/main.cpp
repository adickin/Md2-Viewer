#include<QApplication>
#include"GLWidget.h"
#include"Window.h"


int main (int argc, char **argv) 
{
   QApplication app (argc, argv);

   Window* w = new Window();
   w->resize(1000, 750);
   w->show();                   // Show the window

   return app.exec();              // Pass control to QT
}