#include "picshow.h"
#include "ui_picshow.h"

PicShow::PicShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PicShow)
{
    ui->setupUi(this);
    ui->previousBtn->setIcons(":/icon/previous.png",
                              ":/icon/previous_hover.png",
                              ":/icon/previous_press.png");
    ui->nextBtn->setIcons(":/icon/next.png",
                          ":/icon/next_hover.png",
                          ":/icon/next_press.png");
    QGraphicsOpacityEffect* opacity_pre = new QGraphicsOpacityEffect(this);
    opacity_pre->setOpacity(0);
    ui->previousBtn->setGraphicsEffect(opacity_pre);

    QGraphicsOpacityEffect* opacity_next = new QGraphicsOpacityEffect(this);
    opacity_next->setOpacity(0);
    ui->nextBtn->setGraphicsEffect(opacity_next);

    _animation_show_pre = new QPropertyAnimation(opacity_pre, "opacity", this);
    _animation_show_pre->setEasingCurve(QEasingCurve::OutQuart);
    _animation_show_pre->setDuration(500);
    _animation_show_next = new QPropertyAnimation(opacity_next, "opacity", this);
    _animation_show_next->setEasingCurve(QEasingCurve::OutQuart);
    _animation_show_next->setDuration(500);

    connect(ui->previousBtn, &QPushButton::clicked, this, &PicShow::SigPreClicked);
    connect(ui->nextBtn, &QPushButton::clicked, this, &PicShow::SigNextClicked);
}

PicShow::~PicShow()
{
    delete ui;
}

bool PicShow::event(QEvent *event)
{
    switch(event->type()) {
    case QEvent::Enter:
        showPreNextBtns(true);
        break;
    case QEvent::Leave:
        showPreNextBtns(false);
        break;
    default:
        break;
    }
    return QDialog::event(event);
}

void PicShow::showPreNextBtns(bool b_show)
{
    if (!b_show && _b_btnvisible) {
        _animation_show_pre->stop();
        _animation_show_pre->setStartValue(1);
        _animation_show_pre->setEndValue(0);
        _animation_show_pre->start();

        _animation_show_next->stop();
        _animation_show_next->setStartValue(1);
        _animation_show_next->setEndValue(0);
        _animation_show_next->start();

        _b_btnvisible = false;
        return ;
    }

    if (b_show && !_b_btnvisible) {
        _animation_show_pre->stop();
        _animation_show_pre->setStartValue(0);
        _animation_show_pre->setEndValue(1);
        _animation_show_pre->start();

        _animation_show_next->stop();
        _animation_show_next->setStartValue(0);
        _animation_show_next->setEndValue(1);
        _animation_show_next->start();

        _b_btnvisible = true;
        return ;
    }
}

void PicShow::slotSelectItem(const QString &path)
{
    _selected_path = path;
    _pix_map.load(path);
    auto width =  _pix_map.width();
    auto height = _pix_map.height();
    if (width >= this->width())
        width = this->width() - 10;
    if (height >= this->height())
        height = this->height() - 10;
    _pix_map = _pix_map.scaled(width - 20, height - 20, Qt::KeepAspectRatio);
    ui->label->setPixmap(_pix_map);
}

void PicShow::slotUpdatePic(const QString &path)
{
    _selected_path = path;
    if (_selected_path != "") {
        _pix_map.load(path);
        auto width =  _pix_map.width();
        auto height = _pix_map.height();
        if (width >= this->width())
          width = this->width() - 10;
        if (height >= this->height())
            height = this->height() - 10;
        _pix_map = _pix_map.scaled(width - 20, height - 20, Qt::KeepAspectRatio);
        ui->label->setPixmap(_pix_map);
    }
}

void PicShow::slotDeleteItem()
{
    _selected_path = "";
    ui->label->setText("Project Image is deleted!");
}
