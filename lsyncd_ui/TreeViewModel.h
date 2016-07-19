#ifndef TREEVIEWMODEL_H
#define TREEVIEWMODEL_H

#include <QFileSystemModel>
#include "BackupListModel.h"

class TreeViewModel: public QFileSystemModel
{
    Q_OBJECT
public:
    TreeViewModel(BackupListModel *backupModel, QObject *parent=nullptr);

public:
    enum TreeViewModel_Roles {
        IsInTheTreeRole = Qt::DisplayRole + 10
    };

    Q_INVOKABLE QString getFilePath(const QModelIndex &index) const { return QFileSystemModel::filePath(index); }
    Q_INVOKABLE void switchPath(const QString &path, const QModelIndex &currentIndex);

    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

private:
    BackupListModel *m_BackupModel;
};

#endif // TREEVIEWMODEL_H
