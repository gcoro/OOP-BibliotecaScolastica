#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T13:32:59
#
#-------------------------------------------------

QT       += core gui xml

QMAKE_CXXFLAGS += -std=c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bibliotecaScolastica
TEMPLATE = app


SOURCES += main.cpp\
        libro.cpp \
        libronarrativa.cpp \
        libroscolastico.cpp \
        cdmusicale.cpp \
        rivista.cpp \
        biblioteca.cpp \
        articolo.cpp \
        utente.cpp \
        amministratore.cpp \
        studente.cpp \
        esterno.cpp \
        contribuente.cpp \
        registrazioni.cpp \
        gui/mainwindowlogin.cpp \
        gui/dialogadmin.cpp \
        gui/utentitab.cpp \
        gui/bibliotab.cpp \
        gui/dialogutenteesterno.cpp \
        gui/dialogutentestudente.cpp \
        gui/dialogutentecontribuente.cpp



HEADERS  += \
            libro.h \
            libronarrativa.h \
            libroscolastico.h \
            cdmusicale.h \
            rivista.h \
            biblioteca.h \
            articolo.h \
            utente.h \
            amministratore.h \
            studente.h \
            esterno.h \
            contribuente.h \
            registrazioni.h \
            gui/mainwindowlogin.h \
            gui/dialogadmin.h \
            gui/utentitab.h \
            gui/bibliotab.h \
            gui/dialogutenteesterno.h \
            gui/dialogutentestudente.h \
            gui/dialogutentecontribuente.h

