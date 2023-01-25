include(../defaults.pri)

TEMPLATE = lib
TARGET = libcore
DESTDIR = ../lib
#CONFIG += console # c++11

QMAKE_CXXFLAGS += -std=c++17 -Wpedantic -Werror -Wsuggest-override

HEADERS += \
    bomb.h \
    case.h \
    color.h \
    flag.h \
    game.h \
    gameState.h \
    gameboard.h \
    miner.h \
    observ.h \
    piece.h \
    rank.h \
    scout.h \
    spy.h \
    state_error.h

SOURCES += \
    bomb.cpp \
    case.cpp \
    flag.cpp \
    game.cpp \
    gameboard.cpp \
    miner.cpp \
    piece.cpp \
    scout.cpp \
    spy.cpp \
    state_error.cpp

