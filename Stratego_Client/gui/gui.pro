INCLUDEPATH += ../metier

QT       += core gui

LIBS += -L../lib -llibcore \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++17 -Wpedantic -Werror

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    buffer.cpp \
    convert.cpp \
    counter.cpp \
    deck.cpp \
    graphicview.cpp \
    main.cpp \
    mainwindow.cpp \
    menubar.cpp \
    parametermenu.cpp \
    startmenu.cpp \
    statusbar.cpp \
    tile.cpp \
    zone.cpp

HEADERS += \
    board.h \
    buffer.h \
    convert.h \
    counter.h \
    deck.h \
    graphicview.h \
    imagestock.h \
    mainwindow.h \
    menubar.h \
    parametermenu.h \
    startmenu.h \
    statusbar.h \
    tile.h \
    zone.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
