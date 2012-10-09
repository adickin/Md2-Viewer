/********************************************************************************
** Form generated from reading UI file 'SideBar.ui'
**
** Created: Tue Oct 9 11:53:00 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEBAR_H
#define UI_SIDEBAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabWidget
{
public:
    QWidget *wModelTab;
    QListView *listView;
    QPushButton *pushButton;
    QWidget *wTransformationTab;

    void setupUi(QTabWidget *TabWidget)
    {
        if (TabWidget->objectName().isEmpty())
            TabWidget->setObjectName(QString::fromUtf8("TabWidget"));
        TabWidget->resize(400, 300);
        wModelTab = new QWidget();
        wModelTab->setObjectName(QString::fromUtf8("wModelTab"));
        listView = new QListView(wModelTab);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(10, 10, 256, 192));
        pushButton = new QPushButton(wModelTab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 220, 102, 27));
        TabWidget->addTab(wModelTab, QString());
        wTransformationTab = new QWidget();
        wTransformationTab->setObjectName(QString::fromUtf8("wTransformationTab"));
        TabWidget->addTab(wTransformationTab, QString());

        retranslateUi(TabWidget);

        TabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TabWidget);
    } // setupUi

    void retranslateUi(QTabWidget *TabWidget)
    {
        TabWidget->setWindowTitle(QApplication::translate("TabWidget", "TabWidget", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("TabWidget", "Open", 0, QApplication::UnicodeUTF8));
        TabWidget->setTabText(TabWidget->indexOf(wModelTab), QApplication::translate("TabWidget", "Models", 0, QApplication::UnicodeUTF8));
        TabWidget->setTabText(TabWidget->indexOf(wTransformationTab), QApplication::translate("TabWidget", "Transformations", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TabWidget: public Ui_TabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEBAR_H
