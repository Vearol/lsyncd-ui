#include "configgeneratortests.h"
#include <QUrl>
#include <QStringList>
#include "../lsyncd_ui/BackupItem.h"
#include "../lsyncd_ui/BackupListModel.h"
#include "../lsyncd_ui/LsyncdConfigModel.h"

void COMPARE_STRINGS(const QString &actual, const QString &expected) {
    if (actual.length() != expected.length()) {
        QFAIL(QString("Length of strings is different.\nActual: %1;\n-----------\nExpected: %2\n")
              .arg(actual)
              .arg(expected)
              .toStdString().c_str());
        return;
    }

    int size = actual.length();
    for (int i = 0; i < size; ++i) {
        if (actual[i] != expected[i]) {
            QFAIL(QString("Strings start to differ at index %1. Wrong part is %2")
                  .arg(i)
                  .arg(actual.mid(i, 10))
                  .toStdString().c_str());
            break;
        }
    }
}

void ConfigGeneratorTests::generateConfigWithNoItemsTest() {
    LsyncdConfigModel lsyncdModel;
    BackupListModel listModel;
    lsyncdModel.setBackupElements(&listModel);

    QStringList configLines;
    configLines << "settings {"
                << "    logfile = \"/tmp/lsyncd.log\","
                << "    statusFile = \"/tmp/lsyncd.status\","
                << "    nodaemon = true,"
                << "};"
                << "";
    QString expectedConfig = configLines.join("\n");
    QString actualConfig = lsyncdModel.createConfig();

    COMPARE_STRINGS(actualConfig, expectedConfig);
}

void ConfigGeneratorTests::generateConfigWithOneItemTest() {
    LsyncdConfigModel lsyncdModel;
    BackupListModel listModel;
    lsyncdModel.setBackupElements(&listModel);

    QList<QUrl> dirsList;
    dirsList << QUrl::fromLocalFile("/home/testuser/dir1");
    lsyncdModel.setBackupPath("/media/Data/");

    QStringList configLines;
    configLines << "settings {"
                << "    logfile = \"/tmp/lsyncd.log\","
                << "    statusFile = \"/tmp/lsyncd.status\","
                << "    nodaemon = true,"
                << "};"
                << ""
                << "sync {"
                << "    default.rsync,"
                << "    source = \"/home/testuser/dir1\","
                << "    target = \"/media/Data/home/testuser/dir1\""
                << "}"
                << "";

    QString expectedConfig = configLines.join("\n");
    QString actualConfig = lsyncdModel.createConfig();

    COMPARE_STRINGS(actualConfig, expectedConfig);
}

void ConfigGeneratorTests::generateConfigWithSeveralItemsTest() {
    LsyncdConfigModel lsyncdModel;
    BackupListModel listModel;
    lsyncdModel.setBackupElements(&listModel);

    QList<QUrl> dirsList;
    dirsList << QUrl::fromLocalFile("/home/testuser/dir1")
             << QUrl::fromLocalFile("/home/testuser/another/sophisticated/dir");
    lsyncdModel.setBackupPath("/media/Data/");

    QStringList configLines;
    configLines << "settings {"
                << "    logfile = \"/tmp/lsyncd.log\","
                << "    statusFile = \"/tmp/lsyncd.status\","
                << "    nodaemon = true,"
                << "};"
                << ""
                << "sync {"
                << "    default.rsync,"
                << "    source = \"/home/testuser/dir1\","
                << "    target = \"/media/Data/home/testuser/dir1\""
                << "}"
                << ""
                << "sync {"
                << "    default.rsync,"
                << "    source = \"/home/testuser/another/sophisticated/dir\","
                << "    target = \"/media/Data/home/testuser/another/sophisticated/dir\""
                << "}"
                << "";

    QString expectedConfig = configLines.join("\n");
    QString actualConfig = lsyncdModel.createConfig();

    COMPARE_STRINGS(actualConfig, expectedConfig);
}
