#-------------------------------------------------
#
# Project created by QtCreator 2010-08-09T12:43:09
#
#-------------------------------------------------
QT       += core gui opengl

TARGET = MopViewer
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        glwidget.cpp \
		controls.cpp \
		qtglut.cpp \
		textdisplay.cpp \
    ../moody/capsule/capsuleBase/tinyxml/ticpp.cpp \
    ../moody/capsule/capsuleBase/tinyxml/tinyxml.cpp \
    ../moody/capsule/capsuleBase/tinyxml/tinyxmlerror.cpp \
    ../moody/capsule/capsuleBase/tinyxml/tinyxmlparser.cpp \
    ../moody/capsule/capsuleBase/mopfile/MopState.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    controls.h \
    trailset.h \
    singletrail.h \
    trailElement.h \
    mophandling.h \
    qtglut.h \
    textdisplay.h \
    trailmanager.h \
    ../moody/capsule/capsuleBase/tinyxml/ticpp.h \
    ../moody/capsule/capsuleBase/tinyxml/ticpprc.h \
    ../moody/capsule/capsuleBase/tinyxml/tinyxml.h \
    ../moody/capsule/capsuleBase/mopfile/MopFile.h \
    ../moody/capsule/capsuleBase/mopfile/MopItem.h \
    ../moody/capsule/capsuleBase/mopfile/MopState.h \
    ../moody/capsule/capsuleBase/etc/Advisor.h

FORMS    += mainwindow.ui \
		controls.ui \
		textdisplay.ui

RESOURCES += \
    resources.qrc
