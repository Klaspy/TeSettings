QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = TeSettings

VERSION = 1.0.3
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += TE_SETTINGS_LIBRARY

TEMPLATE = lib
DESTDIR = $$PWD/lib/te_settings
win32: QMAKE_POST_LINK += $$QMAKE_COPY $$system_path($$PWD/te_settings/tesettings.h) $$system_path($$PWD/lib/te_settings/tesettings.h)
else: QMAKE_POST_LINK += cp $$PWD/te_settings/tesettings.h $$PWD/lib/te_settings/tesettings.h


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        te_settings/tesettings.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    te_settings/tesettings.h
