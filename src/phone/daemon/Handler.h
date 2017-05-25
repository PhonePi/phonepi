#ifndef DAEMON_HANDLER_H
#define DAEMON_HANDLER_H

#include <QString>
#include <QVariant>
#include <QObject>
#include <QDBusConnection>
#include <QtDBus/QtDBus>

class Handler : public QObject{
    Q_OBJECT

public:
    Handler(QObject* parent = NULL);
    ~Handler();
    static QString phoneNumber;
    void setUpHandler(QDBusConnection, QString);

public Q_SLOTS:
    void callAdded(const QDBusObjectPath& path, const QVariantMap& props);
    void callRemoved(QString path);

Q_SIGNALS:
    void CallAdded(const QDBusObjectPath& path, const QVariantMap& props);

};


#endif //DAEMON_HANDLER_H
