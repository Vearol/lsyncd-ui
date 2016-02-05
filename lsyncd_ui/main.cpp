#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "BackupListModel.h"
#include "LsyncdConfigModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BackupListModel model;
    LsyncdConfigModel lsmodel;

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("backupModel", &model);
    context->setContextProperty("lsyncdConfigModel", &lsmodel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
