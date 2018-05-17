#ifndef DISPLAY_LNE_H
#define DISPLAY_LNE_H

#include <QtGui/QWidget>
#include "ui_display_lne.h"
#include <iostream>
using namespace std;

class display_lne : public QWidget
{
	Q_OBJECT

public:
	display_lne(QWidget *parent = 0, Qt::WFlags flags = 0);
	~display_lne();

private:
	Ui::display_lneClass ui;

private slots:
	void on_IDC_Btn_Display_clicked();
};

#endif // DISPLAY_LNE_H
