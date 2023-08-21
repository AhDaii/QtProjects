#include "stringlistmodel.h"

StringListModel::StringListModel(const QStringList &strings, QObject *parent)
    : QAbstractListModel{parent}, stringList{strings}
{

}

int StringListModel::rowCount(const QModelIndex &parent) const
{
    return stringList.count();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= stringList.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return stringList.at(index.row());
    else
        return QVariant();

}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool StringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool StringListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    QAbstractListModel::beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++ i)
        stringList.insert(row, "");
    QAbstractListModel::endInsertRows();
}

bool StringListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    QAbstractListModel::beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++ i)
        stringList.removeAt(row);
    QAbstractListModel::endRemoveRows();
}
