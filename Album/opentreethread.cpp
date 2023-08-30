#include "opentreethread.h"
#include "const.h"
#include "protreeitem.h"

#include <QDir>

OpenTreeThread::OpenTreeThread(const QString &src_path, int file_count, QTreeWidget *self, QObject *parent):
    QThread(parent), _src_path(src_path), _file_count(file_count), _self(self), _root(nullptr), _bstop(false),
    _pre_item(nullptr)
{

}

void OpenTreeThread::openProTree(const QString &src_path, int &file_count, QTreeWidget *self)
{
    QDir dir(src_path);
    auto name = dir.dirName();
    auto* item = new ProTreeItem(self, name, src_path, TreeItemPro);
    item->setData(0, Qt::DisplayRole, name);
    item->setData(0, Qt::DecorationRole, QIcon(":/icon/dir.png"));
    item->setData(0, Qt::ToolTipRole, src_path);
    _root = item;

    RecursiveProTree(src_path, file_count, self, _root, item, _pre_item);
}

void OpenTreeThread::run()
{
    openProTree(_src_path, _file_count, _self);
    if (_bstop) {
        auto path = dynamic_cast<ProTreeItem*>(_root)->getPath();
        auto index = _self->indexOfTopLevelItem(_root);
        delete _self->takeTopLevelItem(index);
//        QDir dir(path);
//        dir.removeRecursively();
        return ;
    }
}

void OpenTreeThread::RecursiveProTree(const QString &src_path, int &file_count, QTreeWidget *self, QTreeWidgetItem *root, QTreeWidgetItem *parent, QTreeWidgetItem *preitem)
{
    QDir dir(src_path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Name);
    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.length(); ++ i) {
        if (_bstop) return;
        QFileInfo fileInfo = list.at(i);
        bool isDir = fileInfo.isDir();
        if (isDir) {
            if (_bstop) return ;
            ++ file_count;
            emit SigUpdateProgress(file_count);
            auto* item = new ProTreeItem(parent, fileInfo.fileName(), fileInfo.absoluteFilePath(),
                                         root, TreeItemDir);

            item->setData(0, Qt::DisplayRole, fileInfo.fileName());
            item->setData(0, Qt::DecorationRole, QIcon(":/icon/dir.png"));
            item->setData(0, Qt::ToolTipRole, fileInfo.absoluteFilePath());
            RecursiveProTree(fileInfo.absoluteFilePath(), file_count, self, root, item, _pre_item);
        } else {
            if (_bstop) return;
            const QString& suffix = fileInfo.completeSuffix();
            if (suffix != "png" && suffix != "jpg" && suffix != "jpeg")
                continue;
            ++ file_count;
//            QThread::msleep(500);
            emit SigUpdateProgress(file_count);
            auto *item = new ProTreeItem(parent, fileInfo.fileName(), fileInfo.absoluteFilePath(),
                                         root, TreeItemPic);

            item->setData(0, Qt::DisplayRole, fileInfo.fileName());
            item->setData(0, Qt::DecorationRole, QIcon(":/icon/pic.png"));
            item->setData(0, Qt::ToolTipRole, fileInfo.absoluteFilePath());

            if (preitem) {
                auto *pre_proitem = dynamic_cast<ProTreeItem*>(preitem);
                pre_proitem->setNextItem(item);
            }
            item->setPreItem(preitem);
            preitem = item;
        }
    }
    emit SigFinishProgress(file_count);
}

void OpenTreeThread::slotCancelProgress()
{
    _bstop = true;
}
