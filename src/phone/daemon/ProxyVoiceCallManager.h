#ifndef PROXYVOICECALLMANAGER_H
#define PROXYVOICECALLMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.ofono.VoiceCallManager
 */
class OrgOfonoVoiceCallManagerInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.ofono.VoiceCallManager"; }

public:
    OrgOfonoVoiceCallManagerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgOfonoVoiceCallManagerInterface();

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void CallAdded(const QDBusObjectPath &path, const QVariantMap &properties);
    void CallRemoved(const QDBusObjectPath &path);
    void PropertyChanged(const QString &name, const QDBusVariant &value);
};

namespace org {
  namespace ofono {
    typedef ::OrgOfonoVoiceCallManagerInterface VoiceCallManager;
  }
}
#endif
