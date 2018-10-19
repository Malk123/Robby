QT += core network widgets multimedia

CONFIG += c++11 console link_pkgconfig

PKGCONFIG += gstreamer-video-1.0
INCLUDEPATH += "/home/alex/Projects/qt_projects/robby/final/gst-plugins-base-1.2.4/gst-libs/gst"

SOURCES += main.cpp \
    socket/gstream.cpp \
    control/control.cpp \
    socket/controlsocket.cpp \
    form/form.cpp

HEADERS += \
    socket/gstream.h \
    control/control.h \
    socket/controlsocket.h \
    form/form.h
FORMS += \
    form/form.ui
