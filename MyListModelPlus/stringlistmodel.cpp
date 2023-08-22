#include "stringlistmodel.h"
#include <QIODevice>
#include <QMimeData>
#include <QDataStream>
#include <QByteArray>

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
        return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled;
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

QStringList StringListModel::mimeTypes() const
{
    QStringList types;
    types << "application/zack.list";
    return types;
}

QMimeData *StringListModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodeData;
    QDataStream stream(&encodeData, QIODevice::WriteOnly);
    foreach(const QModelIndex &index, indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }
    mimeData->setData("application/zack.list", encodeData);
    return mimeData;
}

bool StringListModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;
    if (!data->hasFormat("application/zack.list"))
        return false;
    if (column > 0)
        return false;

    int beginRow;
    if (row != -1)
        beginRow = row;
    else if(parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());
    QByteArray encodeData = data->data("application/zack.list");
    QDataStream stream(&encodeData, QIODevice::ReadOnly);
    QStringList newItems;
    int rows = 0;
    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        newItems << text;
        ++ rows;
    }
    insertRows(beginRow, rows, QModelIndex());
    foreach(const QString &text, newItems) {
        QModelIndex idx = index(beginRow, 0, QModelIndex());
        setData(idx, text);
        ++ beginRow;
    }
    return true;
}

Qt::DropActions StringListModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
