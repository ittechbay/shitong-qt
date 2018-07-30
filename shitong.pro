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
    mainpanel.cpp \
    setdate.cpp \
    setptp.cpp \
    setntp.cpp \
    setdatetime.cpp \
    settime.cpp \
    statetable.cpp \
    setalarm.cpp

HEADERS  += widget.h \
    boardbutton.h \
    mainpanel.h \
    setdate.h \
    setptp.h \
    setntp.h \
    setdatetime.h \
    settime.h \
    statetable.h \
    setalarm.h

FORMS    += \
    boardbutton.ui \
    widget.ui \
    mainpanel.ui \
    setdate.ui \
    setptp.ui \
    setntp.ui \
    setdatetime.ui \
    settime.ui \
    setalarm.ui

RESOURCES += \
    res.qrc

DISTFILES +=
