#ifndef DIALER_PI_INCOMINGCALL_H
#define DIALER_PI_INCOMINGCALL_H

#include <QtCore/QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QApplication>
#include <QString>
#include <QObject>
#include <QLabel>
#include <QGridLayout>


class IncomingCall : public QWidget{
    Q_OBJECT
public:
    IncomingCall(QString phoneNumber, QWidget *parent = 0);
    ~IncomingCall();
    void showIncoming();

public slots:
    void answer();
    void hang();

private:
    QString phoneNumber;
    QSize screenSize;
    std::string workingDir = "//home//arseny//Repos//KSPT//Phone//src//phone//qt//";
    QGridLayout *commonLayout;
    QWidget *incomingWindow;
    void getScreenSize();
    void createCommonLayout();

};
#endif // DIALER_PI_INCOMINGCALL_H
