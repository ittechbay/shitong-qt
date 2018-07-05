#-------------------------------------------------
#
# Project created by QtCreator 2018-03-26T08:59:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shitong
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dialog_ptpcfg.cpp \
    dialog_clockcfg.cpp \
    dialog_swich.cpp \
    dialog_b.cpp \
    dialog_power.cpp \
    dialog_123.cpp

HEADERS  += widget.h \
    dialog_ptpcfg.h \
    dialog_clockcfg.h \
    dialog_swich.h \
    dialog_b.h \
    dialog_power.h \
    dialog_123.h

FORMS    += widget.ui \
    dialog_ptpcfg.ui \
    dialog_clockcfg.ui \
    dialog_swich.ui \
    dialog_b.ui \
    dialog_power.ui \
    dialog_123.ui

RESOURCES += \
    res.qrc

DISTFILES +=
