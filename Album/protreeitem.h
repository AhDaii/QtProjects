#ifndef PROTREEITEM_H
#define PROTREEITEM_H

#include <QTreeWidgetItem>
#include <QTreeWidget>

class ProTreeItem : public QTreeWidgetItem
{
public:
    ProTreeItem(QTreeWidget *view, const QString &name, const QString &path, int type = Type);
    ProTreeItem(QTreeWidgetItem *parent, const QString &name, const QString &path,
                QTreeWidgetItem *root, int type = Type);

private:
    QString _path, _name;
    QTreeWidgetItem *_pre_item, *_next_item, *_root;
};

#endif // PROTREEITEM_H
