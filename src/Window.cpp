#include "Window.h"

Window::Window(QWidget *parent) : QMainWindow(parent) 
{
   mainWindow_.setupUi(this);

   widget = new GLWidget(this);              // Initialize the GL Widget
   setCentralWidget(widget);                 // This is the main part of the interface, so set it as the central widget of the window
   widget->setFocus();                       // Set focus to capture keyboard and mouse events
   
   toolBar_ = new QToolBar();

   addToolBar(Qt::LeftToolBarArea, toolBar_);
   
   tabWidget_ = new QTabWidget();
   sideBar_.setupUi(tabWidget_);

   toolBar_->addWidget(tabWidget_);
   //mainWindow_.wToolBar->addWidget(tabWidget_);

   // statusBar = new QStatusBar(this);            // Create a status bar
   // statusBar->showMessage("Test");              // Set a default message that is displayed on the status bar at startup
   // // Connect the GL widget's 'showMessage' signal to the status bar's 'showMessage' function so that a message will be displayed whenever the GL widget sends the signal
   // connect(widget, SIGNAL(showMessage(QString)), statusBar, SLOT(showMessage(QString)));
   // setStatusBar(statusBar);                  // Set the window's status bar to be the one we just created

   // menuBar = new QMenuBar();                 // Create a new menu bar
   // fileMenu = new QMenu("&File", this);         // Create a new menu called "File" the '&' in "&File" automatically creates a shortcut to the menu (ALT+F)
   // // Add an action called "Quit" to the menu. It calls the 'close' function on the window when activated, and has the shortcut (CTRL+Q)
   // fileMenu->addAction("&Quit", this, SLOT(close()), QKeySequence("CTRL+Q"));
   // menuBar->addMenu(fileMenu);                  // Put the file menu on the menu bar
   // setMenuBar(menuBar);                   // Set the window's menu bar to be the one we just created

   // // Create a toolbar with the name "Toolbar". This name appears in the automatically generated context menu that appears when you right click on part of the window
   // toolBar = addToolBar("Toolbar");
   // // Adds an action to the toolbar, that performs the given function (i.e. 'close'). If no icon is given, the text "Test" will appear on the toolbar, otherwise, a button with the icon will appear
   // toolBar->addAction(QIcon("icon.png"), "Test", this, SLOT(close()));

   // frame_ = new QFrame();
   // sideBar_ = new Ui::SideBar();
   // sideBar_->setupUi(frame_);
   

   // dock = new QDockWidget("Dock 1", this);         // Create three new dock widgets. These are movable panels that can be placed around the edges of the central widget
   // dock2 = new QDockWidget("Dock 2", this);     
   // dock3 = new QDockWidget("Dock 3", this);
   // addDockWidget(Qt::RightDockWidgetArea, dock);   // Place two dock widgets on the right side of the window
   // addDockWidget(Qt::RightDockWidgetArea, dock2);
   // addDockWidget(Qt::LeftDockWidgetArea, dock3);   // Place the last on the left side
   // // Docks 1 & 2 will be places on top of one another, with a tab to switch between them. Without this function call, they would instead appear one above the other.
   // tabifyDockWidget(dock, dock2);

   // button = new QPushButton("Press This!");     // Create three push buttons. These are currently not connected to anything. see the 'connect' function as in the status bar for reference
   // button2 = new QPushButton("And This!");
   // button3 = new QPushButton("Not This!");

   // QFrame* frame1 = new QFrame();               // A QFrame is a widget that can hold a layout of other widgets
   // //QVBoxLayout* layout = new QVBoxLayout();      // A vbox layout can arrange widgets in a vertical column
   // //QHBoxLayout* layout = new QHBoxLayout();      // An hbox layout can arrange widgets in a horizontal row
   // QGridLayout* layout = new QGridLayout();     // A grid layout can arrange widgets in a grid
   // frame1->setLayout(layout);                // Attach the layout to the frame
   // layout->addWidget(button, 0, 0);          // Add one button to 0,0 in the grid layout. HBox and VBox layouts to not take the coordinate arguments
   // layout->addWidget(button2, 1, 0, 1, 2);         // Add one button to 1,0 in the grid, and make it 1 row high and 2 columns wide
   // layout->addWidget(button3, 0, 1);            // Add the last button to 0,1 in the grid
   // dock->setWidget(frame1);                  // Finally, set the frame as the dock's widget
   // // Frames are very useful. You could also use a frame as your central widget if you want more than one widget to appear in the center of the window
   // // Other QObjects, such as QScrollAreas and QToolBoxes can be used in a similar fashion 
   
   setWindowTitle("Hello QT");                  // Set the title of the window to be "Hello QT"
}

Window::~Window() { }
