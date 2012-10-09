/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Tue Oct 9 11:59:18 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionQuit;
    QWidget *wCentralWidget;
    QMenuBar *wMenuBar;
    QMenu *menuFile;
    QStatusBar *wStatusBar;
    QToolBar *wToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        wCentralWidget = new QWidget(MainWindow);
        wCentralWidget->setObjectName(QString::fromUtf8("wCentralWidget"));
        MainWindow->setCentralWidget(wCentralWidget);
        wMenuBar = new QMenuBar(MainWindow);
        wMenuBar->setObjectName(QString::fromUtf8("wMenuBar"));
        wMenuBar->setGeometry(QRect(0, 0, 800, 26));
        menuFile = new QMenu(wMenuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(wMenuBar);
        wStatusBar = new QStatusBar(MainWindow);
        wStatusBar->setObjectName(QString::fromUtf8("wStatusBar"));
        MainWindow->setStatusBar(wStatusBar);
        wToolBar = new QToolBar(MainWindow);
        wToolBar->setObjectName(QString::fromUtf8("wToolBar"));
        wToolBar->setAllowedAreas(Qt::LeftToolBarArea);
        MainWindow->addToolBar(Qt::TopToolBarArea, wToolBar);

        wMenuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        wToolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
