#include "SideBar.h"

SideBar::SideBar(QWidget* parent)
:QWidget(parent)
{
   ui_.setupUi(this);
}

SideBar::~SideBar()
{

}

void SideBar::setCurrentMd2FileLabel(const QString& newText)
{
   ui_.currentMd2File->setText(newText);
}

QPushButton* SideBar::md2LoadButton() const
{
   return ui_.md2OpenButton;
}