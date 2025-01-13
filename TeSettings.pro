QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle


VERSION = 1.0.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

CONFIG(debug, debug |release) {
    TEMPLATE = app
} else {
    DESTDIR = $$PWD/lib/te_settings
    TEMPLATE = lib
    QMAKE_POST_LINK += cp $$PWD/te_settings/tesettings.h $$PWD/lib/te_settings/tesettings.h
}


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        te_settings/tesettings.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    te_settings/tesettings.h
