#include "TreeViewModel.h"
#include <QDebug>

TreeViewModel::TreeViewModel(BackupListModel *backupModel, QObject *parent):
    QFileSystemModel(parent),
    m_BackupModel(backupModel)
{
}

void TreeViewModel::switchPath(const QModelIndex &currentIndex) {
    if (!currentIndex.isValid()) { return; }

    QString path = this->filePath(currentIndex);
    m_BackupModel->switchPath(path);

    this->updatePathByIndex(currentIndex);
}

void TreeViewModel::onPathSwitched(const QString &path) {
    auto currIndex = this->index(path);
    this->updatePathByIndex(currIndex);
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

void TreeViewModel::updatePathByIndex(const QModelIndex &currentIndex) {
    Q_ASSERT(currentIndex.isValid());

    QVector<int> rolesToUpdate;
    rolesToUpdate << IsInTheTreeRole << IsPartialBackupRole << IsFullBackupRole;
    auto curr = currentIndex;

    do {
        emit dataChanged(curr, curr, rolesToUpdate);
        curr = this->parent(curr);
    } while (curr.isValid());
}
