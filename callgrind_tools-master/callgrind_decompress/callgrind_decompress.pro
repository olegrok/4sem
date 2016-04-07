TEMPLATE = app
TARGET = callgrind_decompress
DEPENDPATH += .
INCLUDEPATH += .

mac:CONFIG -= app_bundle

#CONFIG += release
QT = core

# Input
HEADERS += decompress.h
SOURCES += main.cpp decompress.cpp
