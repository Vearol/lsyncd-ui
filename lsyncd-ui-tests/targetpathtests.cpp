#include "targetpathtests.h"
#include "../lsyncd_ui/pathhelpers.h"

void TargetPathTests::simplePathTest() {
    QString backupPath = "/media/Data";
    QString itemsPath = "/home/testuser/directory";

    QString result = Helpers::generateTargetPath(backupPath, itemsPath);
    QCOMPARE(result, QLatin1String("/media/Data/home/testuser/directory"));
}

void TargetPathTests::rootBackupPathTest() {
    QString backupPath = "";
    QString itemsPath = "/home/testuser/directory";

    QString result = Helpers::generateTargetPath(backupPath, itemsPath);
    QCOMPARE(result, QLatin1String("/home/testuser/directory"));
}

void TargetPathTests::rootItemsPathTest() {
    QString backupPath = "/media/Data";
    QString itemsPath = "";

    QString result = Helpers::generateTargetPath(backupPath, itemsPath);
    QCOMPARE(result, QLatin1String("/media/Data"));
}
