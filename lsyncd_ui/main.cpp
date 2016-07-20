#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include "BackupListModel.h"
#include "LsyncdConfigModel.h"
#include "TreeViewModel.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);\

#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
    qSetMessagePattern("%{time hh:mm:ss.zzz} %{type} T#%{threadid} %{function} - %{message}");
#endif

    BackupListModel model;
    LsyncdConfigModel lsmodel;
    TreeViewModel fsmodel(&model);

    QObject::connect(&model, SIGNAL(pathSwitched(QString)),
                     &fsmodel, SLOT(onPathSwitched(QString)));

    lsmodel.copyBackupElementsForConfig(&model);
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



