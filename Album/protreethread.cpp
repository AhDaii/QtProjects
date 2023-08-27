#include "protreethread.h"

#include <QDir>


ProTreeThread::ProTreeThread(const QString &src_path, const QString &dist_path, QTreeWidgetItem *parent_item,
                             int file_count, QTreeWidget *self, QTreeWidgetItem *root, QObject *parent):
    QThread(parent), _src_path(src_path), _dist_path(dist_path), _self(self), _root(root), _parent_item(parent_item), _bstop(false)
{

}

ProTreeThread::~ProTreeThread()
{

}

void ProTreeThread::run()
{

}

void ProTreeThread::createProTree(const QString &src_path, const QString &dist_path, QTreeWidgetItem *parent_item, QTreeWidget *self, QTreeWidgetItem *root, QObject *parent)
{
    if (_bstop) {
        return ;
    }
    bool need_copy = true;
    if (src_path == dist_path)
        need_copy = false;
    QDir dir;
}
