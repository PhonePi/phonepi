#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
	Q_INVOKABLE void setValue();

private:
	QObject* object;
};
#endif // MAINWINDOW_H
