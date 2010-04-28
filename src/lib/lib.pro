!include( ../../moorie.pri ):error( Nie można znaleść pliku moorie.pri! )
QT += network \
    webkit
QT -= gui
TARGET = ../../build/moorie
TEMPLATE = lib
DEFINES += MOORIE_LIBRARY
SOURCES += libmoorie.cpp \
    mailboxes/GoogleApps.cpp \
    cmtransfer.cpp \
    cmtools.cpp \
    cmdownload.cpp \
    cmupload.cpp \
    cmstats.cpp \
    hashmanager.cpp \
    hash.cpp \
    tools.cpp \
    hashutils.cpp \
    stringutils.cpp \
    decoder.cpp \
    mailboxfactory.cpp \
    emailheader.cpp \
    moorhunthash.cpp \
    log.cpp \
    mailbox.cpp
HEADERS += libmoorie.h \
    mailboxes/GoogleApps.h \
    libmoorie_global.h \
    cmtransfer.h \
    cmtools.h \
    cmdownload.h \
    cmupload.h \
    cmstats.h \
    hashmanager.h \
    hashdecoder.h \
    moorhunthashdecoder.h \
    hash.h \
    hashinfo.h \
    tools.h \
    hashutils.h \
    stringutils.h \
    decoder.h \
    mailboxfactory.h \
    emailheader.h \
    moorhunthash.h \
    log.h \
    mailbox.h
unix { 
    HARDWARE_PLATFORM = $$system(uname -i)
    contains( HARDWARE_PLATFORM, x86_64 ):LIBS += ../../libs/libmoorhunt.a
    else:LIBS += ../../libs/libmoorhunt64.a
}
