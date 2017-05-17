#include "mainwindow.h"
#include <iostream>
#include <memory>

MainWindow::MainWindow(QObject *parent)
        : QQmlApplicationEngine(parent)
{
    load(QUrl("qrc:///main.qml"));
    rootContext()->setContextProperty("window", this);
}
MainWindow::~MainWindow() {}


QString MainWindow::execCom(){
    const char* cmd = "date";
	std::array<char,128> buffer;
	QString result;
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
	    if (!pipe) throw std::runtime_error("popen() failed!");
		    while (!feof(pipe.get())) {
			     if (fgets(buffer.data(), 128, pipe.get()) != NULL)
					 result += buffer.data();
			 }
	 return result;
}
