#-------------------------------------------------
#
# Project created by QtCreator 2015-05-25T13:38:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    play.cpp \
    gameover.cpp \
    win.cpp

HEADERS  += mainwindow.h \
    play.h \
    gameover.h \
    win.h

FORMS    += mainwindow.ui \
    play.ui \
    gameover.ui \
    win.ui

RESOURCES += \
    2048pic.qrc
