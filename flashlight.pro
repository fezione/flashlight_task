#-------------------------------------------------
#
# Project created by QtCreator 2022-07-05T17:23:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flashlight
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR = .moc
UI_DIR = .uic
RCC_DIR = .rcc

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myview.cpp \
    tcpclient.cpp \
    flashl.cpp

HEADERS += \
        mainwindow.h \
    myview.h \
    tcpclient.h \
    flashl.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
