//
// Created by kivi on 30.06.17.
//

#ifndef UNBLOCK_PI_TIMER_H
#define UNBLOCK_PI_TIMER_H

#include <QObject>

class Timer : public QObject {
Q_OBJECT

signals:
    void updateTime(QString);

public:

    void start();

};

std::string getCurrentTime();


#endif //UNBLOCK_PI_TIMER_H
