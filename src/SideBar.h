
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

   void setLoadLabelText(const QString& newText);

private:
   Ui::SideBar ui_;
};

#endif