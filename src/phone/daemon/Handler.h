//
// Created by arseny on 15.05.17.
//

#ifndef DAEMON_HANDLER_H
#define DAEMON_HANDLER_H

#include <QString>
#include <QVariant>

class Handler : public QObject{
public:
    void callAdded(QString path, QMap<QString, QVariant> props);
    void callRemoved(QString path);
    Handler(QDBusConnection bus, QString current_modem);
    QString phoneNumber;
};


#endif //DAEMON_HANDLER_H
