#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include "BackupListModel.h"
#include "LsyncdConfigModel.h"
#include "TreeViewModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BackupListModel model;
    LsyncdConfigModel lsmodel;
    TreeViewModel fsmodel;

    lsmodel.copyBackupElementsForConfig(&model);
    fsmodel.copyBackupElementsForTree(&model);
    fsmodel.setRootPath("/");
    fsmodel.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("backupModel", &model);
    context->setContextProperty("lsyncdConfigModel", &lsmodel);
    context->setContextProperty("fileSystemModel", &fsmodel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}



