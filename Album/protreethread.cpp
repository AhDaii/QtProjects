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
    if (_bstop) return ;
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
                qDebug() << QString("[FAILED COPY] %1 -> %2").arg(fileInfo.absoluteFilePath()).arg(dist_path);
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
