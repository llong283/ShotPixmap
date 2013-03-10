#-------------------------------------------------
#
# Project created by QtCreator 2011-02-10T14:55:08
#
#-------------------------------------------------

QT       += core gui

TARGET = ShotPixmap
TEMPLATE = app

include(qxtglobalshortcut/qxtglobalshortcut.pri)


SOURCES += main.cpp\
        widget.cpp \
    customlabel.cpp \
    tool.cpp \
    drawtool.cpp \
    customtextedit.cpp

HEADERS  += widget.h \
    ../ShotPixmap-build-desktop/ui_widget.h \
    customlabel.h \
    qxtglobalshortcut/qxtglobalshortcut_p.h \
    qxtglobalshortcut/qxtglobalshortcut.h \
    qxtglobalshortcut/qxtglobal.h \
    tool.h \
    drawtool.h \
    customtextedit.h

FORMS    += widget.ui \
    tool.ui \
    drawtool.ui

RESOURCES += \
    source.qrc

OTHER_FILES += \
    icon.rc

RC_FILE += icon.rc
