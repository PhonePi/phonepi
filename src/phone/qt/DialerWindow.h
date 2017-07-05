#ifndef DIALER_PI_WINDOW_H
#define DIALER_PI_WINDOW_H

#include <QtCore/QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QApplication>
#include <QString>
#include <QObject>
#include <QLabel>
#include <QGridLayout>


class DialerWindow : public QWidget{
    Q_OBJECT
public:
    DialerWindow(QWidget *parent = 0);
    ~DialerWindow();
    void showDialer();

public slots:
    void back();
    void erase();
    void dialNumber();

private:
    QString selected_modem;
    QLabel *phoneNumber;
    std::string workingDir = "//home//arseny//Repos//KSPT//Phone//src//phone//qt//";
    QGridLayout *commonLayout;
    QWidget *mainWindow;
    void getSimPath();
    QSize screenSize;
    void getScreenSize();
    void createCommonLayout();

};
#endif // DIALER_PI_WINDOW_H
