//
// Created by arseny on 7/4/17.
//

#ifndef DIALER_PI_BUTTON_H
#define DIALER_PI_BUTTON_H


#include <QtWidgets/QPushButton>

class Button : public QPushButton{
    Q_OBJECT
public:
    Button(QWidget * parent = 0);
    QPushButton* createButtonIco(std::string, QSize);
    QLayout* createButtonGrid();

public slots:
    void buttonClicked();

private:
    std::string numbers[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#"};

};


#endif //DIALER_PI_BUTTON_H
