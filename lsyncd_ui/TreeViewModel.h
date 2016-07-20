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
        IsInTheTreeRole = Qt::DisplayRole + 10,
        IsPartialBackupRole,
        IsFullBackupRole
    };

    Q_INVOKABLE QString getFilePath(const QModelIndex &index) const { return QFileSystemModel::filePath(index); }
    Q_INVOKABLE void switchPath(const QModelIndex &currentIndex);

public slots:
    void onPathSwitched(const QString &path);

    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

private:
    void updatePathByIndex(const QModelIndex &currentIndex);

private:
    BackupListModel *m_BackupModel;
};

#endif // TREEVIEWMODEL_H
