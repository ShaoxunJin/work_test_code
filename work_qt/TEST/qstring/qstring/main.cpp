#include <QtGui/QApplication>
#include "display_lne.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	display_lne w;
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
