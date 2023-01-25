QT -= gui

TEMPLATE = lib
#DEFINES += STRATEGO_LIBS_LIBRARY
CONFIG += staticlib
CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Stratego-encap/stratego_encap.cpp \
    Model/bomb.cpp \
     Model/case.cpp \
     Model/flag.cpp\
     Model/game.cpp\
     Model/gameboard.cpp\
     Model/miner.cpp\
     Model/piece.cpp\
     Model/scout.cpp\
     Model/spy.cpp\
     Model/state_error.cpp \
     Model/bot.cpp \
     Stratego-encap/json_generator.cpp \
     Stratego-encap/json_interpreter.cpp

HEADERS += \
    Stratego-encap/stratego_encap.h \
    Model/bomb.h \
     Model/case.h \
     Model/flag.h\
     Model/game.h\
     Model/gameboard.h\
     Model/miner.h\
     Model/piece.h\
     Model/scout.h\
     Model/spy.h\
     Model/state_error.h\
     Model/color.h \
     Model/gameState.h \
     Model/observ.h\
     Model/rank.h \
     Model/Player.hpp\
     Model/action_send.h\
     Model/bot.h\
     Stratego-encap/json_generator.h \
     Stratego-encap/json_interpreter.h



# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DESTDIR = $$PWD/


