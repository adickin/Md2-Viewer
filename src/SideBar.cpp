#include "SideBar.h"

SideBar::SideBar(QWidget* parent)
:QWidget(parent)
{
   ui_.setupUi(this);
}

SideBar::~SideBar()
{

}

void SideBar::setLoadLabelText(const QString& newText)
{
   ui_.wFileLoadLabel->setText(newText);
}