#include "BackupItem.h"
#include <QFileInfo>

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
