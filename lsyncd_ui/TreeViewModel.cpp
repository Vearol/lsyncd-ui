#include "TreeViewModel.h"

TreeViewModel::TreeViewModel(BackupListModel *backupModel, QObject *parent):
    QFileSystemModel(parent),
    m_BackupModel(backupModel)
{
}

void TreeViewModel::switchPath(const QString &path, const QModelIndex &currentIndex) {
    m_BackupModel->switchPath(path);
    emit dataChanged(currentIndex, currentIndex, QVector<int>());
}

QVariant TreeViewModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) { return QVariant(); }

    switch (role) {
    case IsInTheTreeRole: {
        QString filepath = getFilePath(index);
        return m_BackupModel->isInTheTree(filepath);
    }
    case IsPartialBackup: {
        QString filepath = getFilePath(index);
        return m_BackupModel->isPartialBackup(filepath);
    }
    case IsFullBackup:{
        QString filepath = getFilePath(index);
        return m_BackupModel->isFullBackup(filepath);
    }
    default:
        return QFileSystemModel::data(index, role);
    }
}

QHash<int, QByteArray> TreeViewModel::roleNames() const {
    QHash<int, QByteArray> names = QFileSystemModel::roleNames();
    names[IsInTheTreeRole] = "isInTheTree";
    names[IsPartialBackup] = "isPartialBackup";
    names[IsFullBackup] = "isFullBackup";
    return names;
}
