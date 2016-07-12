#ifndef TREEVIEWMODEL_H
#define TREEVIEWMODEL_H

#include <QFileSystemModel>
#include "BackupListModel.h"

class TreeViewModel: public QFileSystemModel
{
    Q_OBJECT
public:
    TreeViewModel();

    void copyBackupElementsForTree(BackupListModel *BackupElements);

    Q_INVOKABLE bool isAdded(const QString &filePath);
    Q_INVOKABLE QString getFilePath(const QModelIndex &index) const { return QFileSystemModel::filePath(index); }

private:
    BackupListModel *m_BackupElements;
};

#endif // TREEVIEWMODEL_H
