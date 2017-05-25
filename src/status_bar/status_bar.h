#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QtCore/QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QString>
#include <QtDBus>
#include <QObject>

class MainWindow : public QQmlApplicationEngine{
	Q_OBJECT
public:
    MainWindow(QObject *parent = 0);
    ~MainWindow();
	Q_INVOKABLE void getTime ();
	Q_INVOKABLE void getBatteryState();

private:
	QList<QObject*> objectList;
};
#endif // STATUSBAR_H
