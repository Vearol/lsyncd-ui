#ifndef CONFIGGENERATORTESTS_H
#define CONFIGGENERATORTESTS_H

#include <QObject>
#include <QtTest/QtTest>
#include <QThread>

class ConfigGeneratorTests : public QObject
{
    Q_OBJECT
private slots:
    void generateConfigWithNoItemsTest();
    void generateConfigWithOneItemTest();
    void generateConfigWithSeveralItemsTest();
};

#endif // CONFIGGENERATORTESTS_H
