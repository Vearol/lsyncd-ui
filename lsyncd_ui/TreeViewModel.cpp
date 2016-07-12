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
    bool isAdded = false;
    int size = m_BackupElements->rowCount();

    for (int i = 0; i < size; i++){
        if (m_BackupElements->getAddedFile(i) == filePath)
            isAdded = true;
    }

    return isAdded;
}


