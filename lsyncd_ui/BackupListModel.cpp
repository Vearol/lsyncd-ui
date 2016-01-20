#include "BackupListModel.h"
#include "BackupItem.h"
#include <QUrl>
#include <QList>

BackupListModel::BackupListModel():
    QAbstractListModel()
{
}

BackupListModel::~BackupListModel()
{
    qDeleteAll(m_BackupItems);
}

int BackupListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_BackupItems.length();
}

QVariant BackupListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row >= m_BackupItems.length()) return QVariant();

    BackupItem *item = m_BackupItems[row];

    switch (role) {
    case ItemPathRole:
        return item->getBackupPath();
    case IsFileRole:
        return item->isFile();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> BackupListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ItemPathRole] = "path";
    roles[IsFileRole] = "isfile";

    return roles;
}

void BackupListModel::addItems(const QList<QUrl> &urls)
{
    int size = urls.size();
    int existingSize = m_BackupItems.size();


    beginInsertRows(QModelIndex(), existingSize, existingSize + size - 1);

    for(int i = 0; i < size; i++){
        QString path = urls[i].toLocalFile();
        m_BackupItems.push_back(new BackupItem(path));
    }

    endInsertRows();
}




