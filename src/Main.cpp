#include "MainWindow.h"
#include <iostream>
#include <QtCore>
#include <QApplication>

int main(int argc, char * argv[])
{
	std::cout << argc << argv << std::endl;
	QApplication app(argc, argv);
	MainWindow window;
	QObject::connect(&window, SIGNAL(quitApp()), &app, SLOT(quit()));
	return app.exec();
}
