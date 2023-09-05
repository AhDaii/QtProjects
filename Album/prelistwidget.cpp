#include "prelistwidget.h"
#include "protreeitem.h"
#include "prelistitem.h"
#include "const.h"
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QPixmap>
#include <QPainter>

PreListWidget::PreListWidget(QWidget* parent): QListWidget(parent), _cnt(0), _pre_index(-1)
{
    this->setViewMode(QListWidget::IconMode);
    this->setIconSize(QSize(PREICON_SIZE, PREICON_SIZE));
    this->setSpacing(5);

    _last_index = QGuiApplication::primaryScreen()->geometry().width() * 1.0 / 100 - 2;
    connect(this, &PreListWidget::itemPressed, this, &PreListWidget::slotItemPressed);
}

PreListWidget::~PreListWidget()
{

}

void PreListWidget::slotUpPreList(QTreeWidgetItem *tree_item)
{
    if (tree_item == nullptr) {
        qDebug() << "tree_item is empty";
        return ;
    }
    auto* pro_item = dynamic_cast<ProTreeItem*>(tree_item);
    auto path = pro_item->getPath();
    auto iter = _map_items.find(path);

    if (iter != _map_items.end()) {
        qDebug() << QString("path %1 is exists").arg(path);
        return ;
    }

    addListPath(path);
}

void PreListWidget::slotUpSelect(QTreeWidgetItem *tree_item)
{
    if (tree_item == nullptr) {
        return ;
    }
    auto* pro_item = dynamic_cast<ProTreeItem*>(tree_item);
    auto path = pro_item->getPath();
    auto iter = _map_items.find(path);

    if (iter == _map_items.end()) {
        qDebug() << QString("path %1 is not exists").arg(path);
        return ;
    }

    auto* list_item = dynamic_cast<PreListItem*>(iter.value());
    auto index = list_item->getIndex();
    int max_num = QGuiApplication::primaryScreen()->geometry().width() * 1.0 / 100 - 2;
    if (index > max_num) {
        auto pos_cur = this->pos();
        if (_pre_index > index)
            this->move(pos_cur.x() + 105, pos_cur.y());
        else if (_pre_index < index)
            this->move(pos_cur.x() - 105, pos_cur.y());
    } else {
        this->move(_pos_origin);
        _last_index = max_num;
    }
    _pre_index = index;
    this->setCurrentItem(iter.value());
}

void PreListWidget::slotItemPressed(QListWidgetItem *item)
{
    if (QGuiApplication::mouseButtons() != Qt::LeftButton) {
        return ;
    }
    auto* list_item = dynamic_cast<PreListItem*>(item);
    auto path = list_item->getPath();
    auto index = list_item->getIndex();
    if (index > _last_index && _pre_index > index) {
        this->move(this->pos().x() + (_pre_index - index) * 105, this->pos().y());
    } else if(index < _last_index) {
        this->move(_pos_origin);
    }
    _pre_index = index;
    this->setCurrentItem(item);
    emit SigUpSelectShow(path);
}

void PreListWidget::addListPath(const QString &path)
{
    QPixmap src_pixmap(path);
    src_pixmap = src_pixmap.scaled(PREICON_SIZE, PREICON_SIZE, Qt::KeepAspectRatio);
    QPixmap dst_pixmap(QSize(PREICON_SIZE, PREICON_SIZE));
    dst_pixmap.fill(QColor(255, 255, 255, 50));

    QPainter painter(&dst_pixmap);
    auto src_w = src_pixmap.width();
    auto src_h = src_pixmap.height();
    auto dst_w = dst_pixmap.width();
    auto dst_h = dst_pixmap.height();
    auto x = (dst_w - src_w) / 2;
    auto y = (dst_h - src_h) / 2;
    painter.drawPixmap(x, y, src_pixmap);
    ++ _cnt;

    PreListItem* pItem = new PreListItem(QIcon(dst_pixmap), path, _cnt, this);
    pItem->setSizeHint(QSize(PREITEM_SIZE, PREITEM_SIZE));
    this->addItem(pItem);
    _map_items[path] = pItem;
    if (_cnt == 1) {
        _pos_origin = this->pos();
    }
}
