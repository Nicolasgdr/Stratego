QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += console c++20

SOURCES += \
        Client.cpp \
        case_lobby.cpp \
        listofgame.cpp \
        main.cpp \
        welcome_home_page.cpp\
        gui/board.cpp\
        gui/buffer.cpp\
        gui/convert.cpp\
        gui/counter.cpp\
        gui/deck.cpp\
        gui/graphicview.cpp\
        gui/tile.cpp\
        gui/zone.cpp


HEADERS += \
    Client.h \
    case_lobby.h \
    listofgame.h \
    welcome_home_page.h\
    gui/board.h\
    gui/buffer.h\
    gui/convert.h\
    gui/counter.h\
    gui/deck.h\
    gui/graphicview.h\
    gui/tile.h\
    gui/zone.h


FORMS += \
    listofgame.ui \
    welcome_home_page.ui \
    gui/widget.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Stratego_libs/ -lStratego_Libs
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Stratego_libs/ -lStratego_Libs
else:unix: LIBS += -L$$PWD/../Stratego_libs/ -lStratego_Libs

INCLUDEPATH += $$PWD/../Stratego_libs
DEPENDPATH += $$PWD/../Stratego_libs
