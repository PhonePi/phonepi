QT += core dbus
CONFIG += c++11 qtquickcompiler warn_off

HEADERS += Handler.h \
        Struct.h \
        OfonoModem.h \
        AdaptorVoiceCallManager.h \
        ProxyVoiceCallManager.h \

SOURCES += main.cpp \
    Handler.cpp \
    OfonoModem.cpp \
    AdaptorVoiceCallManager.cpp \
    ProxyVoiceCallManager.cpp \

target.path = $$[QT_INSTALL_EXAMPLES]
sources.files = $$SOURCES $$HEADERS calls_daemon.pro
sources.path = $$[QT_INSTALL_EXAMPLES]
INSTALLS += target sources
