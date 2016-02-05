#ifndef LSYNCDCONFIGMODEL
#define LSYNCDCONFIGMODEL

#include <QObject>
#include <QString>
#include <QUrl>
#include <BackupItem.h>

class LsyncdConfigModel : public QObject
{
   Q_PROPERTY(QString backupPath READ readBackupPath  NOTIFY backupPathChanged)

public:

    LsyncdConfigModel();
    virtual ~LsyncdConfigModel();

    Q_INVOKABLE QString readBackupPath(const QList<QUrl> &urls);

signals:
    void backupPathChanged();

private:
    QString m_backupPath;
    BackupItem outputPath;
};

#endif // LSYNCDCONFIGMODEL

