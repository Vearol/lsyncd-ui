
#include <QCoreApplication>
#include <QtTest/QtTest>
#include <QThread>
#include "configgeneratortests.h"
#include "targetpathtests.h"
#include "filesystemtreetest.h"

#define QTEST_CLASS(TestObject, vName, result) \
    TestObject vName; \
    result = result + QTest::qExec(&vName, argc, argv); \

int main(int argc, char *argv[]) {
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    int result = 0;

    QTEST_CLASS(ConfigGeneratorTests, cgt, result);
    QTEST_CLASS(TargetPathTests, tpt, result);
    QTEST_CLASS(FileSystemTreeTest, fstt, result);

    QThread::sleep(1);

    return result;
}
