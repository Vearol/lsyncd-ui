#include "TreeViewModel.h"

TreeViewModel::TreeViewModel()
{
}

void TreeViewModel::copyBackupElementsForTree(BackupListModel *BackupElements)
{
    m_BackupElements = BackupElements;
}

bool TreeViewModel::isAdded(const QString &filePath)
{
    int size = m_BackupElements->rowCount();
    for (int i = 0; i < size; i++){
        if (m_BackupElements->getAddedPath(i) == filePath)
            return true;
    }
    return false;
    //return m_BackupElements->m_AddedPaths.contains(filePath);
}
