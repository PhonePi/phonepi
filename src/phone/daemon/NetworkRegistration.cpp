#include "NetworkRegistration.h"

/*
 * Implementation of interface class OrgOfonoNetworkRegistrationInterface
 */

OrgOfonoNetworkRegistrationInterface::OrgOfonoNetworkRegistrationInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

OrgOfonoNetworkRegistrationInterface::~OrgOfonoNetworkRegistrationInterface()
{
}

