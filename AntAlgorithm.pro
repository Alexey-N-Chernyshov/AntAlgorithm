#-------------------------------------------------
#
# Project created by QtCreator 2010-11-15T23:38:23
#
#-------------------------------------------------

QT       += core gui

TARGET = AntAlgorithm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphscene.cpp \
    graphicsnodeitem.cpp \
    graphicsedgeitem.cpp \
    graphicstextitem.cpp \
    ant.cpp \
    antalgorithm.cpp

HEADERS  += mainwindow.h \
    graphscene.h \
    graphicsnodeitem.h \
    graphicsedgeitem.h \
    graphicstextitem.h \
    ant.h \
    antalgorithm.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
