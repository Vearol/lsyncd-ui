#ifndef BACKUPITEM
#define BACKUPITEM

#include <QString>

class BackupItem {
public:
    BackupItem() {}
    BackupItem(const QString &path);

    enum BackupType { BackupTypeFile, BackupTypeDirectory };

public:
    const QString &getBackupPath() const { return m_BackupPath; }
    BackupType getItemType() const { return m_ItemType; }

    bool isFile() const { return m_ItemType == BackupTypeFile; }
    bool isDirectory() const { return m_ItemType == BackupTypeDirectory; }

private:
    QString m_BackupPath;
    BackupType m_ItemType;
};

#endif // BACKUPITEM

