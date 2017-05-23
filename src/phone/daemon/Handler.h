//
// Created by arseny on 15.05.17.
//

#ifndef DAEMON_HANDLER_H
#define DAEMON_HANDLER_H

#include <QString>
#include <QVariant>
#include <QObject>
#include <QDBusConnection>

class Handler : public QObject{
    Q_OBJECT

public:
    Handler(QObject* parent = NULL);
    ~Handler();
    //Handler(QDBusConnection, QString);
    static QString phoneNumber;
    void setUpHandler(QDBusConnection, QString);

public Q_SLOTS:
    void callAdded(const QString&, const QMap<QString, QVariant>&);
    void callRemoved(QString path);

};


#endif //DAEMON_HANDLER_H
