QT += core dbus 
QT -= gui
CONFIG += c++11 qtquickcompiler warn_off

HEADERS += Handler.h Struct.h \
        OfonoModem.h OfonoVoiceCallManagerAdaptor.h \

SOURCES += main.cpp \
    Handler.cpp \
    OfonoModem.cpp \
    OfonoVoiceCallManagerAdaptor.cpp \



target.path = $$[QT_INSTALL_EXAMPLES]
sources.files = $$SOURCES $$HEADERS calls_daemon.pro
sources.path = $$[QT_INSTALL_EXAMPLES]
INSTALLS += target sources
