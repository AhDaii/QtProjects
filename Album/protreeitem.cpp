#include "protreeitem.h"
#include "const.h"


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
    return _path;
}

QTreeWidgetItem *ProTreeItem::getRoot()
{
    return _root;
}

void ProTreeItem::setPreItem(QTreeWidgetItem *item)
{
    _pre_item = item;
}

void ProTreeItem::setNextItem(QTreeWidgetItem *item)
{
    _next_item = item;
}

ProTreeItem *ProTreeItem::getPreItem()
{
    return dynamic_cast<ProTreeItem*>(_pre_item);
}

ProTreeItem *ProTreeItem::getNextItem()
{
    return dynamic_cast<ProTreeItem*>(_next_item);
}

ProTreeItem *ProTreeItem::getLastPicChild()
{
    if (this->type() == TreeItemPic) {
        return nullptr;
    }
    auto child_count = this->childCount();
    if (child_count == 0) {
        return nullptr;
    }

    for (int i = child_count - 1; i >= 0; -- i) {
        auto* last_child = this->child(i);
        auto* last_tree_item = dynamic_cast<ProTreeItem*>(last_child);
        int item_type = last_tree_item->type();
        if (item_type == TreeItemPic) {
            return last_tree_item;
        }
        last_child = last_tree_item->getLastPicChild();
        if (!last_child) {
            continue;
        }
        last_tree_item = dynamic_cast<ProTreeItem*>(last_child);
        return last_tree_item;
    }
    return nullptr;
}

ProTreeItem *ProTreeItem::getFirstPicChild()
{
    if (this->type() == TreeItemPic) {
        return nullptr;
    }
    auto child_count = this->childCount();
    if (child_count == 0) {
        return nullptr;
    }

    for (int i = 0; i < child_count; ++ i) {
        auto* first_child = this->child(i);
        auto* first_tree_item = dynamic_cast<ProTreeItem*>(first_child);
        int item_type = first_tree_item->type();
        if (item_type == TreeItemPic) {
            return first_tree_item;
        }
        first_child = first_tree_item->getFirstPicChild();
        if (!first_child) {
            continue;
        }
        first_tree_item = dynamic_cast<ProTreeItem*>(first_child);
        return first_tree_item;
    }
    return nullptr;
}
