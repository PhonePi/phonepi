#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QQmlContext>
#include <QApplication>
#include <QWidget>
class MainWindow : public QQmlApplicationEngine{
    Q_OBJECT
    
public:
    MainWindow(QObject *parent = 0);
    ~MainWindow();
    Q_INVOKABLE void EmptyFunc();
    Q_INVOKABLE void DialNumber(QString number);
};
#endif // MAINWINDOW_H
