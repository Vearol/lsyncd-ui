#include "BackupListModel.h"
#include "BackupItem.h"
#include "LsyncdConfigModel.h"
#include <QUrl>
#include <QDir>
#include <QList>
#include <iterator>
#include <QString>
#include <QDebug>
#include "enums.h"

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
            m_FileNames.push_back(urls[i].fileName());
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

    emit rowCountIsChanged();
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

    emit rowCountIsChanged();
}

void BackupListModel::removeSingle(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    QString path = m_BackupItems[index]->getBackupPath();

    delete m_BackupItems[index];
    m_AddedPaths.remove(path);
    m_BackupItems.remove(index);

    endRemoveRows();

    emit rowCountIsChanged();
}

bool BackupListModel::isEmpty()
{
    return m_BackupItems.size() == 0;
}

const QString &BackupListModel::getAddedFile(int index) const
{
    return m_FileNames[index];
}

NodeBackupType BackupListModel::retrieveBackupType(const QString &path) const
{
    if (m_AddedPaths.contains(path)) { return BackupTypeFull; }

    QDir dir(path);
    while (dir.cdUp()) {
        const QString &currPath = dir.path();
        if (m_AddedPaths.contains(currPath)) { return BackupTypeFull; }
    }

    dir.cd(path);
    auto entries = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for (auto &entry: entries) {
        QString childPath = entry.absolutePath();
        if (m_AddedPaths.contains(childPath)) { return BackupTypeFull; }
    }
}

const QString &BackupListModel::getAddedPath(int index) const
{
    return m_BackupItems[index]->getBackupPath();
}






