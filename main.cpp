#include "Be_my_girlfriend.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Be_my_girlfriend w;
	w.show();
	return a.exec();
}
