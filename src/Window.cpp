
#include <QStringList>

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
   //Opening Tab
   //MODEL
   connect(sideBar_->ui_.md2OpenButton, SIGNAL(released())
         , this, SLOT(openMd2ModelFileBrowser()));
   connect(this, SIGNAL(modelFileOpened(const QString&))
         , sideBar_->ui_.currentMd2File, SLOT(setText(const QString&)));

   connect(sideBar_->ui_.selectTextureButton, SIGNAL(released())
         , this, SLOT(openModelTextureFileBrowser()));
   connect(this, SIGNAL(modelTextureFileOpened(const QString&))
         , sideBar_->ui_.currentTextureLabel, SLOT(setText(const QString&)));

   //WEAPON
   connect(sideBar_->ui_.weaponOpenButton, SIGNAL(released())
         , this, SLOT(openWeaponFileBrowser()));
   connect(this, SIGNAL(weaponFileLoaded(const QString&))
         , sideBar_->ui_.currentWeapon, SLOT(setText(const QString&)));

   connect(sideBar_->ui_.selectWeaponTextureButton, SIGNAL(released())
         , this, SLOT(openWeaponTextureFileBrowser()));
   connect(this, SIGNAL(weaponTextureLoaded(const QString&))
         , sideBar_->ui_.currentWeaponTextureLabel, SLOT(setText(const QString&)));

   //Rendering Tab
   connect(sideBar_->ui_.displayModeComboBox, SIGNAL(currentIndexChanged(const QString&)),
            glWidget_, SLOT(changeDisplayMode(const QString&)));

   connect(sideBar_->ui_.vertexNormalsCheckBox, SIGNAL(stateChanged(int)),
            glWidget_, SLOT(showVertexNormals(int)));

   connect(quitAction_, SIGNAL(triggered(bool))
         , this, SLOT(exitApplication(bool)));
}

void Window::openMd2ModelFileBrowser()
{
   QString fileName = QFileDialog::getOpenFileName(this, QString("selectMd2File")
                     , QString("./"), QString("Models (*.md2 *.MD2"));

   glWidget_->openModelFile(fileName);
   QStringList list = fileName.split(QString("/"));
   emit modelFileOpened(list.at(list.size()-1));
   emit modelTextureFileOpened(QString("NONE"));
   emit weaponFileLoaded(QString("NONE"));
   emit weaponTextureLoaded(QString("NONE"));
}

void Window::openModelTextureFileBrowser()
{
   QString fileName = QFileDialog::getOpenFileName(this, QString("selectTextureFile"), QString("./")
                              , QString("Textures (*.BMP *.bmp *.pcx *.PCX"));

   glWidget_->openModelTextureFile(fileName);
   QStringList list = fileName.split(QString("/"));
   emit modelTextureFileOpened(list.at(list.size()-1));
}

void Window::openWeaponFileBrowser()
{
   QString fileName = QFileDialog::getOpenFileName(this, QString("select Weapon File")
                                 , QString("./"), QString("Models (*.md2 *.MD2"));

   glWidget_->openWeaponFile(fileName);
   QStringList list = fileName.split(QString("/"));
   emit weaponFileLoaded(list.at(list.size()-1));
   emit weaponTextureLoaded(QString("NONE"));
}

void Window::openWeaponTextureFileBrowser()
{
   QString fileName = QFileDialog::getOpenFileName(this, QString("Select Weapon Texture"), QString("./")
                              , QString("Textures (*.BMP *.bmp *.pcx *.PCX"));

   glWidget_->openWeaponTextureFile(fileName);
   QStringList list = fileName.split(QString("/"));
   emit weaponTextureLoaded(list.at(list.size()-1));
}

void Window::exitApplication(bool exit)
{
   QApplication::exit(exit);
}