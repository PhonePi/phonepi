#ifndef PHONE_QDBUS_H
#define PHONE_QDBUS_H

#include <QString>
#include <QtDBus>

typedef struct{
    QString name;
    QMap<QString, QVariant> porp_map;
} Modem_struct;
Q_DECLARE_METATYPE(Modem_struct)

class QDBusCalls {
private:
    QDBusConnection bus = QDBusConnection::systemBus();
    Modem_struct modem_struct;
    QString selected_modem;
    bool isAnswerValid(QDBusMessage msg);
    void getModemAnswer(const QDBusArgument &dbusArgs);

public:
    QDBusCalls();
    ~QDBusCalls();
    void dialNumber(const char* phoneNumber);

};


#endif //PHONE_QDBUS_H
