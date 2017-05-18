QT += core dbus
QT -= gui
CONFIG += c++11 qtquickcompiler no_keywords

HEADERS += Handler.h Struct.h

SOURCES += main.cpp Handler.cpp

target.path = $$[QT_INSTALL_EXAMPLES]
sources.files = $$SOURCES $$HEADERS calls_daemon.pro
sources.path = $$[QT_INSTALL_EXAMPLES]
INSTALLS += target sources
