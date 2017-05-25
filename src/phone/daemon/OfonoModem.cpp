#include "OfonoModem.h"

/*
 * Implementation of interface class OrgOfonoModemInterface
 */

OrgOfonoModemInterface::OrgOfonoModemInterface(
        const QString &service, const QString &path,
        const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

OrgOfonoModemInterface::~OrgOfonoModemInterface()
{
}

