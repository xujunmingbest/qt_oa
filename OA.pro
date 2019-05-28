#-------------------------------------------------
#
# Project created by QtCreator 2019-04-29T09:47:19
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OA
TEMPLATE = app


INCLUDEPATH += F:\OA\c-sdk-for-windows-master\include

LIBS += F:\OA\c-sdk-for-windows-master\lib\curllib.lib
LIBS += F:\OA\c-sdk-for-windows-master\lib\libeay32.lib
LIBS += F:\OA\c-sdk-for-windows-master\lib\openldap.lib
LIBS += F:\OA\c-sdk-for-windows-master\lib\qiniu.lib
LIBS += F:\OA\c-sdk-for-windows-master\lib\ssleay32.lib

DEFINES  -= UNICODE
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#RC_ICONS += XiaShanJiasfo.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    mysqloperate.cpp \
    showauth.cpp \
    tianjialiushuizhang.cpp \
    chakanliushuizhang.cpp \
    xiugaimima.cpp \
    addoperator.cpp \
    operatorlist.cpp \
    editoperator.cpp \
    editliushuizhang.cpp \
    datastatistic.cpp

HEADERS  += mainwindow.h \
    login.h \
    mysqloperate.h \
    showauth.h \
    tianjialiushuizhang.h \
    chakanliushuizhang.h \
    mysqlstruct.h \
    xiugaimima.h \
    addoperator.h \
    operatorlist.h \
    editoperator.h \
    editliushuizhang.h \
    datastatistic.h \
    picture.h

FORMS    += mainwindow.ui \
    login.ui \
    showauth.ui \
    tianjialiushuizhang.ui \
    chakanliushuizhang.ui \
    xiugaimima.ui \
    addoperator.ui \
    operatorlist.ui \
    editoperator.ui \
    editliushuizhang.ui \
    datastatistic.ui

RESOURCES += \
    image.qrc
