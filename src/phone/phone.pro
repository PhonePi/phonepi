QT += gui qml quick core dbus
CONFIG += c++11 qtquickcompiler

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += mainwindow.h

SOURCES += main.cpp mainwindow.cpp

OTHER_FILES = main.qml

RESOURCES += res.qrc

target.path = $$[QT_INSTALL_EXAMPLES]
sources.files = $$SOURCES $$HEADERS $$RESOURCES phone.pro
sources.path = $$[QT_INSTALL_EXAMPLES]
INSTALLS += target sources
