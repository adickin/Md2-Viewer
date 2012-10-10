#include<QApplication>
#include"GLWidget.h"
#include"Window.h"


int main (int argc, char **argv) {
    QApplication app (argc, argv);     // Create an instance of QApplication

    Window* w = new Window();       // Create an instance of Window
    w->resize(800, 500);            // Set the window to 500x500
    w->show();                   // Show the window

    return app.exec();              // Pass control to QT
}