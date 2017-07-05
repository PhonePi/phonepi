#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <iostream>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QScreen>

#include "Config.h"
#include "AppRunner.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Config config;

    // creating widget
    QWidget widget;
    // setting background image
    std::string background = "background-image: url(" + config.getBackgroung() + ")";
    widget.setStyleSheet(QString(background.c_str()));

    // creating layout for widget
    QGridLayout* layout = new QGridLayout();
    const int maxrows = config.getDesktopRows();
    const int maxcolumns = config.getDesktopColumns();
    int column = 0, row = 0;
    int iconsize = config.getIconsize();
    // handlers for desktop items
    std::vector<AppRunner*> handlers;

    for (auto&& app : config.getApplications()) {
        // vertival layout for gred cell
        QVBoxLayout* vbox = new QVBoxLayout;

        // creating handler for application
        handlers.push_back(new AppRunner(app));
        // creating button for application
        QPushButton* btn = new QPushButton();
        QPixmap pixmap(app.icon.c_str());
        QIcon ButtonIcon(pixmap);
        btn->setIcon(ButtonIcon);
        btn->setIconSize(QSize(iconsize, iconsize));
        btn->setStyleSheet("QPushButton {background-color:transparent;}");
        btn->show();
        // connecting button with handler
        QObject::connect(btn, SIGNAL(clicked()), handlers.back(), SLOT(execute()));
        // adding button to cell layout
        btn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        vbox->addWidget(btn);

        // creating label for button
        QLabel* lbl = new QLabel(QString(app.name.c_str()));
        lbl->setAlignment(Qt::AlignCenter);
        std::string fontcolor = "QLabel { color : " + config.getFontColor() + "; }";
        lbl->setStyleSheet(QString(fontcolor.c_str()));
        QFont font = lbl->font();
        font.setPointSize(config.getFontSize());
        font.setBold(true);
        lbl->setFont(font);
        lbl->setMinimumWidth(btn->size().width());
        lbl->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        vbox->addWidget(lbl);

        // adding cell layout to grid layout
        layout->addLayout(vbox, row, column++);

        // check layout parameters
        if (column >= maxcolumns) {
            column = 0;
            ++row;
            if (row >= maxrows) break;
        }
    }
    // if layout is not full, add stub widgets
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
    // set layout
    widget.setLayout(layout);
    // run
	QRect geometry = QGuiApplication::primaryScreen()->geometry();
    widget.setFixedSize(geometry.width(), geometry.height());
    widget.activateWindow();
	widget.show();

    return a.exec();
}
