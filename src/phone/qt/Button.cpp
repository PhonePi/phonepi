#include <QTextEdit>
#include <iostream>
#include <QDebug>
#include "Button.h"

Button::Button(QWidget *parent)
        : QLabel(parent)
{
}

Button::~Button() {
}

void Button::setLabel(QLabel* label){
    numberLabel = label;
}

QGridLayout* Button::createButtonGrid(QWidget* wiget){
    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(2);
    int buttonWidth = wiget->width() / 3 - 2 * layout->spacing() / 3;
    int buttonHeight = wiget->height() / 4 - 3 * layout->spacing() / 4;


    std::string fontcolor = "QLabel { color: black; }";
    int k = 0;
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            Button *btn = new Button();
            btn->setText(numbers[k].c_str());
            k++;
            btn->setStyleSheet(QString(fontcolor.c_str()));
            QFont font = btn->font();
            font.setPointSize(30);
            font.setBold(true);
            btn->setAlignment(Qt::AlignCenter);
            btn->setFont(font);

            btn->setAutoFillBackground(true);
            QPalette pal(palette());
            pal.setColor(QPalette::Background, "#fbf1c7");
            btn->setPalette(pal);

            btn->setFixedSize(buttonWidth, buttonHeight);
            connect(btn, SIGNAL(clicked()), this, SLOT(buttonClicked()));
            if(btn->text() == "0")
                connect(btn, SIGNAL(doubleClicked()), this, SLOT(doubleClick()));

            layout->addWidget(btn, i, j, Qt::AlignCenter);
        }
    }

    return layout;
}

void Button::createButtonIco(std::string iconPath, QSize size){
    setScaledContents(true);
    QPixmap backPict(iconPath.c_str());
    QIcon backIcon(backPict);
    setPixmap(backPict);
    setFixedSize(size);
}

void Button::mouseDoubleClickEvent(QMouseEvent *event){
    emit doubleClicked();
}

void Button::mousePressEvent(QMouseEvent *event){
    emit clicked();
}

void Button::buttonClicked() {
    QLabel* button = (QLabel*)qobject_cast<QWidget*>(sender());
    QString newText = numberLabel->text() + button->text();
    numberLabel->setText(newText);
}

void Button::doubleClick(){

    QString oldText = numberLabel->text().toStdString().substr(0, numberLabel->text().size() - 1).c_str();
    QString newText = oldText + "+";
    numberLabel->setText(newText);
}