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

QGridLayout Button::createButtonGrid(int parentWidth, int parentHeight){
    QGridLayout *layout = new QGridLayout();
    layout->setVerticalSpacing(2);
    layout->setHorizontalSpacing(2);

    std::string fontcolor = "QLabel { color : black; }";
    int k = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 4; j++){
            QLabel *caption = new QLabel(numbers[k].c_str());
            k++;
            caption->setStyleSheet(QString(fontcolor.c_str()));
            QFont font = caption->font();
            font.setPointSize(20);
            font.setBold(true);
            caption->setFont(font);

            layout->addWidget(caption, i, j, Qt::AlignCenter);
        }


}

QPushButton* Button::createButtonIco(char* iconPath, QSize size){
    QPushButton *button = new QPushButton();
    QPixmap backPict(iconPath);
    QIcon backIcon(backPict);
    button->setIcon(backIcon);
    button->setIconSize(size);
    button->setStyleSheet("QPushButton {background-color:transparent;}");

    return button;
}