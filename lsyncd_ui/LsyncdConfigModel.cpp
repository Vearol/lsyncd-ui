#include "LsyncdConfigModel.h"
#include "BackupListModel.h"
#include "BackupItem.h"
#include <QString>
#include <QUrl>

LsyncdConfigModel::LsyncdConfigModel(){
}

LsyncdConfigModel::~LsyncdConfigModel(){
}


QString LsyncdConfigModel::readBackupPath() const
{
    return m_backupPath;
}

void LsyncdConfigModel::setBackupPath(const QString &backupPath)
{
    if (m_backupPath == backupPath)
        return;

    m_backupPath = backupPath;
    emit backupPathChanged();
}

void LsyncdConfigModel::setBackupElements(BackupListModel *BackupElements)
{
    m_BackupElements = BackupElements;
}

void LsyncdConfigModel::useBackupPath(const QUrl &url){
    QString newBackupPath = url.toLocalFile();
    setBackupPath(newBackupPath);
}

QString LsyncdConfigModel::createConfig()
{
    QString config = "";
    int size = m_BackupElements->rowCount();

    config += "settings {\n  logfile =,\n  statusFile =,\n  nodeamon = true,\n}";

    for (int i = 0; i < size; i++){
        config += "sync {\n  default.rsync,\n  source = " + m_backupPath + "\n  target = " + m_BackupElements->getAddedPath(i)  + ",\n}";
    }

    return config;
}
