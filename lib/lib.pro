! include( ../moorie.pri ) {
    error( Nie można znaleść pliku moorie.pri! )
}
QT       += network webkit xml
QT       -= gui

TARGET = ../build/moorie
TEMPLATE = lib

DEFINES += MOORIE_LIBRARY

SOURCES += libmoorie.cpp

HEADERS += libmoorie.h\
        libmoorie_global.h
