#include "slideshowdialog.h"
#include "ui_slideshowdialog.h"
#include "protreewidget.h"

SlideShowDialog::SlideShowDialog(QWidget *parent, QTreeWidgetItem* first, QTreeWidgetItem* last) :
    QDialog(parent), _first_item(first), _last_item(last),
    ui(new Ui::SlideShowDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    ui->slidePreBtn->setIcons(":/icon/previous.png",
                              ":/icon/previous_hover.png",
                              ":/icon/previous_press.png");
    ui->slideNextBtn->setIcons(":/icon/next.png",
                              ":/icon/next_hover.png",
                              ":/icon/next_press.png");
    ui->closeBtn->setIcons(":/icon/closeshow.png",
                           ":/icon/closeshow_hover.png",
                           ":/icon/closeshow_press.png");
    ui->playBtn->setIcons(":/icon/play.png", ":/icon/play_hover.png", ":/icon/play_press.png",
                          ":/icon/pause.png", ":/icon/pause_hover.png", ":/icon/pause_press.png");

    connect(ui->picAnimation, &PicAnimationWidget::SigUpPreList, ui->preListWidget, &PreListWidget::slotUpPreList);
    connect(ui->picAnimation, &PicAnimationWidget::SigSelectItem, ui->preListWidget, &PreListWidget::slotUpSelect);

    connect(ui->closeBtn, &QPushButton::clicked, this, &SlideShowDialog::close);
    connect(ui->slidePreBtn, &QPushButton::clicked, this, &SlideShowDialog::slotSlidePre);
    connect(ui->slideNextBtn, &QPushButton::clicked, this, &SlideShowDialog::slotSlideNext);
    connect(ui->playBtn, &QPushButton::clicked, ui->picAnimation, &PicAnimationWidget::slotStartOrStop);

    auto* preListWid = dynamic_cast<PreListWidget*>(ui->preListWidget);
    connect(preListWid, &PreListWidget::SigUpSelectShow, ui->picAnimation, &PicAnimationWidget::slotUpSelectShow);
    connect(ui->picAnimation, &PicAnimationWidget::SigStart, ui->playBtn, &PicStateBtn::slotStart);
    connect(ui->picAnimation, &PicAnimationWidget::SigStop, ui->playBtn, &PicStateBtn::slotStop);

    auto* _protree_widget = dynamic_cast<ProTreeWidget*>(parent);
    connect(ui->picAnimation, &PicAnimationWidget::SigStartMusic, _protree_widget, &ProTreeWidget::slotStartMusic);
    connect(ui->picAnimation, &PicAnimationWidget::SigStopMusic, _protree_widget, &ProTreeWidget::slotStopMusic);
    ui->picAnimation->setPixmap(_first_item);
    ui->picAnimation->start();
}

SlideShowDialog::~SlideShowDialog()
{
    delete ui;
}

void SlideShowDialog::slotSlidePre()
{
    ui->picAnimation->slidePre();
}

void SlideShowDialog::slotSlideNext()
{
    ui->picAnimation->slideNext();
}
