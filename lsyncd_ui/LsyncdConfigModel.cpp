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
        sourcePath = m_BackupElements->getAddedPath(i)/*.remove(0,1)*/;
        stream << "sync {" << endl <<
                  "    default.rsync," << endl <<
                  "    source = " << m_BackupElements->getAddedPath(i) << "," << endl <<
                  "    target = " << m_backupPath + sourcePath << "," << endl <<
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
    stream << "settings {" << endl << "  logfile =," << endl << "  statusFile =," << endl << "  nodeamon = true," << endl << "} " << endl << endl;

    for (int i = 0; i < size; i++){
        stream << "sync {" << endl << "  default.rsync," << endl << "  source = " << m_backupPath << endl << "  target = " << m_BackupElements->getAddedPath(i) << "," << endl << "}" << endl;
    }
}

void LsyncdConfigModel::readFileLocation(const QUrl &url)
{
    m_savedFilePath = url.toLocalFile();
}
