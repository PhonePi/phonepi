#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

#include <iostream>

#include "brightness.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    QWidget widget;

    // main layout
    QVBoxLayout *layout = new QVBoxLayout();

    // brightness
    QWidget* brightnessWidget = new QWidget;
    brightnessWidget->setWindowTitle("brightness");
    QHBoxLayout *brightnessLayout = new QHBoxLayout();

    QLabel* brightnessLabel = new QLabel("Brightness:");
    std::string fontcolor = "QLabel { color : black; }";
    brightnessLabel->setStyleSheet(QString(fontcolor.c_str()));
    QFont font = brightnessLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    brightnessLabel->setFont(font);

    QSpinBox *brightnessSpinBox = new QSpinBox;
    brightnessSpinBox->setReadOnly(true);

    QSlider* brightnessSlider = new QSlider(Qt::Horizontal, 0);
    brightnessSlider->setRange(0, 100);
    QObject::connect(brightnessSlider, &QSlider::valueChanged, brightnessSpinBox, &QSpinBox::setValue);
    QObject::connect(brightnessSlider, &QSlider::valueChanged, readBrightness);

    brightnessLayout->addWidget(brightnessLabel);
    brightnessLayout->addWidget(brightnessSlider);
    brightnessLayout->addWidget(brightnessSpinBox);
    brightnessWidget->setLayout(brightnessLayout);


    layout->addWidget(brightnessWidget, 0 , Qt::AlignTop | Qt::AlignVCenter | Qt::AlignBaseline);

    // start application
    widget.setLayout(layout);
    widget.showMaximized();
    widget.activateWindow();

    // start up brightness thread
    startUpBrightnessThread();

    return a.exec();
}