//
// Created by kivi on 23.05.17.
//

#ifndef DESKTOP_ICONCLICK_H
#define DESKTOP_ICONCLICK_H

#include <QObject>
#include "Config.h"

class AppRunner : public QObject {
Q_OBJECT

public:

    AppRunner(Applicaton app): app_(app) {}

public slots:

    void execute();

private:
    Applicaton app_;
};


#endif //DESKTOP_ICONCLICK_H
