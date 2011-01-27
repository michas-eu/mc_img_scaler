#include <QtGui/QApplication>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
	int tmp;
	QApplication a(argc, argv);
	MainWindow w;
	w.set_args(a.arguments());
	tmp = w.cond_show();
	if (tmp) return a.exec();
	else return 0;
}
