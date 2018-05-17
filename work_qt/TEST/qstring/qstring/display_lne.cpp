#include "display_lne.h"

display_lne::display_lne(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
}

display_lne::~display_lne()
{

}

void display_lne::on_IDC_Btn_Display_clicked()
{
	ui.IDC_Lne_Display->setText(QString::number(999));
}