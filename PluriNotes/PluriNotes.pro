#-------------------------------------------------
#
# Project created by QtCreator 2017-05-11T18:41:39
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PluriNotes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    plurinotes.cpp \
    application.cpp \
    notes.cpp \
    noteentity.cpp \
    noteelement.cpp \
    notetemplate.cpp \
    note_article.cpp \
    note_document.cpp

HEADERS  += \
    application.h \
    notes.h \
    noteentity.h \
    noteelement.h \
    notetemplate.h \
    note_article.h \
    note_document.h

FORMS    += plurinotes.ui
