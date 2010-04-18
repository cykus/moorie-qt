! include( ../moorie.pri ) {
    error( Nie można znaleść pliku moorie.pri! )
}

QT -= gui

TARGET = ../build/moorie

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
HEADERS += 

LIBS += -L../build/ -lmoorie
