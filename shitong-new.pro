#-------------------------------------------------
#
# Project created by QtCreator 2018-08-02T07:44:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shitong-new
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    boardbutton.cpp \
    clock.cpp \
    ctrbuttonform.cpp \
    mainpanel.cpp \
    setalarm.cpp \
    setdate.cpp \
    setdatetime.cpp \
    setntp.cpp \
    setptp.cpp \
    settime.cpp \
    statetable.cpp \
    ftsCan.c

HEADERS  += widget.h \
    boardbutton.h \
    clock.h \
    ctrbuttonform.h \
    mainpanel.h \
    setalarm.h \
    setdate.h \
    setdatetime.h \
    setntp.h \
    setptp.h \
    settime.h \
    statetable.h \
    ftsCan.h \
    ftsSetDo.h

FORMS    += widget.ui \
    boardbutton.ui \
    mainpanel.ui \
    setalarm.ui \
    setdatetime.ui \
    setdate.ui \
    setntp.ui \
    setptp.ui \
    settime.ui

RESOURCES += \
    res.qrc
