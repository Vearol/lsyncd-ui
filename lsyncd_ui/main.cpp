#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "BackupListModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BackupListModel model;

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("backupModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
