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
    QLabel *phoneNumber;
    QGridLayout *commonLayout;
    QWidget *mainWindow;
    QSize screenSize;
    void createCommonLayout();

};
#endif // DIALER_PI_WINDOW_H
