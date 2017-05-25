#include "status_bar.h"
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
	FILE *in;
    char state[512];
    if(!(in = popen("cat battery_status", "r")))
        exit(1);

    fgets(state, sizeof(state), in);
	
	pclose(in);

	if (*state >= 0 && *state < 5){
		object->setProperty("text","");	
		object->setProperty("color","red");	
	}
	if (*state >= 5 && *state < 30){
		object->setProperty("text", ""); 
		object->setProperty("color", "white"); 
	}
	if (*state >= 30 && *state < 50){
		object->setProperty("text","");	
		object->setProperty("color","white");	
	}
	if (*state >= 50 && *state < 85){
		object->setProperty("text", "");	
		object->setProperty("color","white");	
	}
	if (*state >= 85 && *state < 100){
		object->setProperty("text", "");		
		object->setProperty("color","white");	
	}
}

