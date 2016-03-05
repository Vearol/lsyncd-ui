QT += core testlib
QT -= gui

CONFIG += c++11

TARGET = lsync-ui-tests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../lsyncd_ui/BackupItem.cpp \
    ../lsyncd_ui/BackupListModel.cpp \
    ../lsyncd_ui/LsyncdConfigModel.cpp \
    configgeneratortests.cpp

HEADERS += \
    ../lsyncd_ui/BackupItem.h \
    ../lsyncd_ui/BackupListModel.h \
    ../lsyncd_ui/LsyncdConfigModel.h \
    configgeneratortests.h
