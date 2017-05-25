#ifndef NETWORKREGISTRATION_H
#define NETWORKREGISTRATION_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.ofono.NetworkRegistration
 */
class OrgOfonoNetworkRegistrationInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.ofono.NetworkRegistration"; }

public:
    OrgOfonoNetworkRegistrationInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgOfonoNetworkRegistrationInterface();

public Q_SLOTS:
    inline QDBusPendingReply<> GetOperators()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetOperators"), argumentList);
    }

    inline QDBusPendingReply<QVariantMap> GetProperties()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetProperties"), argumentList);
    }

    inline QDBusPendingReply<> Register()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("Register"), argumentList);
    }

Q_SIGNALS:
};

namespace org {
  namespace ofono {
    typedef ::OrgOfonoNetworkRegistrationInterface NetworkRegistration;
  }
}
#endif
