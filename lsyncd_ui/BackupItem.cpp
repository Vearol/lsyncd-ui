#include "BackupItem.h"
#include <QFileInfo>
#include <QDir>

BackupItem::BackupItem(const QString &path):
    m_BackupPath(path)
{
    QFileInfo fileInfo(path);
    if (fileInfo.isFile()) {
        m_ItemType = BackupTypeFile;
    } else {
        m_ItemType = BackupTypeDirectory;
    }
}

bool BackupItem::isChildOf(const QString &path)
{
    //return this->getBackupPath().startsWith(path);
    bool isChild = false;
    QDir child(this->getBackupPath());

    while (child.cdUp()){
        if (child.path() == path){
            isChild = true;
            break;
        }
    }
    return isChild;
}
