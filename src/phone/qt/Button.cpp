//
// Created by arseny on 7/4/17.
//

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLabel>
#include "Button.h"

Button::Button(QWidget *parent)
        : QPushButton(parent)
{
}

QLayout* Button::createButtonGrid(){
    QGridLayout *layout = new QGridLayout();
    layout->setVerticalSpacing(2);
    layout->setHorizontalSpacing(2);

    std::string fontcolor = "QLabel { color : black; }";
    int k = 0;
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            QPushButton *button = new QPushButton(numbers[k].c_str());
            k++;
            button->setStyleSheet(QString(fontcolor.c_str()));
            QFont font = button->font();
            font.setPointSize(20);
            font.setBold(true);
            button->setFont(font);
            //button->setStyleSheet("QPushButton {background-color:transparent;}");

            button->setFixedSize(70, 70);
            connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

            layout->addWidget(button, i, j, Qt::AlignCenter);
        }
    }

    return layout;
}

QPushButton* Button::createButtonIco(std::string iconPath, QSize size){
    QPushButton *button = new QPushButton();
    QPixmap backPict(iconPath.c_str());
    QIcon backIcon(backPict);
    button->setIcon(backIcon);
    button->setIconSize(size);
    button->setFixedSize(size);

    return button;
}

void Button::buttonClicked() {
    //Get button caption that rised this signal
}