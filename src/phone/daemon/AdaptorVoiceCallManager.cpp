#include "AdaptorVoiceCallManager.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class VoiceCallManagerAdaptor
 */

VoiceCallManagerAdaptor::VoiceCallManagerAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    setAutoRelaySignals(true);
}

VoiceCallManagerAdaptor::~VoiceCallManagerAdaptor()
{
}

