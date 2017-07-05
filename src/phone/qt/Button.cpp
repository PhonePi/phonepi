//
// Created by arseny on 7/4/17.
//

#include <QTextEdit>
#include <iostream>
#include "Button.h"

Button::Button(QString text, QWidget *parent)
        : QLabel(parent)
{
    setText(text);
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
            Button *btn = new Button(numbers[k].c_str());
            k++;
            btn->setStyleSheet(QString(fontcolor.c_str()));
            QFont font = btn->font();
            font.setPointSize(20);
            font.setBold(true);
            btn->setAlignment(Qt::AlignCenter);
            btn->setFont(font);

            btn->setAutoFillBackground(true);
            QPalette pal(palette());
            pal.setColor(QPalette::Background, "#fbf1c7");
            btn->setPalette(pal);

            btn->setFixedSize(buttonWidth, buttonHeight);
            connect(btn, SIGNAL(clicked()), this, SLOT(buttonClicked()));

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

void Button::mousePressEvent(QMouseEvent *event){
    std::cout << "clicked event \n";
    emit clicked();
}

void Button::buttonClicked() {
    std::cout << "clicked SLOT \n";
    //Get button caption that rised this signal
}