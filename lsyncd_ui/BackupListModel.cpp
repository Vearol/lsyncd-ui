#include "BackupListModel.h"
#include "BackupItem.h"
#include <QUrl>
#include <QList>
#include <iterator>
#include <QString>
#include <QDebug>

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

    QSet<QString> originalPaths;
    originalPaths.reserve(size);

    for (int i = 0; i <  size; i++){
        QString path = urls[i].toLocalFile();
        if (!m_AddedPaths.contains(path) && !originalPaths.contains(path)) {
            originalPaths.insert(path);
        }
    }

    int k = originalPaths.size();
    m_BackupItems.reserve(existingSize + k);
    m_AddedPaths.reserve(existingSize + k);

    beginInsertRows(QModelIndex(), existingSize, existingSize + k - 1);

    QSet<QString>::const_iterator i = originalPaths.constBegin();
    QSet<QString>::const_iterator end = originalPaths.constEnd();
    while (i != end) {
        const QString &path = *i;

        m_AddedPaths.insert(path);
        m_BackupItems.push_back(new BackupItem(path));

        ++i;
    }

    endInsertRows();
}

void BackupListModel::removeAll()
{
    beginResetModel();

    int size = m_BackupItems.size();
    for (int i = 0; i < size; i++){
        delete m_BackupItems[i];
    }
    m_BackupItems.clear();
    m_AddedPaths.clear();

    endResetModel();
}





