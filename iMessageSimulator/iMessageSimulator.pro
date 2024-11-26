#-------------------------------------------------
#
# Project created by QtCreator 2024-08-20T00:33:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iMessageSimulator
TEMPLATE = app


SOURCES += main.cpp\
        UfrmMain.cpp \
    UServerWindow.cpp \
    USentWindow.cpp \
    mail.cpp \
    server.cpp \
    user.cpp \
    UCreateMailDialog.cpp \
    UMailDialog.cpp \
    queue.cpp \
    UConectDialog.cpp \
    UDeletedWindow.cpp \
    UInfoDialog.cpp \
    UErrorDialog.cpp \
    iscorrectstring.cpp

HEADERS  += UfrmMain.h \
    UServerWindow.h \
    USentWindow.h \
    mail.h \
    server.h \
    user.h \
    UCreateMailDialog.h \
    UMailDialog.h \
    queue.h \
    UConectDialog.h \
    UDeletedWindow.h \
    UInfoDialog.h \
    UErrorDialog.h \
    iscorrectstring.h

FORMS    += UFrmMain.ui \
    UServerWindow.ui \
    USentWindow.ui \
    UCreateMailDialog.ui \
    UMailDialog.ui \
    UConectDialog.ui \
    UDeletedWindow.ui \
    UInfoDialog.ui \
    UErrorDialog.ui

RESOURCES += \
    imgMail.qrc
