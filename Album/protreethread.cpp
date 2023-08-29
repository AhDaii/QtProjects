#include "const.h"
#include "protreeitem.h"
#include "protreethread.h"

#include <QDir>
#include <QDebug>


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
    createProTree(_src_path, _dist_path, _parent_item, _file_count, _self, _root);
    if (_bstop) {
        auto path = dynamic_cast<ProTreeItem*>(_root)->getPath();
        auto index = _self->indexOfTopLevelItem(_root);
        delete _self->takeTopLevelItem(index);
        QDir dir(path);
        dir.removeRecursively();
        return ;
    }
    emit SigFinishProgress(_file_count);
}

void ProTreeThread::createProTree(const QString &src_path, const QString &dist_path, QTreeWidgetItem *parent_item, int& file_count, QTreeWidget *self, QTreeWidgetItem *root, QTreeWidgetItem* preItem)
{
    if (_bstop) return;
    bool need_copy = true;
    if (src_path == dist_path)
        need_copy = false;
    QDir import_dir(src_path);
    QStringList nameFilters;
    import_dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    import_dir.setSorting(QDir::Name);
    QFileInfoList list = import_dir.entryInfoList();
    for (int i  = 0; i < list.size(); ++ i) {
        if (_bstop) return ;
        QFileInfo fileInfo = list.at(i);
        bool bIsDir = fileInfo.isDir();
        if (bIsDir) {
            if (_bstop) return ;
            ++ file_count;
            emit SigUpdateProgress(file_count);

            QDir dist_dir(dist_path);
            QString sub_dist_path = dist_dir.absoluteFilePath(fileInfo.fileName());
            QDir sub_dist_dir(sub_dist_path);
            if (!sub_dist_dir.exists()) {
                bool ret = sub_dist_dir.mkdir(sub_dist_path);
                if (!ret) {
                    qDebug() << QString("[MKDIR FAILED] %1").arg(sub_dist_path);
                    continue;
                }
                auto *item = new ProTreeItem(parent_item, fileInfo.fileName(), sub_dist_path, root, TreeItemDir);
                item->setData(0, Qt::DisplayRole, fileInfo.fileName());
                item->setData(0, Qt::DecorationRole, QIcon(":/icon/dir.png"));
                item->setData(0, Qt::ToolTipRole, sub_dist_path);

                createProTree(fileInfo.absoluteFilePath(), sub_dist_path, item, file_count, self, root, preItem);
            }
        } else {
            if (_bstop) return ;
            const QString& suffix = fileInfo.completeSuffix();
            if (suffix != "png" && suffix != "jpg" && suffix != "jpeg") {
                continue;
            }

            ++ file_count;
            emit SigUpdateProgress(file_count);
            if (!need_copy) continue;

            QDir dist_dir(dist_path);
            QString dist_file_path = dist_dir.absoluteFilePath(fileInfo.fileName());
            if (!QFile::copy(fileInfo.absoluteFilePath(), dist_file_path)) {
                qDebug() << QString("[COPY FAILED] %1 -> %2").arg(fileInfo.absoluteFilePath()).arg(dist_path);
                continue;
            }

            auto *item = new ProTreeItem(parent_item, fileInfo.fileName(), dist_file_path, root, TreeItemPic);
            item->setData(0, Qt::DisplayRole, fileInfo.fileName());
            item->setData(0, Qt::DecorationRole, QIcon(":/icon/pic.png"));
            item->setData(0, Qt::ToolTipRole, dist_file_path);
            if (preItem) {
                auto *pre_proitem = dynamic_cast<ProTreeItem*>(preItem);
                pre_proitem->setNextItem(item);
            }
            item->setPreItem(preItem);
            preItem = item;
        }
    }

}

void ProTreeThread::slotCancelProgress()
{
    _bstop = true;
}
