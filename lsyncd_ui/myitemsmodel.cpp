#include "myitemsmodel.h"

MyItemsModel::MyItemsModel():
    QAbstractListModel()
{
}

int MyItemsModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_Items.length();
}

QVariant MyItemsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    const MyItem &item = m_Items.at(row);

    if (role == ItemName) {
        return item.m_Name;
    } else if (role == ItemSurname) {
        return item.m_Surname;
    } else {
        return QVariant();
    }
}

QHash<int, QByteArray> MyItemsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemName] = "super_name";
    roles[ItemSurname] = "surname";
    return roles;
}

void MyItemsModel::addItems()
{
    int n = 10;
    beginInsertRows(QModelIndex(), 0, n - 1);

    while (n--) {
        m_Items.append(MyItem("Taras", "Kushnir"));
    }

    endInsertRows();
}
/*
void MyItemsModel::changeItems()
{
    int size = m_Items.length();
    for (int i = 0; i < size; ++i) {
        m_Items[i].m_Name = "NoName";
    }

    emit dataChanged(this->index(0), this->index(size - 1), QVector<int>() << ItemName);
}
*/
