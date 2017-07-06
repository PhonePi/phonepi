#ifndef DIALER_PI_CALLWINDOW_H
#define DIALER_PI_CALLWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTime>

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
    QTime elapsedTime;
    QSize screenSize;
    int secs;
    int min;
    QString phoneNumber;
    QWidget *callWindow;
    QGridLayout *commonLayout;
    QLabel *timerLabel;
    void createCommonLayout();
};


#endif //DIALER_PI_CALLWINDOW_H
