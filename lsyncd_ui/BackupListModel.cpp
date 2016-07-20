#include "BackupListModel.h"
#include "BackupItem.h"
#include "LsyncdConfigModel.h"
#include <QUrl>
#include <QDir>
#include <QList>
#include <iterator>
#include <QString>
#include <QDebug>
#include "pathhelpers.h"

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

void BackupListModel::addItems(const QList<QUrl> &urls, bool areFromList)
{
    doAddItems(urls, areFromList);
}

void BackupListModel::addSingle(const QString &path)
{
    addItems(QList<QUrl>() << QUrl::fromLocalFile(path), false);
    m_BackupTree.addBackupPath(path);
}

void BackupListModel::removeAll()
{
    beginResetModel();

    int size = m_BackupItems.size();
    for (int i = 0; i < size; i++){
        m_BackupTree.removeBackupPath(m_BackupItems[i]->getBackupPath());
        delete m_BackupItems[i];
    }
    m_BackupItems.clear();
    m_AddedPaths.clear();
    listPaths.clear();

    endResetModel();

    emit rowCountIsChanged();
}

void BackupListModel::removeSingle(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    QString pathToRemove = m_BackupItems[index]->getBackupPath();

    m_BackupTree.removeBackupPath(pathToRemove);
    BackupItem *itemToRemove = m_BackupItems.takeAt(index);
    delete itemToRemove;
    m_AddedPaths.remove(pathToRemove);
    listPaths.remove(pathToRemove);
    emit pathSwitched(pathToRemove);

    endRemoveRows();

    emit rowCountIsChanged();
}

bool BackupListModel::isEmpty()
{
    return m_BackupItems.size() == 0;
}

void BackupListModel::removeBackupPath(const QString &path)
{
    m_BackupTree.removeBackupPath(path);
}

bool BackupListModel::isFullBackup(const QString &path) const
{
    return m_BackupTree.isFullBackup(path);
}

bool BackupListModel::isPartialBackup(const QString &path) const
{
    return m_BackupTree.isPartialBackup(path);
}

bool BackupListModel::isInTheTree(const QString &path) const
{
    return m_BackupTree.isInTheTree(path);
}

bool BackupListModel::isFromTheList(const QString &path)
{
    return listPaths.contains(path);
}

void BackupListModel::switchPath(const QString &path)
{
    if (isInTheTree(path)) {
        int size = m_BackupItems.size();
        for (int i = 0; i < size; i++){
            if (m_BackupItems[i]->getBackupPath() == path) {
                removeSingle(i);
                break;
            }
        }
    } else {
        addSingle(path);
    }
}

void BackupListModel::doAddItems(const QList<QUrl> &urls, bool areFromList) {
    int size = urls.size();
    int existingSize = m_BackupItems.size();

    QSet<QString> originalPaths;
    originalPaths.reserve(size);

    bool newPathIsNotChild = true;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < existingSize; j++){
            QString urlPath = urls[i].toLocalFile();
            if (urlPath.startsWith(m_BackupItems[j]->getBackupPath())){
                newPathIsNotChild = false;
            }

            if (m_BackupItems[j]->isChildOf(urlPath)){
                removeSingle(j);
                existingSize--;
            }
        }

        if (newPathIsNotChild){
            QString path = urls[i].toLocalFile();
            if (!m_AddedPaths.contains(path) && !originalPaths.contains(path)) {
                originalPaths.insert(path);
                m_BackupTree.addBackupPath(path);
                if (areFromList) listPaths.insert(path);
            }
        }

        int k = originalPaths.size();
        m_BackupItems.reserve(existingSize + k);
        m_AddedPaths.reserve(existingSize + k);

        beginInsertRows(QModelIndex(), existingSize, existingSize + k - 1);

        QSet<QString>::const_iterator it = originalPaths.constBegin();
        QSet<QString>::const_iterator end = originalPaths.constEnd();
        while (it != end) {
            const QString &path = *it;

            m_AddedPaths.insert(path);
            m_BackupItems.push_back(new BackupItem(path));
            emit pathSwitched(path);

            ++it;
        }

        endInsertRows();

        emit rowCountIsChanged();
    }
}

const QString &BackupListModel::getAddedPath(int index) const
{
    return m_BackupItems[index]->getBackupPath();
}






