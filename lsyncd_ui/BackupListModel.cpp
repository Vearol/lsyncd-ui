#include "BackupListModel.h"
#include "BackupItem.h"

BackupListModel::BackupListModel():
    QAbstractListModel()
{
}

int BackupListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_BackupItems.length();
}

QVariant BackupListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row >= m_BackupItems.length()) return QVariant();

    const BackupItem &item = m_BackupItems.at(row);

    if (role == ItemPath) {
        return item.getBackupPath();
    } else {
        return QVariant();
    }
}

QHash<int, QByteArray> BackupListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemPath] = "path";
    return roles;
}
