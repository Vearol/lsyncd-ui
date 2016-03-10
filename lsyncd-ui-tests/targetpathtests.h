#ifndef TARGETPATHTESTS_H
#define TARGETPATHTESTS_H

#include <QObject>
#include <QtTest/QtTest>

class TargetPathTests : public QObject
{
    Q_OBJECT
private slots:
    void simplePathTest();
    void rootBackupPathTest();
    void rootItemsPathTest();
};

#endif // TARGETPATHTESTS_H
