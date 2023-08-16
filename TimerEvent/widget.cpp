#include "widget.h"
#include "ui_widget.h"
#include <QTime>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    id1 = startTimer(1000);
    id2 = startTimer(1500);
    id3 = startTimer(2000);

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Widget::slot_update_led);
    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
    killTimer(id1);
    killTimer(id2);
    killTimer(id3);
}

void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1) {
        qDebug() << "id1 timer triggered";
    }

    if (event->timerId() == id2) {
        qDebug() << "id2 timer triggered";
    }

    if (event->timerId() == id3) {
        qDebug() << "id3 timer triggered";
    }
}

void Widget::slot_update_led()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    if (time.second() % 2 == 0)
        text[2] = text[5] = ' ';
    ui->lcdNumber->setDigitCount(text.length());
    ui->lcdNumber->display(text);
}

