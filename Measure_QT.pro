QT       += core gui
QT       += charts
QT       += serialport serialbus
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=$$PWD/source/include
INCLUDEPATH +=$$PWD/source/library

SOURCES += \
    source/library/sqlite3.c \
    source/src/app_measure.cpp \
    source/src/app_output.cpp \
    source/src/history.cpp \
    source/src/keyboard.cpp \
    source/src/led.cpp \
    source/src/menu.cpp \
    source/src/menu_alarm.cpp \
    source/src/menu_correct.cpp \
    source/src/menu_note.cpp \
    source/src/menu_output.cpp \


HEADERS += \
    source/include/app_measure.h \
    source/include/app_output.h \
    source/include/history.h \
    source/include/keyboard.h \
    source/include/led.h \
    source/include/main.h \
    source/include/menu.h \
    source/include/menu_alarm.h \
    source/include/menu_correct.h \
    source/include/menu_note.h \
    source/include/menu_output.h \
    source/include/platform_config.h \
    source/library/sqlite3.h \


FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Measure_QT_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    back_icon.qrc
