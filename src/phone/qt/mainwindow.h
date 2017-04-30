#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QString>
#include <QtDBus>

typedef struct{
    QString name;
    QMap<QString, QVariant> porp_map;
} Parse_struct;
Q_DECLARE_METATYPE(Parse_struct)

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
    Parse_struct modem_struct;
    QString selected_modem;
};
#endif // MAINWINDOW_H
