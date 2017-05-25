#ifndef ADAPTORVOICECALLMANAGER_H
#define ADAPTORVOICECALLMANAGER_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface org.ofono.VoiceCallManager
 */
class VoiceCallManagerAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ofono.VoiceCallManager")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.ofono.VoiceCallManager\">\n"
"    <signal name=\"PropertyChanged\">\n"
"      <arg type=\"s\" name=\"name\"/>\n"
"      <arg type=\"v\" name=\"value\"/>\n"
"    </signal>\n"
"    <signal name=\"CallAdded\">\n"
"      <annotation value=\"QVariantMap\" name=\"org.qtproject.QtDBus.QtTypeName.In1\"/>\n"
"      <arg type=\"o\" name=\"path\"/>\n"
"      <arg type=\"a{sv}\" name=\"properties\"/>\n"
"    </signal>\n"
"    <signal name=\"CallRemoved\">\n"
"      <arg type=\"o\" name=\"path\"/>\n"
"    </signal>\n"
"  </interface>\n"
        "")
public:
    VoiceCallManagerAdaptor(QObject *parent);
    virtual ~VoiceCallManagerAdaptor();

public Q_SLOTS:
Q_SIGNALS:
    void CallAdded(const QDBusObjectPath &path, const QVariantMap &properties);
    void CallRemoved(const QDBusObjectPath &path);
    void PropertyChanged(const QString &name, const QDBusVariant &value);
};

#endif
