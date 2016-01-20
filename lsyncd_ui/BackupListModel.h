#ifndef BACKUPLISTMODEL_H
#define BACKUPLISTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>
#include <QObject>
#include <QUrl>
#include "BackupItem.h"

class BackupListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    BackupListModel();

    enum BackupListModel_Roles {
        ItemPath = Qt::DisplayRole + 1
    };

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

public:
    //Q_INVOKABLE void addItems(const QList<QUrl> &urls);

private:
    QVector<BackupItem> m_BackupItems;
};

#endif // BACKUPLISTMODEL_H
