#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QString>
#include <QtDBus>

struct Answer_struct{
    QString name;
    QMap<QString, QVariant> porp_map;
};
Q_DECLARE_METATYPE(Answer_struct)

class MainWindow : public QQmlApplicationEngine{
    Q_OBJECT
public:
    MainWindow(QObject *parent = 0);
    ~MainWindow();
    void GetModem();
    void EnableModem();
    void AnswerValidation(QDBusMessage msg);
    Q_INVOKABLE void dialNumber(QString number);

private:
    QDBusConnection bus = QDBusConnection::systemBus();
    QString selected_modem;
    QVariant isModemEnabled = "false";
	QString dialedNumber;
};
#endif // MAINWINDOW_H
