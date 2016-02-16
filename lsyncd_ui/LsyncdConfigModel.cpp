#include "LsyncdConfigModel.h"
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

void LsyncdConfigModel::useBackupPath(const QUrl &url){
    QString newBackupPath = url.toLocalFile();
    setBackupPath(newBackupPath);
}
