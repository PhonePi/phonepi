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

QLayout* Button::createButtonGrid(int parentWidth, int parentHeight){
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
    //button->setStyleSheet("QPushButton {background-color:transparent;}");

    return button;
}