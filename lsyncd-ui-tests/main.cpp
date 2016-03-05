#include <QCoreApplication>
#include <QtTest/QtTest>
#include "configgeneratortests.h"

#define QTEST_CLASS(TestObject, vName, result) \
    TestObject vName; \
    result = result + QTest::qExec(&vName, argc, argv); \

int main(int argc, char *argv[]) {
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    int result = 0;

    QTEST_CLASS(ConfigGeneratorTests, cgt, result);

    QThread::sleep(1);

    return result;
}
