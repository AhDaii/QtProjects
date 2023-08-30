#include "protreewidget.h"
#include <QDir>
#include <QHeaderView>
#include "protreeitem.h"
#include "const.h"
#include "removeprodialog.h"
#include "OpenTreeThread.h"
#include <QFileDialog>
#include <QGuiApplication>
#include <QMenu>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QDebug>

ProTreeWidget::ProTreeWidget(QWidget *parent):
    QTreeWidget(parent), _right_btn_item(nullptr), _active_item(nullptr), _dialog_progress(nullptr), _selected_item(nullptr),
    _thread_import_pro(nullptr), _thread_open_pro(nullptr), _dialog_open_progress(nullptr)
{
    qRegisterMetaType<QVector<int> >("QVector<int>");
    this->header()->hide();
    connect(this, &ProTreeWidget::itemPressed, this, &ProTreeWidget::slotItemPressed);
    _action_import = new QAction(QIcon(":/icon/import.png"), tr("导入文件"), this);
    _action_setstart = new QAction(QIcon(":/icon/core.png"), tr("设置活动项目"), this);
    _action_closepro = new QAction(QIcon(":/icon/close.png"), tr("关闭项目"), this);
    _action_slideshow = new QAction(QIcon(":/icon/slideshow.png"), tr("轮播图播放"), this);
    connect(_action_import, &QAction::triggered, this, &ProTreeWidget::slotImport);
    connect(_action_setstart, &QAction::triggered, this, &ProTreeWidget::slotSetActive);
    connect(_action_closepro, &QAction::triggered, this, &ProTreeWidget::slotClosePro);
}

void ProTreeWidget::addProToTree(const QString &name, const QString &path)
{
    QDir dir(path);
    QString file_path = dir.absoluteFilePath(name);
    if (_set_path.find(file_path) != _set_path.end()) {
        return ;
    }
    QDir pro_dir(file_path);
    if (!pro_dir.exists()) {
        bool enable = pro_dir.mkpath(file_path);
        if (!enable) {
            return ;
        }
    }
    _set_path.insert(file_path);
    auto *item = new ProTreeItem(this, name, file_path, TreeItemPro);
    item->setData(0, Qt::DisplayRole, name);
    item->setData(0, Qt::DecorationRole, QIcon(":/icon/dir.png"));
    item->setData(0, Qt::ToolTipRole, file_path);
//    this->addTopLevelItem(item);
}

void ProTreeWidget::slotItemPressed(QTreeWidgetItem *pressedItem, int column)
{
    if (QGuiApplication::mouseButtons() == Qt::RightButton) {
        QMenu menu(this);
        int itemtype = pressedItem->type();
        if (itemtype == TreeItemPro) {
            _right_btn_item = pressedItem;
            menu.addAction(_action_import);
            menu.addAction(_action_setstart);
            menu.addAction(_action_closepro);
            menu.addAction(_action_slideshow);
            menu.exec(QCursor::pos());
        }
    }
}

void ProTreeWidget::slotImport()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle(tr("选择导入的文件夹"));
    QString path = "";
    if (!_right_btn_item) {
        qDebug() << "_right_btn_item is empty";
        return ;
    }

    path = dynamic_cast<ProTreeItem*>(_right_btn_item)->getPath();
    file_dialog.setDirectory(path);
    file_dialog.setViewMode(QFileDialog::Detail);

    QStringList fileName;
    if (file_dialog.exec()) {
        fileName = file_dialog.selectedFiles();
    }

    if (fileName.length() <= 0) {
        return ;
    }

    QString import_path = fileName.at(0);
    int file_count = 0;

    _dialog_progress = new QProgressDialog(this);

    _thread_import_pro = std::make_shared<ProTreeThread>(import_path, path, _right_btn_item, file_count, this,
                                                         _right_btn_item, nullptr);
    connect(_thread_import_pro.get(), &ProTreeThread::SigUpdateProgress, this, &ProTreeWidget::slotUpdateProgress);
    connect(_thread_import_pro.get(), &ProTreeThread::SigFinishProgress, this, &ProTreeWidget::slotFinishProgress);
    connect(_dialog_progress, &QProgressDialog::canceled, this, &ProTreeWidget::slotCancelProgress);
    connect(this, &ProTreeWidget::SigCancelProgress, _thread_import_pro.get(), &ProTreeThread::slotCancelProgress);
    _thread_import_pro->start();
    _dialog_progress->setWindowTitle(tr("导入中"));
    _dialog_progress->setFixedWidth(PROCESS_WIDTH);
    _dialog_progress->setRange(0, PROCESS_WIDTH);
    _dialog_progress->exec();
}

void ProTreeWidget::slotUpdateProgress(int count)
{
    if (!_dialog_progress)
        return ;
    if (count >= PROCESS_MAX) {
        _dialog_progress->setValue(count % PROCESS_MAX);
    } else {
        _dialog_progress->setValue(count);
    }
}

void ProTreeWidget::slotFinishProgress()
{
    _dialog_progress->setValue(PROCESS_MAX);
    _dialog_progress->deleteLater();
}

void ProTreeWidget::slotCancelProgress()
{
    emit SigCancelProgress();
    delete _dialog_progress;
    _dialog_progress = nullptr;
}

void ProTreeWidget::slotSetActive() {
    if (!_right_btn_item) {
        return ;
    }

    QFont nullFont;
    nullFont.setBold(false);
    if (_active_item) {
        _active_item->setFont(0, nullFont);
        _active_item->setData(0, Qt::DecorationRole, QIcon(":/icon/dir.png"));
    }
    _active_item = _right_btn_item;
    nullFont.setBold(true);
    _active_item->setFont(0, nullFont);
    _active_item->setData(0, Qt::DecorationRole, QIcon(":/icon/dir_star.png"));
}

void ProTreeWidget::slotClosePro()
{
    RemoveProDialog remove_pro_dialog;
    auto ret = remove_pro_dialog.exec();
    if (ret == QDialog::Rejected) {
        return ;
    }

    bool b_remove = remove_pro_dialog.isRemoved();
    auto index_right_btn = this->indexOfTopLevelItem(_right_btn_item);
    auto *protreeitem = dynamic_cast<ProTreeItem*>(_right_btn_item);
//    auto *selecteditem = dynamic_cast<ProTreeItem*>(_selected_item);
    auto delete_path = protreeitem->getPath();
    _set_path.remove(delete_path);
    if (b_remove) {
        QDir delete_dir(delete_path);
        delete_dir.removeRecursively();
    }

    if (protreeitem == _active_item) {
        _active_item = nullptr;
    }

    delete this->takeTopLevelItem(index_right_btn);
    _right_btn_item = nullptr;
}

void ProTreeWidget::slotUpdateOpenProgress(int count)
{
    if (!_dialog_open_progress)
        return ;
    if (count >= PROCESS_MAX) {
        _dialog_open_progress->setValue(count % PROCESS_MAX);
    } else {
        _dialog_open_progress->setValue(count);
    }
}

void ProTreeWidget::slotFinishOpenProgress()
{
    if (!_dialog_open_progress)
        return ;
    _dialog_open_progress->setValue(PROCESS_MAX);
    delete _dialog_open_progress;
    _dialog_open_progress = nullptr;
}

void ProTreeWidget::slotCancelOpenProgress()
{
    emit SigCancelOpenProgress();
    delete _dialog_open_progress;
    _dialog_open_progress = nullptr;
}

void ProTreeWidget::slotOpenPro(const QString &path)
{
    if (_set_path.find(path) != _set_path.end()) {
        return ;
    }
    _set_path.insert(path);
    int file_count = 0;
    QDir pro_dir(path);
    QString pro_name = pro_dir.dirName();

    _dialog_open_progress = new QProgressDialog(this);
    _thread_open_pro = std::make_shared<OpenTreeThread>(path, file_count, this, nullptr);
    connect(_thread_open_pro.get(), &OpenTreeThread::SigUpdateProgress, this, &ProTreeWidget::slotUpdateOpenProgress);
    connect(_thread_open_pro.get(), &OpenTreeThread::SigFinishProgress, this, &ProTreeWidget::slotFinishOpenProgress);
    connect(_dialog_open_progress, &QProgressDialog::canceled, this, &ProTreeWidget::slotCancelOpenProgress);
    connect(this, &ProTreeWidget::SigCancelOpenProgress, _thread_open_pro.get(), &OpenTreeThread::slotCancelProgress);
    _thread_open_pro->start();
    _dialog_open_progress->setWindowTitle(tr("打开项目中"));
    _dialog_open_progress->setFixedWidth(PROCESS_WIDTH);
    _dialog_open_progress->setRange(0, PROCESS_WIDTH);
    _dialog_open_progress->exec();
}
