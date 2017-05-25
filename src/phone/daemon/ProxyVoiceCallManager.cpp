#include "ProxyVoiceCallManager.h"

/*
 * Implementation of interface class OrgOfonoVoiceCallManagerInterface
 */

OrgOfonoVoiceCallManagerInterface::OrgOfonoVoiceCallManagerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

OrgOfonoVoiceCallManagerInterface::~OrgOfonoVoiceCallManagerInterface()
{
}

