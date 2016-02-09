#include <BackupItem.h>
#include "LsyncdConfigModel.h"
#include <QString>
#include <QUrl>

LsyncdConfigModel::LsyncdConfigModel(){
}

LsyncdConfigModel::~LsyncdConfigModel(){
}

void LsyncdConfigModel::backupPathChanged() {
}



QString LsyncdConfigModel::readBackupPath() const
{
    return m_backupPath;
}

void LsyncdConfigModel::setBackupPath(QString backupPath)
{
    if (m_backupPath == backupPath)
        return;

    m_backupPath = backupPath;
    emit backupPathChanged();
}

void LsyncdConfigModel::addBackupPath(const QUrl &url){
    QString newBackupPath = url.toLocalFile();

    setBackupPath(newBackupPath);
}
