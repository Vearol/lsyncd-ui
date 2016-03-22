#ifndef TREEVIEWMODEL_H
#define TREEVIEWMODEL_H

#include <QFileSystemModel>
#include "BackupListModel.h"

class TreeViewModel : public QFileSystemModel
{
public:
    TreeViewModel();

    void copyBackupElementsForTree(BackupListModel *BackupElements);

    Q_INVOKABLE bool isAdded(const QString &filePath);

private:
    BackupListModel *m_BackupElements;
};

#endif // TREEVIEWMODEL_H
