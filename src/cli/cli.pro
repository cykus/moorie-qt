!include( ../../moorie.pri ):error( Nie można znaleść pliku moorie.pri! )
QT -= gui
TARGET = ../../build/moorie
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    anyoption.cpp 
HEADERS += anyoption.h
LIBS += -L../../build/ -lmoorie
LIBS += -lmcrypt -lboost_regex -lboost_program_options -lboost_filesystem -lmhash -lqca
