#-------------------------------------------------
#
# Project created by QtCreator 2017-10-18T12:40:56
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    LoginWindow.cpp \
    ClickableLabel.cpp \
    Register.cpp \
    User.cpp \
    Utils.cpp


HEADERS += \
        MainWindow.h \
    LoginWindow.h \
    ClickableLabel.h \
    Register.h \
    packet.h \
    User.h \
    Utils.h

FORMS += \
        MainWindow.ui \
    LoginWindow.ui \
    Register.ui

RESOURCES += \
    res.qrc

