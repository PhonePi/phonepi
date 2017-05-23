#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <iostream>
#include <QtWidgets/QPushButton>
#include "Config.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Config config("config.ini");


    QWidget widget;
    std::string background = "background-image: url(" + config.getBackgroung() + ")";
    widget.setStyleSheet(QString(background.c_str()));


    QGridLayout* layout = new QGridLayout();
    const int maxrows = config.getDesktopRows();
    const int maxcolumns = config.getDesktopColumns();
    int column = 0, row = 0;
    int iconsize = config.getIconsize();


    for (auto&& app : config.getApplications()) {
        QPushButton* btn = new QPushButton();
        if (!app.icon.empty()) {
            QPixmap pixmap(app.icon.c_str());
            QIcon ButtonIcon(pixmap);
            btn->setIcon(ButtonIcon);
            btn->setIconSize(QSize(iconsize, iconsize));
        }
        //btn->setFlat(true);
        btn->setStyleSheet("QPushButton {background-color:transparent;}");
        btn->show();
        layout->addWidget(btn, row, column++);
        if (column >= maxcolumns) {
            column = 0;
            ++row;
            if (row >= maxrows) break;
        }
    }
    while (row < maxrows) {
        QWidget *wgt = new QWidget;
        wgt->setFixedSize(0, 0);
        wgt->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        wgt->setAutoFillBackground(false);
        layout->addWidget(wgt, row, column++);
        if (column >= maxcolumns) {
            column = 0;
            ++row;
        }
    }
    widget.setLayout(layout);
    widget.showFullScreen();

    return a.exec();
}
