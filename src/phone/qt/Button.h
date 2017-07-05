//
// Created by arseny on 7/4/17.
//

#ifndef DIALER_PI_BUTTON_H
#define DIALER_PI_BUTTON_H


#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>

class Button : public QLabel{
    Q_OBJECT
public:
    Button(QString text = "", QWidget * parent = 0);
    void createButtonIco(std::string, QSize);
    QGridLayout* createButtonGrid();

public slots:
    void buttonClicked();

signals:
    void clicked();

private:
    std::string numbers[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#"};
    void mousePressEvent(QMouseEvent*);

};


#endif //DIALER_PI_BUTTON_H
