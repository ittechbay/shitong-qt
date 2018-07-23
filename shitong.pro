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
    boardbutton.cpp \
    mainpanel.cpp

HEADERS  += widget.h \
    boardbutton.h \
    mainpanel.h

FORMS    += \
    boardbutton.ui \
    widget.ui \
    mainpanel.ui

RESOURCES += \
    res.qrc

DISTFILES +=
