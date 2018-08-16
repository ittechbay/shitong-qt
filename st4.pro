QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = st4
TEMPLATE = app


HEADERS += \
    boardbutton.h \
    clock.h \
    ctrbuttonform.h \
    ftsCan.h \
    ftsSetDo.h \
    mainpanel.h \
    setalarm.h \
    setdate.h \
    setdatetime.h \
    setntp.h \
    setptp.h \
    settime.h \
    statetable.h \
    widget.h

SOURCES += \
    boardbutton.cpp \
    clock.cpp \
    ctrbuttonform.cpp \
    main.cpp \
    mainpanel.cpp \
    setalarm.cpp \
    setdate.cpp \
    setdatetime.cpp \
    setntp.cpp \
    setptp.cpp \
    settime.cpp \
    statetable.cpp \
    widget.cpp \
    ftsCan.c

RESOURCES += \
    res.qrc

FORMS += \
    boardbutton.ui \
    frame.ui \
    mainpanel.ui \
    setalarm.ui \
    setdate.ui \
    setdatetime.ui \
    setntp.ui \
    setptp.ui \
    settime.ui \
    widget.ui
