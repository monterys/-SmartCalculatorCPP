QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creditModel.cc \
    creditController.cc \
    creditwindow.cc \
    depositModel.cc \
    depositController.cc \
    depositwindow.cc \
    main.cc \
    mainwindow.cc \
    calcModel.cc \
    calcController.cc \
    qcustomplot.cc 

HEADERS += \
    creditModel.h \
    creditController.h \
    creditwindow.h \
    depositModel.h \
    depositController.h \
    depositwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#QT       += core gui printsupport

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++17

## You can make your code fail to compile if it uses deprecated APIs.
## In order to do so, uncomment the following line.
##DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#SOURCES += \
#creditwindow.cpp \
#    depositwindow.cpp \
#    grafwindow.cpp \
#    main.cpp \
#    mainwindow.cpp \
#    base.c \
#    calc.c \
#    parcer.c \
#    rpn.c \
#    verification.c \
#    qcustomplot.cpp

#HEADERS += \
#    creditwindow.h \
#    depositwindow.h \
#    grafwindow.h \
#    mainwindow.h \
#    SmartCalc.h \
#    qcustomplot.h

#FORMS += \
#    creditwindow.ui \
#    depositwindow.ui \
#    grafwindow.ui \
#    mainwindow.ui

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

