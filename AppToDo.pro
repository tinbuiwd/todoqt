#-------------------------------------------------
#
# Project created by QtCreator 2017-02-24T14:47:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppToDo
TEMPLATE = app


SOURCES += main.cpp\
    taskwindow.cpp \
    calendar.cpp \
    comboboxdelegate.cpp

HEADERS  += \
    taskwindow.h \
    calendar.h \
    comboboxdelegate.h

FORMS    += \
    taskwindow.ui \
    calendar.ui
