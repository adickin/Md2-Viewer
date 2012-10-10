#include "Window.h"


Window::Window(QWidget *parent) : QMainWindow(parent) 
{
   ui_.setupUi(this);

   widget = new GLWidget(this);              // Initialize the GL Widget
   setCentralWidget(widget);                 // This is the main part of the interface, so set it as the central widget of the window
   widget->setFocus();                       // Set focus to capture keyboard and mouse events
   
   toolBar_ = new QToolBar(this);

   addToolBar(Qt::LeftToolBarArea, toolBar_);

   sideBar_ = new SideBar();
   sideBar_->setVisible(true);
   toolBar_->addWidget(sideBar_);
   
   setWindowTitle("Model Viewer");                  // Set the title of the window to be "Hello QT"
}

Window::~Window() { }
