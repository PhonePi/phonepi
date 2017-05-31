#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

#include <iostream>
#include <QtWidgets/QPushButton>

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
    brightnessSpinBox->setValue(100);

    QSlider* brightnessSlider = new QSlider(Qt::Horizontal, 0);
    brightnessSlider->setRange(0, 100);
    brightnessSlider->setValue(100);
    QObject::connect(brightnessSlider, &QSlider::valueChanged, brightnessSpinBox, &QSpinBox::setValue);
    QObject::connect(brightnessSlider, &QSlider::valueChanged, readBrightness);

    brightnessLayout->addWidget(brightnessLabel);
    brightnessLayout->addWidget(brightnessSlider);
    brightnessLayout->addWidget(brightnessSpinBox);
    brightnessWidget->setLayout(brightnessLayout);

    layout->addWidget(brightnessWidget, 0, Qt::AlignTop | Qt::AlignVCenter | Qt::AlignBaseline);


    // back button
    QWidget* controlWidget = new QWidget;
    controlWidget->setWindowTitle("controls");
    QHBoxLayout *controlLayout = new QHBoxLayout();

    QPushButton *backButton = new QPushButton;
    backButton->setText("back");
    backButton->setStyleSheet(QString(fontcolor.c_str()));
    font = backButton->font();
    font.setPointSize(16);
    font.setBold(true);
    backButton->setFont(font);
    QObject::connect(backButton, &QPushButton::clicked, &a, &QApplication::quit);
    controlLayout->addWidget(backButton);


    controlWidget->setLayout(controlLayout);
    layout->addWidget(controlWidget, 0, Qt::AlignVertical_Mask);


    // start application
    widget.setLayout(layout);
    widget.showMaximized();
    widget.activateWindow();

    // start up brightness thread
    startUpBrightnessThread();

    return a.exec();
}