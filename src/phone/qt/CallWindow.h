#ifndef DIALER_PI_CALLWINDOW_H
#define DIALER_PI_CALLWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class CallWindow : public QWidget {
    Q_OBJECT
public:
    CallWindow(QString phoneNumber, QWidget *parent = 0);
    ~CallWindow();
    void showWindow();

public slots:
    void updateTimerLabel();
    void hang();

private:
    QSize screenSize;
    int secs;
    int min;
    QString phoneNumber;
    QWidget *callWindow;
    QGridLayout *commonLayout;
    QLabel *timerLabel;
    void createCommonLayout();
    void getScreenSize();
};


#endif //DIALER_PI_CALLWINDOW_H
