#ifndef LSYNCDCONFIGMODEL
#define LSYNCDCONFIGMODEL

#include <QObject>
#include <QString>
#include <QUrl>
#include "BackupListModel.h"

class LsyncdConfigModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString backupPath READ readBackupPath WRITE setBackupPath NOTIFY backupPathChanged)
public:
    LsyncdConfigModel();
    virtual ~LsyncdConfigModel();

    QString readBackupPath() const;
    void setBackupPath(const QString &backupPath);
    void setBackupElements(BackupListModel *BackupElements);

    Q_INVOKABLE void useBackupPath(const QUrl &url);
    Q_INVOKABLE QString createConfig();

signals:
    void backupPathChanged();

private:
    QString m_backupPath;
    BackupListModel *m_BackupElements;
};

#endif // LSYNCDCONFIGMODEL

