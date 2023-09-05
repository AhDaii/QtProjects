#include "prelistitem.h"


PreListItem::PreListItem(const QIcon &icon, const QString &text, const int &index,
                         QListWidget *listview, int type):
    QListWidgetItem(icon, "", listview, type), _path(text), _index(index)
{

}

int PreListItem::getIndex()
{
    return _index;
}

QString PreListItem::getPath()
{
    return _path;
}
