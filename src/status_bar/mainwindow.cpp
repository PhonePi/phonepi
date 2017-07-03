#include "mainwindow.h"
#include <iostream>
#include <memory>
#include <QQuickView>
#include <QDateTime>
#include <unistd.h>
#include <fstream>

MainWindow::MainWindow(QObject *parent)
        : QQmlApplicationEngine(parent)
{
    load(QUrl("qrc:///main.qml"));
    rootContext()->setContextProperty("status", this);
	objectList = this->rootObjects();
	getBatteryState();
}
MainWindow::~MainWindow() {}


void MainWindow::getTime(){
	QObject* object =  objectList[0]->findChild<QObject*>("time");
	if(object)
		object->setProperty("text", QTime::currentTime());	
}

void MainWindow::getBatteryState(){
	QObject* object =  objectList[0]->findChild<QObject*>("battery");
	std::ifstream batteryFile;
	int state = 0;
	batteryFile.open("battery_status");
	if (batteryFile.is_open()) {
		while (!batteryFile.eof()) {
		    batteryFile >> state;
		}
	}
	batteryFile.close();
	if (state >= 0 && state < 5){
		object->setProperty("text","");	
		object->setProperty("color","red");	
	}
	if (state >= 5 && state < 30){
		object->setProperty("text", ""); 
		object->setProperty("color", "white"); 
	}
	if (state >= 30 && state < 50){
		object->setProperty("text","");	
		object->setProperty("color","white");	
	}
	if (state >= 50 && state < 85){
		object->setProperty("text", "");	
		object->setProperty("color","white");	
	}
	if (state >= 85 && state < 100){
		object->setProperty("text", "");		
		object->setProperty("color","white");	
	}
}

