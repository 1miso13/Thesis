# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = QtGuiApplication2
DESTDIR = ../x64/Release/QtProgram
QT += core opengl gui widgets openglextensions
CONFIG += release
DEFINES += _UNICODE WIN64 QT_DLL QT_OPENGL_LIB QT_OPENGLEXTENSIONS_LIB QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName)
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(QtGuiApplication2.pri)
