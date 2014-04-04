#-------------------------------------------------
#
# Project created by QtCreator 2013-03-26T15:03:11
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = VirtualMemoryManager
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    harddrive.cpp \
    object.cpp \
    physicalmemory.cpp \
    virtualmemorymanager.cpp \
    pagetable.cpp \
    tlb.cpp \
    command.cpp \
    commandmanager.cpp \
    page.cpp \
    frame.cpp

HEADERS += \
    harddrive.h \
    object.h \
    physicalmemory.h \
    virtualmemorymanager.h \
    pagetable.h \
    tlb.h \
    command.h \
    commandmanager.h \
    page.h \
    frame.h
