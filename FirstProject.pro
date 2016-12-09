#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T18:22:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FirstProject
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    newuser.cpp \
    addorread.cpp \
    crypto.cpp

LIBS += \
       -lboost_system -lboost_filesystem -lbotan-1.11\

INCLUDEPATH += -I"/usr/local/include"

HEADERS  += mainwindow.h \
    newuser.h \
    addorread.h \
    crypto.h

FORMS    += mainwindow.ui \
    newuser.ui \
    addorread.ui
