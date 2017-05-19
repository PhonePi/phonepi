#include "mainwindow.h"
#include <iostream>
#include <memory>
#include <QQuickView>
#include <QDateTime>
#include <unistd.h>

MainWindow::MainWindow(QObject *parent)
        : QQmlApplicationEngine(parent)
{
    load(QUrl("qrc:///main.qml"));
    rootContext()->setContextProperty("window", this);
	QList<QObject*> objectList = this->rootObjects();//->findChild<QObject*>("status_bar");
	object =  objectList[0]->findChild<QObject*>("status_text");
}
MainWindow::~MainWindow() {}


void MainWindow::setValue(){
		if(object)
			object->setProperty("text", QTime::currentTime());	
		else
			qDebug() << "object: "<< object;
}
