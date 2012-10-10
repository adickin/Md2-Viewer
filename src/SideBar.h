
#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include "ui_SideBar.h"

class SideBar : public QWidget
{
   Q_OBJECT

public:
	SideBar( QWidget* parent = NULL);
	~SideBar();

private:
   Ui::SideBar ui_;
};

#endif