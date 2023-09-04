#include "slideshowdialog.h"
#include "ui_slideshowdialog.h"

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
    ui->picAnimation->setPixmap(_first_item);
    ui->picAnimation->start();
}

SlideShowDialog::~SlideShowDialog()
{
    delete ui;
}
