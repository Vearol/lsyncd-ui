#ifndef BACKUPLISTMODEL_H
#define BACKUPLISTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>
#include <QObject>
#include <QUrl>
#include <QSet>
#include "BackupItem.h"

class BackupListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    BackupListModel();
    virtual ~BackupListModel();

    enum BackupListModel_Roles {
        ItemPathRole = Qt::DisplayRole + 1,
        IsFileRole
    };

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

public:
    Q_INVOKABLE void addItems(const QList<QUrl> &urls);
    Q_INVOKABLE void removeAll();
    Q_INVOKABLE void removeSingle(int index);

private:
    QVector<BackupItem*> m_BackupItems;
    QSet<QString> m_AddedPaths;
};

#endif // BACKUPLISTMODEL_H
