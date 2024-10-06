QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hex_map
TEMPLATE = app


HEADERS += \
    Interface.h \
    Mainmenu.h \
    Map.h \
    Intro.h \
    Pickmenu.h \
    Play.h \
    Header.h \
    Ball.h \
    Sound.h \
    Tiger.h \
    Tremble.h

SOURCES += \
    Interface.cpp \
    Sound.cpp \
    main.cpp \
    Mainmenu.cpp \
    Map.cpp \
    Intro.cpp \
    Pickmenu.cpp \
    Play.cpp \
    Ball.cpp \
    Tiger.cpp \
    Tremble.cpp

RESOURCES += \
    Resc.qrc

CONFIG += resources_big
