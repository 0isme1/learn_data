#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09 T 23:42:49
#
# @Qt Version : Qt Creator 4.4.1 Based on Qt 5.9.3 (MSVC 2015, 32 bit)
#
# @Author : wsg
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Weather
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        weather.cpp \

HEADERS += \
        WeatherTool.h \
        weather.h

FORMS += \
        weather.ui

RESOURCES += \
    images/images.qrc \
    icons/icons.qrc \
    weatherIcons/weatypeico.qrc
