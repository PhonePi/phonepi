#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QString>

class MainWindow : public QQmlApplicationEngine{
    Q_OBJECT
public:
    MainWindow(QObject *parent = 0);
    ~MainWindow();
    Q_INVOKABLE void shutTheFuckUpKhmOff();
    Q_INVOKABLE void close();
	void setPath( int, char **);
private:
	char *socket_path = "\0hidden";
};
#endif // MAINWINDOW_H
