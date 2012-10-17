
#include <QString>

#include "Window.h"

Window::Window(QWidget *parent) : QMainWindow(parent) 
{
   interfaceSetup();
   setupSignalsAndSlots();
}

Window::~Window() 
{
}

/*
***************************************************************
*
*   sets up all items that appear in the GUI.
*
***************************************************************
*/
void Window::interfaceSetup()
{
   setWindowTitle("Model Viewer");

   
   ui_.setupUi(this);

   glWidget_ = new GLWidget(ui_.widget);
   //setCentralWidget(glWidget_);
   glWidget_->setFocus();




   // toolBar_ = new QToolBar(this);
   // sideBar_ = new SideBar();
   // sideBar_->setVisible(true);
   // toolBar_->addWidget(sideBar_);
   // addToolBar(Qt::LeftToolBarArea, toolBar_);
}

/*
***************************************************************
*
*   Sets up all signals and slots for this class.
*
***************************************************************
*/
void Window::setupSignalsAndSlots()
{
   connect(glWidget_, SIGNAL(fileLoadSuccess(bool)), this, SLOT(postSuccessMessageToScreen(bool)));
   connect(ui_.actionQuit, SIGNAL(triggered(bool)), this, SLOT(exitApplication(bool)));
}

void Window::postSuccessMessageToScreen(bool success)
{
   if(success)
   {
      sideBar_->setLoadLabelText(QString("File Loaded Successfully"));
   }
   else


   {
      sideBar_->setLoadLabelText(QString("File Load Error"));  
   }
}

void Window::exitApplication(bool exit)
{
   QApplication::exit(0);
}