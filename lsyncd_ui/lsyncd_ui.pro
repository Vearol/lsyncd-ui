TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += main.cpp \
    BackupListModel.cpp \
    BackupItem.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    BackupListModel.h \
    BackupItem.h

DISTFILES += \
    assets/folder_blue.svg \
    assets/file_blue.svg

