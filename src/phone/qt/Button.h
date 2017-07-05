#ifndef DIALER_PI_BUTTON_H
#define DIALER_PI_BUTTON_H


#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>

class Button : public QLabel{
    Q_OBJECT
public:
    Button(QWidget * parent = 0);
    ~Button();
    void createButtonIco(std::string, QSize);
    QGridLayout* createButtonGrid(QWidget*);
    void setLabel(QLabel*);

public slots:
    void buttonClicked();
    void doubleClick();

signals:
    void clicked();
    void doubleClicked();

private:
    std::string numbers[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#"};
    void mousePressEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    QLabel* numberLabel;

};


#endif //DIALER_PI_BUTTON_H
