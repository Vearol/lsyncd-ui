TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += main.cpp \
    BackupListModel.cpp \
    BackupItem.cpp \
    LsyncdConfigModel.cpp \
    pathhelpers.cpp \
    TreeViewModel.cpp \
    filesystemtree.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    BackupListModel.h \
    BackupItem.h \
    LsyncdConfigModel.h \
    pathhelpers.h \
    TreeViewModel.h \
    enums.h \
    filesystemtree.h

DISTFILES += \
    assets/folder_blue.svg \
    assets/file_blue.svg \
    assets/List_blue.svg \
    assets/List_gray.svg \
    assets/List_white.svg \
    assets/tree_blue.svg \
    assets/tree_gray.svg \
    assets/tree_white.svg \
    assets/file_gray.svg \
    assets/folder_gray.svg

