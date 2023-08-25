#include "protreeitem.h"


ProTreeItem::ProTreeItem(QTreeWidget *view, const QString &name, const QString &path, int type):
    QTreeWidgetItem(view, type),_path(path), _name(name), _root(this), _pre_item(nullptr), _next_item(nullptr)
{

}

ProTreeItem::ProTreeItem(QTreeWidgetItem *parent, const QString &name, const QString &path, QTreeWidgetItem *root, int type):
    QTreeWidgetItem(parent, type), _path(path), _name(name), _root(root), _pre_item(nullptr), _next_item(nullptr)
{
    
}

const QString &ProTreeItem::getPath()
{
    
}

QTreeWidgetItem *ProTreeItem::getRoot()
{
    
}

void ProTreeItem::setPreItem(QTreeWidgetItem *item)
{
    
}

void ProTreeItem::setNextItem(QTreeWidgetItem *item)
{
    
}

ProTreeItem *ProTreeItem::getPreItem()
{
    
}

ProTreeItem *ProTreeItem::getNextItem()
{
    
}

ProTreeItem *ProTreeItem::getLastPicChild()
{
    
}

ProTreeItem *ProTreeItem::getFirstPicChild()
{
    
}
