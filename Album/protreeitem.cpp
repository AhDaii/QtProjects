#include "protreeitem.h"


ProTreeItem::ProTreeItem(QTreeWidget *view, const QString &name, const QString &path, int type):
    _path(path), _name(name), _root(this), _pre_item(nullptr), _next_item(nullptr)
{

}

ProTreeItem::ProTreeItem(QTreeWidgetItem *parent, const QString &name, const QString &path, QTreeWidgetItem *root, int type):
    _path(path), _name(name), _root(root), _pre_item(nullptr), _next_item(nullptr)
{

}
