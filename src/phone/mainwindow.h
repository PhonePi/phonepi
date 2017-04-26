#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QString>
#include <QtDBus>

class MainWindow : public QQmlApplicationEngine{
    Q_OBJECT
    
public:
    MainWindow(QObject *parent = 0);
    ~MainWindow();
    void GetModem();
    void EnableModem();
    //void TestConnection();
    void AnswerValidation(QDBusMessage msg);
    Q_INVOKABLE void DialNumber(QString number);

private:
    QDBusConnection bus = QDBusConnection::systemBus();
    QString selected_modem;
};
#endif // MAINWINDOW_H
