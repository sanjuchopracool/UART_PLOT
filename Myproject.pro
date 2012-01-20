#-------------------------------------------------
#
# Project created by QtCreator 2012-01-15T10:58:15
#
#-------------------------------------------------

QT       += core gui

TARGET = Myproject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/receiveport.cpp

HEADERS  += mainwindow.h \
    src/receiveport.h

FORMS    += mainwindow.ui
LIBS += -lqwt
