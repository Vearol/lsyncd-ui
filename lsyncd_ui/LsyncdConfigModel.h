#ifndef LSYNCDCONFIGMODEL
#define LSYNCDCONFIGMODEL

#include <QObject>
#include <QString>
#include <QUrl>
#include <BackupItem.h>

class LsyncdConfigModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString backupPath READ readBackupPath WRITE setBackupPath NOTIFY backupPathChanged)
public:
    LsyncdConfigModel();
    virtual ~LsyncdConfigModel();

    QString readBackupPath() const;
    void setBackupPath(const QString &backupPath);

    Q_INVOKABLE void useBackupPath(const QUrl &url);

signals:
    void backupPathChanged();

private:
    QString m_backupPath;
};

#endif // LSYNCDCONFIGMODEL

