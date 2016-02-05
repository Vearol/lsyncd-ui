#include <BackupItem.h>
#include "LsyncdConfigModel.h"
#include <QString>
#include <QUrl>

LsyncdConfigModel::LsyncdConfigModel(){
}

LsyncdConfigModel::~LsyncdConfigModel(){
}

QString LsyncdConfigModel::readBackupPath(const QList<QUrl> &urls)
{
    QString diskPath = urls[0].toLocalFile();
    outputPath = BackupItem(diskPath);

    return outputPath.getBackupPath();

    //emit backupPathChanged();
}
