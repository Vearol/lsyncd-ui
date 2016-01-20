#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "myitemsmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MyItemsModel model;

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("myModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
