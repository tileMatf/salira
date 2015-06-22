#------------------------------------------------- 
#
# Project created by QtCreator 2015-05-29T01:22:54 
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Salira
TEMPLATE = app 

SOURCES += main.cpp\
        mainwindow.cpp \
        Engines/translator.cpp \
        Data/gcommand.cpp \
        Data/vaxcommand.cpp \
        Engines/parser.cpp \
    Engines/executor.cpp \
    Data/state.cpp \
    Data/graphnode.cpp \
    Data/dumpnode.cpp

HEADERS  += mainwindow.h \
            Engines/translator.h \
            Data/gcommand.h \
            Data/vaxcommand.h \
            Engines/parser.h \
    Engines/executor.h \
    Data/state.h \
    Data/graphnode.h \
    Data/dumpnode.h
            
FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc