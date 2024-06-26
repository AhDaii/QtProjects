#include "picanimationwidget.h"
#include "protreeitem.h"
#include <QPainter>

PicAnimationWidget::PicAnimationWidget(QWidget *parent)
    : QWidget{parent}, _b_start(false), _factor(0.0), _cur_item(nullptr)
{
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &PicAnimationWidget::timeOut);

}

PicAnimationWidget::~PicAnimationWidget()
{

}

void PicAnimationWidget::setPixmap(QTreeWidgetItem *item)
{
    if (item == nullptr) {
        return ;
    }
    auto* tree_item = dynamic_cast<ProTreeItem*>(item);
    auto path = tree_item->getPath();
    _pixmap1.load(path);
    _cur_item = tree_item;

    if (_map_items.find(path) == _map_items.end()) {
        _map_items[path] = tree_item;
        // 发送更新浏览列表逻辑
        emit SigUpPreList(item);
    }

    emit SigSelectItem(item);

    auto* next_item = tree_item->getNextItem();
    if (next_item == nullptr) {
        return ;
    }
    auto next_path = next_item->getPath();
    _pixmap2.load(next_path);
    if (_map_items.find(next_path) == _map_items.end()) {
        _map_items[next_path] = next_item;
        // 发送更新浏览列表逻辑
        emit SigUpPreList(next_item);
    }
}

void PicAnimationWidget::start()
{
    emit SigStart();
    emit SigStartMusic();
    _factor = 0;
    _timer->start(25);
    _b_start = true;
}

void PicAnimationWidget::stop()
{
    emit SigStop();
    emit SigStopMusic();
    _timer->stop();
    _factor = 0;
    _b_start = false;
}

void PicAnimationWidget::slidePre()
{
    this->stop();
    if (_cur_item == nullptr) {
        return ;
    }

    auto* cur_pro_item = dynamic_cast<ProTreeItem*>(_cur_item);
    auto* pre_item = cur_pro_item->getPreItem();
    if (pre_item == nullptr)
        return ;
    setPixmap(pre_item);
    update();
}

void PicAnimationWidget::slideNext()
{
    this->stop();
    if (_cur_item == nullptr) {
        return ;
    }

    auto* cur_pro_item = dynamic_cast<ProTreeItem*>(_cur_item);
    auto* next_item = cur_pro_item->getNextItem();
    if (next_item == nullptr)
        return ;
    setPixmap(next_item);
    update();
}

void PicAnimationWidget::slotUpSelectShow(QString path)
{
    auto iter = _map_items.find(path);
    if (iter == _map_items.end()) {
        return ;
    }
    upSelectPixmap(iter.value());
    update();
}

void PicAnimationWidget::slotStartOrStop()
{
    if (!_b_start) {
        this->start();
//        emit SigStartMusic();
    } else {
        this->stop();
        update();
//        emit SigStopMusic();
    }
}

void PicAnimationWidget::paintEvent(QPaintEvent *e)
{
    if (_pixmap1.isNull()) {
        return ;
    }
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
    QRect rect = geometry();
    int w = rect.width();
    int h = rect.height();
    _pixmap1 = _pixmap1.scaled(w, h, Qt::KeepAspectRatio);
    int alpha = 255 * (1.0f - _factor);
    QPixmap alphaPixmap(_pixmap1.size());
    alphaPixmap.fill(Qt::transparent);

    QPainter p1(&alphaPixmap);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, _pixmap1);
    p1.setCompositionMode(QPainter::CompositionMode_Destination);
    p1.fillRect(alphaPixmap.rect(), QColor(0, 0, 0, alpha));
    p1.end();

    int x = (w - _pixmap1.width()) / 2;
    int y = (h - _pixmap1.height()) / 2;
    painter.drawPixmap(x, y, alphaPixmap);

    if (_pixmap2.isNull()) {
        return ;
    }

    _pixmap2 = _pixmap2.scaled(w, h, Qt::KeepAspectRatio);
    alpha = 255 * _factor;
    QPixmap alphaPixmap2(_pixmap2.size());
    alphaPixmap2.fill(Qt::transparent);

    QPainter p2(&alphaPixmap2);
    p2.setCompositionMode(QPainter::CompositionMode_Source);
    p2.drawPixmap(0, 0, _pixmap2);
    p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p2.fillRect(alphaPixmap2.rect(), QColor(0, 0, 0, alpha));
    p2.end();
    x = (w - _pixmap2.width()) / 2;
    y = (h - _pixmap2.height()) / 2;
    painter.drawPixmap(x, y, alphaPixmap2);
}

void PicAnimationWidget::upSelectPixmap(QTreeWidgetItem *item)
{
    if (item == nullptr) {
        return ;
    }
    this->stop();
    auto* tree_item = dynamic_cast<ProTreeItem*>(item);
    auto path = tree_item->getPath();
    _pixmap1.load(path);
    _cur_item = item;

    if (_map_items.find(path) == _map_items.end()) {
        _map_items[path] = tree_item;
    }

    auto* next_item = tree_item->getNextItem();
    if (next_item == nullptr) {
        return ;
    }
    auto next_path = next_item->getPath();
    _pixmap2.load(next_path);
    if (_map_items.find(next_path) == _map_items.end()) {
        _map_items[next_path] = next_item;
    }
}

void PicAnimationWidget::timeOut()
{
    if (_cur_item == nullptr) {
        this->stop();
        update();
        return ;
    }
    _factor += 0.01;
    if (_factor >= 1) {
        _factor = 0;
        auto* cur_pro_item = dynamic_cast<ProTreeItem*>(_cur_item);
        auto* next_pro_item = cur_pro_item->getNextItem();
        if (next_pro_item == nullptr) {
            this->stop();
            update();
            return ;
        }
        this->setPixmap(next_pro_item);
        update();
        return ;
    }
    update();
}
