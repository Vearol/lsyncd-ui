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
        return (m_BackupElements->getAddedFile(i) == filePath);
    }
    return false;

}


