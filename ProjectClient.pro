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
    Utils.cpp \
    ForgetPass.cpp \
    UpdatePasswd.cpp \
    AdminControlWidget.cpp \
    ClientMainWindow.cpp \
    ClientSocket.cpp \
    InputAdminPasswordDialog.cpp \
    InputhostAddressDialog.cpp \
    NetworkConfigurationDialog.cpp \
    RecordAVI.cpp


HEADERS += \
        MainWindow.h \
    LoginWindow.h \
    ClickableLabel.h \
    Register.h \
    packet.h \
    User.h \
    Utils.h \
    ForgetPass.h \
    UpdatePasswd.h \
    CommandType.h \
    AdminControlWidget.h \
    ClientMainWindow.h \
    ClientSocket.h \
    InputAdminPasswordDialog.h \
    InputhostAddressDialog.h \
    NetworkConfigurationDialog.h \
    RecordAVI.h

FORMS += \
        MainWindow.ui \
    LoginWindow.ui \
    Register.ui \
    ForgetPass.ui \
    UpdatePasswd.ui \
    AdminControlWidget.ui \
    ClientMainWindow.ui \
    InputAdminPasswordDialog.ui \
    InputhostAddressDialog.ui \
    NetworkConfigurationDialog.ui

RESOURCES += \
    res.qrc

INCLUDEPATH += /Users/Cary/Downloads/opencv-3.3.0/include
INCLUDEPATH += /Users/Cary/Downloads/opencv-3.3.0/include/opencv
INCLUDEPATH += /Users/Cary/Downloads/opencv-3.3.0/include/opencv2

#------------------------------
#LIBS += /Users/Cary/Downloads/opencv-3.3.0/lib/libopencv_core.3.3.0.dylib
#LIBS += /Users/Cary/Downloads/opencv-3.3.0/lib/libopencv_highgui.3.3.0.dylib
#LIBS += /Users/Cary/Downloads/opencv-3.3.0/lib/libopencv_imgproc.3.3.0.dylib
#LIBS += /Users/Cary/Downloads/opencv-3.3.0/lib/libopencv_video.3.3.0.dylib

#LIBS += /usr/local/lib/libopencv_highgui.so \
 #       /usr/local/lib/libopencv_core.so    \
 #       /usr/local/lib/libopencv_imgproc.so
#---------------------------------------------------------
