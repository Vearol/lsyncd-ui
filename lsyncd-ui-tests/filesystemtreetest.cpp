#include "filesystemtreetest.h"
#include "../lsyncd_ui/FileSystemTree.h"

void FileSystemTreeTest::simpleAddPathTest() {
    BackupTree tree;
    tree.addBackupPath("/a/b/c");
    QVERIFY(tree.isFullBackup("/a/b/c/"));
    QVERIFY(!tree.isPartialBackup("/a/b/c"));
}

void FileSystemTreeTest::simplePartialBackupTest() {
    BackupTree tree;
    tree.addBackupPath("/a/b/c");
    QVERIFY(!tree.isFullBackup("/a"));
    QVERIFY(!tree.isFullBackup("/a/b/"));
    QVERIFY(tree.isPartialBackup("/a/b"));
}

void FileSystemTreeTest::addPathsTest() {
    BackupTree tree;
    tree.addBackupPath("/a/b/c");
    tree.addBackupPath("/a/b/d");

    QVERIFY(tree.isFullBackup("/a/b/c/"));
    QVERIFY(tree.isFullBackup("/a/b/d/"));
}

void FileSystemTreeTest::addSiblingsPathsTest() {
    BackupTree tree;
    tree.addBackupPath("/a/c");
    tree.addBackupPath("/a/d");
    tree.addBackupPath("/a/b/c");
    tree.addBackupPath("/a/b/d");

    QVERIFY(!tree.isFullBackup("/a"));
    QVERIFY(tree.isPartialBackup("/a"));
    QVERIFY(tree.isFullBackup("/a/c"));
    QVERIFY(tree.isFullBackup("/a/d"));
    QVERIFY(tree.isFullBackup("/a/b/c/"));
    QVERIFY(tree.isFullBackup("/a/b/d/"));
}

void FileSystemTreeTest::isBackedUpWithParentTest() {
    BackupTree tree;
    tree.addBackupPath("/a/b");

    QVERIFY(tree.isFullBackup("/a/b/c/"));
}

void FileSystemTreeTest::addMoreCommonItemTest() {
    BackupTree tree;
    tree.addBackupPath("/a/b/c");
    tree.addBackupPath("/a/b/");

    QVERIFY(tree.isFullBackup("/a/b/"));
}

void FileSystemTreeTest::removePathsTest() {
    BackupTree tree;
    tree.addBackupPath("/a/b/c");
    tree.removeBackupPath("/a/b/c");

    QVERIFY(!tree.isFullBackup("/a/b/c"));
    QVERIFY(!tree.isPartialBackup("/a/b/c"));

    QVERIFY(!tree.isFullBackup("/a"));
    QVERIFY(!tree.isPartialBackup("/a"));
}

void FileSystemTreeTest::removeCleanupTest() {
    BackupTree tree;
    tree.addBackupPath("/a/b/c");
    tree.addBackupPath("/a/k/r");

    tree.removeBackupPath("/a/b/c");

    QVERIFY(!tree.isFullBackup("/a/b/"));
    QVERIFY(!tree.isPartialBackup("/a/b/"));

    QVERIFY(tree.isFullBackup("/a/k/r/"));
    QVERIFY(tree.isPartialBackup("/a/k"));
}

void FileSystemTreeTest::isInTheTreeTest() {
    BackupTree tree;
    tree.addBackupPath("/a/b");

    QVERIFY(!tree.isInTheTree("/a"));
    QVERIFY(tree.isInTheTree("/a/b"));
    QVERIFY(!tree.isInTheTree("/a/b/c"));
    QVERIFY(tree.isFullBackup("/a/b/c"));
}

void FileSystemTreeTest::addParentPathTest() {
    BackupTree tree;
    tree.addBackupPath("/a/b/c");
    tree.addBackupPath("/a/b/d");
    tree.addBackupPath("/k/l/m");

    tree.addBackupPath("/a/b");

    QVERIFY(tree.isFullBackup("/a/b/c"));
    QVERIFY(!tree.isInTheTree("/a/b/c"));

    QVERIFY(tree.isFullBackup("/a/b/d"));
    QVERIFY(!tree.isInTheTree("/a/b/d"));

    QVERIFY(tree.isFullBackup("/a/b"));
    QVERIFY(tree.isInTheTree("/a/b"));

    QVERIFY(tree.isFullBackup("/k/l/m"));
    QVERIFY(tree.isInTheTree("/k/l/m"));
}

void FileSystemTreeTest::simpleAddRootTest() {
    BackupTree tree;
    tree.addBackupPath("/");

    QVERIFY(tree.isFullBackup("/"));
    QVERIFY(tree.isInTheTree("/"));
    QVERIFY(!tree.isPartialBackup("/"));
}

void FileSystemTreeTest::addRootTest() {
    BackupTree tree;

    QVERIFY(!tree.isFullBackup("/"));
    QVERIFY(!tree.isInTheTree("/"));
    QVERIFY(!tree.isPartialBackup("/"));

    tree.addBackupPath("/a/b/c");

    QVERIFY(!tree.isFullBackup("/"));
    QVERIFY(!tree.isInTheTree("/"));
    QVERIFY(tree.isPartialBackup("/"));
}

void FileSystemTreeTest::addRootRemovesChildrenTest() {
    BackupTree tree;

    tree.addBackupPath("/a/b/c");
    tree.addBackupPath("/");

    QVERIFY(tree.isFullBackup("/a/b/c"));
    QVERIFY(!tree.isInTheTree("/a/b/c"));
}
