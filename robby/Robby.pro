QT -= gui concurrent designer
QT += core network widgets multimedia

CONFIG += c++11 console link_pkgconfig
CONFIG -= app_bundle

LIBS += -L/usr/local/lib -lwiringPi

PKGCONFIG += gstreamer-1.0

INCLUDEPATH += "/usr/include/"

SOURCES += main.cpp \
    Sockets/command.cpp \
    Sockets/video.cpp

HEADERS += \
    Sockets/command.h \
    Sockets/video.h




