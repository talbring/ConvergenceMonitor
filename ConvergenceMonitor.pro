#-------------------------------------------------
#
# Project created by QtCreator 2015-10-25T12:37:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ConvergenceMonitor
TEMPLATE = app

INCLUDEPATH += include

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/qcustomplot.cpp \
    src/plotsettings.cpp \
    src/datahandler.cpp \
    src/datatab.cpp

HEADERS  += include/mainwindow.h \
    include/qcustomplot.h \
    include/plotsettings.h \
    include/datahandler.h \
    include/datatab.h

FORMS    += ui/mainwindow.ui \
    ui/plotsettings.ui \
    ui/datatab.ui

UI_DIR = ui
MOC_DIR = .moc
OBJECTS_DIR = .obj
