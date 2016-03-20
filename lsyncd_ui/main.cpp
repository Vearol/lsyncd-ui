#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "BackupListModel.h"
#include "LsyncdConfigModel.h"
#include <QFileSystemModel>
#include <QTreeView>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BackupListModel model;
    LsyncdConfigModel lsmodel;
    lsmodel.setBackupElements(&model);
    QFileSystemModel fsmodel;
    fsmodel.setRootPath("/");

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("backupModel", &model);
    context->setContextProperty("lsyncdConfigModel", &lsmodel);
    context->setContextProperty("fileSystemModel", &fsmodel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}



