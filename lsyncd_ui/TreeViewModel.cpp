#include "TreeViewModel.h"

TreeViewModel::TreeViewModel(BackupListModel *backupModel, QObject *parent):
    QFileSystemModel(parent),
    m_BackupModel(backupModel)
{
}

void TreeViewModel::switchPath(const QModelIndex &currentIndex) {
    QString path = this->filePath(currentIndex);
    m_BackupModel->switchPath(path);

    emit dataChanged(currentIndex, currentIndex, QVector<int>());
    emit dataChanged(parent(currentIndex), parent(currentIndex), QVector<int>());
}

void TreeViewModel::updateModel()
{
    /*int size = m_BackupModel->rowCount();
    if (size != 0) {
        QString last = m_BackupModel->getAddedPath(size - 1);
        emit dataChanged (index(rootPath()), index(last), QVector<int>());
    }*/
}

QVariant TreeViewModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) { return QVariant(); }

    QString filepath = getFilePath(index);

    switch (role) {
    case IsInTheTreeRole: return m_BackupModel->isInTheTree(filepath);
    case IsPartialBackupRole: return m_BackupModel->isPartialBackup(filepath);
    case IsFullBackupRole: return m_BackupModel->isFullBackup(filepath);
    default: return QFileSystemModel::data(index, role);
    }
}

QHash<int, QByteArray> TreeViewModel::roleNames() const {
    QHash<int, QByteArray> names = QFileSystemModel::roleNames();
    names[IsInTheTreeRole] = "isInTheTree";
    names[IsPartialBackupRole] = "isPartialBackup";
    names[IsFullBackupRole] = "isFullBackup";
    return names;
}
