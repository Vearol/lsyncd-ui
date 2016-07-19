#ifndef FILESYSTEMTREETEST_H
#define FILESYSTEMTREETEST_H

#include <QObject>
#include <QtTest/QtTest>

class FileSystemTreeTest: public QObject
{
    Q_OBJECT
private slots:
    void simpleAddPathTest();
    void simplePartialBackupTest();
    void addPathsTest();
    void addSiblingsPathsTest();
    void isBackedUpWithParentTest();
    void addMoreCommonItemTest();
    void removePathsTest();
    void removeCleanupTest();
    void isInTheTreeTest();
    void addParentPathTest();
    void simpleAddRootTest();
    void addRootTest();
    void addRootRemovesChildrenTest();
};

#endif // FILESYSTEMTREETEST_H
