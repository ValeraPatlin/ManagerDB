#-------------------------------------------------
#
# Project created by QtCreator 2025-04-15T08:27:18
#
#-------------------------------------------------

QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ManagerDB
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        managerdb.cpp \
    formcreatedb.cpp \
    frontdb.cpp \
    formtablename.cpp \
    formrequestdb.cpp

HEADERS += \
        managerdb.h \
    formcreatedb.h \
    frontdb.h \
    formtablename.h \
    formrequestdb.h

FORMS += \
        managerdb.ui \
    formcreatedb.ui \
    formtablename.ui \
    formrequestdb.ui \
    formrequestdb.ui
