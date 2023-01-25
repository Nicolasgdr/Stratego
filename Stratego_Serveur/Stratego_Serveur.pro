QT -= gui
QT += network
QT += core
QT += sql
QT += widgets
CONFIG -= app_bundle
greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++20

SOURCES += \
    Server.cpp \
    connection_to_client.cpp \
    dao/historyDao.cpp \
    dao/pauseDao.cpp \
    dao/statDao.cpp \
    dao/userDao.cpp \
    dto/historyDto.cpp \
    dto/pauseDto.cpp \
    dto/statDto.cpp \
    dto/userDto.cpp \
    main.cpp \
    repository/historyrepository.cpp \
    repository/pauseRepository.cpp \
    repository/statrepository.cpp \
    repository/userrepository.cpp \
    server_view.cpp

HEADERS += \
    Server.h \
    connection_to_client.h \
    dao/historyDao.h \
    dao/pauseDao.h \
    dao/statDao.h \
    dao/userDao.h \
    dto/historyDto.h \
    dto/pauseDto.h \
    dto/statDto.h \
    dto/userDto.h \
    repository/historyrepository.h \
    repository/pauseRepository.h \
    repository/statrepository.h \
    repository/userrepository.h \
    server_view.h



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Stratego_libs/ -lStratego_Libs
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Stratego_libs/ -lStratego_Libs
else:unix: LIBS += -L$$PWD/../Stratego_libs/ -lStratego_Libs

INCLUDEPATH += $$PWD/../Stratego_libs
DEPENDPATH += $$PWD/../Stratego_libs

DESTDIR = $$PWD/
