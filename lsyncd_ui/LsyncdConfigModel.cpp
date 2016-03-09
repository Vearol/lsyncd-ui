#include "LsyncdConfigModel.h"
#include <QString>
#include <QUrl>
#include <QTextStream>
#include <QFile>
#include "BackupListModel.h"
#include "BackupItem.h"
#include "pathhelpers.h"

LsyncdConfigModel::LsyncdConfigModel(){
}

LsyncdConfigModel::~LsyncdConfigModel(){
}


QString LsyncdConfigModel::readBackupPath() const
{
    return m_BackupPath;
}

void LsyncdConfigModel::setBackupPath(const QString &backupPath)
{
    if (m_BackupPath == backupPath)
        return;

    m_BackupPath = backupPath;
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
        const QString &itemsPath = m_BackupElements->getAddedPath(i);
        sourcePath = Helpers::generateTargetPath(m_BackupPath, itemsPath);
        stream << "sync {" << endl <<
                  "    default.rsync," << endl <<
                  "    source = " << itemsPath << "," << endl <<
                  "    target = " << sourcePath << "," << endl <<
                  "}" << endl;
    }

    m_LastConfig = QString(config);

    return config;
}

void LsyncdConfigModel::saveToFile()
{
    QFile file(m_savedFilePath);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << m_LastConfig;
}

void LsyncdConfigModel::readFileLocation(const QUrl &url)
{
    m_savedFilePath = url.toLocalFile();
}
