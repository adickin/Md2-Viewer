
#include <QString>

#include "Window.h"

Window::Window(QWidget *parent) 
:QMainWindow(parent) 
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

   //Menu Bar
   menuBar_ = new QMenuBar(this);
   menuBar_->setGeometry(QRect(0, 0, 810, 26));
   fileMenu_ = new QMenu(menuBar_);
   fileMenu_->setTitle(QString("File"));
   setMenuBar(menuBar_);

   saveAction_ = new QAction(this);
   saveAction_->setText(QString("Save"));
   quitAction_ = new QAction(this);
   quitAction_->setText(QString("Quit"));
   menuBar_->addAction(fileMenu_->menuAction());
   fileMenu_->addAction(saveAction_);
   fileMenu_->addAction(quitAction_);

   centralWidget_ = new QWidget(this);
   horizontalLayout_ = new QHBoxLayout(centralWidget_);

   glWidget_ = new GLWidget(centralWidget_);
   sideBar_ = new SideBar(centralWidget_);
   
   horizontalLayout_->addWidget(sideBar_);
   horizontalLayout_->addWidget(glWidget_);
   setCentralWidget(centralWidget_);


//temporary todo
   QString fileName("/work/assignment2/models-5/stormtrooper/stormtrooper.md2");
   glWidget_->openMd2File(fileName);
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
   connect(sideBar_->md2LoadButton(), SIGNAL(released()), this, SLOT(openBrowseMd2FileBrowser()));
   connect(quitAction_, SIGNAL(triggered(bool)), this, SLOT(exitApplication(bool)));
}

void Window::postSuccessMessageToScreen(bool success)
{

}

void Window::openBrowseMd2FileBrowser()
{
   QString fileName = QFileDialog::getOpenFileName(this, QString("selectMd2File"), QString("./"), QString("Images (*.md2 *.MD2"));
   glWidget_->openMd2File(fileName);
}

void Window::exitApplication(bool exit)
{
   QApplication::exit(exit);
}