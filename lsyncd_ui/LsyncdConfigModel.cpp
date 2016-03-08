#include "LsyncdConfigModel.h"
#include "BackupListModel.h"
#include "BackupItem.h"
#include <QString>
#include <QUrl>
#include <QTextStream>
#include <QFile>

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

QString LsyncdConfigModel::generateTargetPath(QString backupDisk, QString source)
{
    if (source == backupDisk)
        return source;
    else return backupDisk + source;

}

void LsyncdConfigModel::useBackupPath(const QUrl &url){
    QString newBackupPath = url.toLocalFile();
    setBackupPath(newBackupPath);
}

QString LsyncdConfigModel::createConfig()
{
    QByteArray config = "";
    int size = m_BackupElements->rowCount();
    QString sourcePath;

    QTextStream stream(&config);
    stream << "settings {" << endl <<
              "    logfile = \"/tmp/lsyncd.log\"," << endl <<
              "    statusFile = \"/tmp/lsyncd.status\"," << endl <<
              "    nodaemon = true," << endl <<
              "}" << endl;

    for (int i = 0; i < size; i++){
        sourcePath = generateTargetPath(m_backupPath, m_BackupElements->getAddedPath(i));
        stream << "sync {" << endl <<
                  "    default.rsync," << endl <<
                  "    source = " << m_BackupElements->getAddedPath(i) << "," << endl <<
                  "    target = " << sourcePath << "," << endl <<
                  "}" << endl;

    }

    return config;
}

void LsyncdConfigModel::saveToFile()
{
    int size = m_BackupElements->rowCount();
    QFile file(m_savedFilePath);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << "settings {" << endl <<
              "    logfile = \"/tmp/lsyncd.log\"," << endl <<
              "    statusFile = \"/tmp/lsyncd.status\"," << endl <<
              "    nodaemon = true," << endl <<
              "}" << endl;

    for (int i = 0; i < size; i++){
        QString sourcePath = generateTargetPath(m_backupPath, m_BackupElements->getAddedPath(i));
        stream << "sync {" << endl <<
                  "    default.rsync," << endl <<
                  "    source = " << m_BackupElements->getAddedPath(i) << "," << endl <<
                  "    target = " << sourcePath << "," << endl <<
                  "}" << endl;

    }
}

void LsyncdConfigModel::readFileLocation(const QUrl &url)
{
    m_savedFilePath = url.toLocalFile();
}
