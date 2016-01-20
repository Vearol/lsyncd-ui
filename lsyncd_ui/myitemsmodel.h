#ifndef MYITEMSMODEL_H
#define MYITEMSMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>
#include <QObject>

struct MyItem {
    MyItem() {}
    MyItem(const QString &name, const QString &surname):
        m_Name(name),
        m_Surname(surname)
    {
    }

    QString m_Name;
    QString m_Surname;
};

class MyItemsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MyItemsModel();

    enum MyItemsModel_Roles {
        ItemName = Qt::DisplayRole + 1,
        ItemSurname
    };

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

public:
    Q_INVOKABLE void addItems();
    Q_INVOKABLE void changeItems();

private:
    QVector<MyItem> m_Items;
};

#endif // MYITEMSMODEL_H
