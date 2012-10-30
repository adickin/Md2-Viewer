
#include <QStringList>

#include "Window.h"
#include "GLWidget.h"
#include "SideBar.h"
#include "AffineTransformer.h"
#include "ViewChanger.h"

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

   sideBar_ = new SideBar(centralWidget_);

   affineTransformations_ = new AffineTransformer(sideBar_);
   viewChanger_ = new ViewChanger(sideBar_);
   glWidget_ = new GLWidget(affineTransformations_, viewChanger_, centralWidget_);
   
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
   connect(sideBar_->ui_.faceNormalsCheckBox, SIGNAL(stateChanged(int)),
            glWidget_, SLOT(showFaceNormals(int)));
   connect(sideBar_->ui_.groundPatCheckBox, SIGNAL(stateChanged(int)),
            glWidget_, SLOT(showGroundSheet(int)));

   connect(quitAction_, SIGNAL(triggered(bool))
         , this, SLOT(exitApplication(bool)));

   //Affine Transformations Tab
      //Scaling
   connect(sideBar_->ui_.xScaleSlider, SIGNAL(valueChanged(int)),
            affineTransformations_, SLOT(updateScalingOnModel()));
   connect(sideBar_->ui_.yScaleSlider, SIGNAL(valueChanged(int)),
            affineTransformations_, SLOT(updateScalingOnModel()));
   connect(sideBar_->ui_.zScaleSlider, SIGNAL(valueChanged(int)),
            affineTransformations_, SLOT(updateScalingOnModel()));
   connect(sideBar_->ui_.allScaleSlider, SIGNAL(valueChanged(int)),
            affineTransformations_, SLOT(updateScalingOnModel()));

      //Translations
   connect(sideBar_->ui_.xTranslationSlider, SIGNAL(valueChanged(int)),
            affineTransformations_, SLOT(updateTranslationOnModel()));
   connect(sideBar_->ui_.yTranslationSlider, SIGNAL(valueChanged(int)),
            affineTransformations_, SLOT(updateTranslationOnModel()));
   connect(sideBar_->ui_.zTranslationSlider, SIGNAL(valueChanged(int)),
            affineTransformations_, SLOT(updateTranslationOnModel()));
   connect(sideBar_->ui_.allTranslationSlider, SIGNAL(valueChanged(int)),
            affineTransformations_, SLOT(updateTranslationOnModel()));

   connect(affineTransformations_, SIGNAL(redraw()), glWidget_, SLOT(updateGL()));
   connect(sideBar_->ui_.resetAllButtonTransformation, SIGNAL(released()),
            affineTransformations_, SLOT(resetTransformations()));

   //View Location
   connect(sideBar_->ui_.xLocationSlider, SIGNAL(valueChanged(int)),
            viewChanger_, SLOT(updateViewLocationOfCamera()));
   connect(sideBar_->ui_.yLocationSlider, SIGNAL(valueChanged(int)),
            viewChanger_, SLOT(updateViewLocationOfCamera()));
   connect(sideBar_->ui_.zLocationSlider, SIGNAL(valueChanged(int)),
            viewChanger_, SLOT(updateViewLocationOfCamera()));

   //View Direction
   connect(sideBar_->ui_.xDirectionSlider, SIGNAL(valueChanged(int)),
            viewChanger_, SLOT(updateViewDirectionOfCamera()));
   connect(sideBar_->ui_.yDirectionSlider, SIGNAL(valueChanged(int)),
            viewChanger_, SLOT(updateViewDirectionOfCamera()));
   connect(sideBar_->ui_.zDirectionSlider, SIGNAL(valueChanged(int)),
            viewChanger_, SLOT(updateViewDirectionOfCamera()));

   //View Orientation
   connect(sideBar_->ui_.xOrientationSlider, SIGNAL(valueChanged(int)),
            viewChanger_, SLOT(updateViewOrientationOfCamera()));
   connect(sideBar_->ui_.yOrientationSlider, SIGNAL(valueChanged(int)),
            viewChanger_, SLOT(updateViewOrientationOfCamera()));
   connect(sideBar_->ui_.zOrientationSlider, SIGNAL(valueChanged(int)),
            viewChanger_, SLOT(updateViewOrientationOfCamera()));

   connect(viewChanger_, SIGNAL(redraw()), glWidget_, SLOT(updateGL()));
   connect(sideBar_->ui_.resetAllButtonView, SIGNAL(released()),
            viewChanger_, SLOT(resetView()));



   connect(sideBar_->ui_.projectionComboBox, SIGNAL(currentIndexChanged(const QString&)),
      glWidget_, SLOT(setProjectionType(const QString&)));
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