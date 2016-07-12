#ifndef BACKUPLISTMODEL_H
#define BACKUPLISTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>
#include <QObject>
#include <QUrl>
#include <QSet>
#include "BackupItem.h"
#include "enums.h"

class BackupListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int itemsCount READ rowCount NOTIFY rowCountIsChanged)

public:
    BackupListModel();
    virtual ~BackupListModel();

    enum BackupListModel_Roles {
        ItemPathRole = Qt::DisplayRole + 1,
        IsFileRole
    };

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

public:
    Q_INVOKABLE void addItems(const QList<QUrl> &urls);  
    Q_INVOKABLE void removeAll();
    Q_INVOKABLE void removeSingle(int index);
    Q_INVOKABLE bool isEmpty();
    Q_INVOKABLE bool isFullyBackedUp(const QString &path) const { return retrieveBackupType(path) == BackupTypeFull; }
    Q_INVOKABLE bool isPartiallyBackedUp(const QString &path) const { return retrieveBackupType(path) == BackupTypePartial; }
    Q_INVOKABLE bool isNotBackedUp(const QString &path) const { return retrieveBackupType(path) == BackupTypeNone; }
    const QString &getAddedPath(int index) const;
    const QString &getAddedFile(int index) const;

signals:
    void rowCountIsChanged();

private:
    NodeBackupType retrieveBackupType(const QString &path) const;

private:
    QVector<BackupItem*> m_BackupItems;
    QSet<QString> m_AddedPaths;

    QVector<QString> m_FileNames;
};


#endif // BACKUPLISTMODEL_H
