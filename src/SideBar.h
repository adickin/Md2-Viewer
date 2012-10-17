
#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QString>
#include "ui_SideBar.h"

class SideBar : public QWidget
{
   Q_OBJECT

public:
   SideBar( QWidget* parent = NULL);
   ~SideBar();

   void setCurrentMd2FileLabel(const QString& newText);
   QPushButton* md2LoadButton() const;

private:
   Ui::SideBar ui_;
};

#endif