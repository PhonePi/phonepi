#ifndef OFONOMODEM_H
#define OFONOMODEM_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.ofono.Modem
 */
class OrgOfonoModemInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.ofono.Modem"; }

public:
    OrgOfonoModemInterface(const QString &service, const QString &path,
                           const QDBusConnection &connection, QObject *parent = 0);

    ~OrgOfonoModemInterface();

public Q_SLOTS:
    inline QDBusPendingReply<QVariantMap> GetProperties()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetProperties"), argumentList);
    }

    inline QDBusPendingReply<> SetProperty(const QString &property, const QDBusVariant &value)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(property) << QVariant::fromValue(value);
        return asyncCallWithArgumentList(QStringLiteral("SetProperty"), argumentList);
    }

Q_SIGNALS:
    void PropertyChanged(const QString &name, const QDBusVariant &value);
};

namespace org {
  namespace ofono {
    typedef ::OrgOfonoModemInterface Modem;
  }
}
#endif
