#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::ClickFocus);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event) {
    // ctrl + m
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->key() == Qt::Key_M && windowState() != Qt::WindowFullScreen) {
            setWindowState(Qt::WindowFullScreen);
            return ;
        }
        return ;
    }


    // ESC
    if (event->key() == Qt::Key_Escape && windowState() == Qt::WindowFullScreen) {
        setWindowState(Qt::WindowNoState);
        return ;
    }

    // button move
    bool up = false, down = false, left = false, right = false;

    if (event->key() == Qt::Key_Up) {
        if (event->isAutoRepeat()) {
            auto curPos = ui->pushButton->pos();
            curPos.setY(curPos.y() - 5);
            ui->pushButton->move(curPos);
            return ;
        }
        up = true;
    }

    if (event->key() == Qt::Key_Down) {
        if (event->isAutoRepeat()) {
            auto curPos = ui->pushButton->pos();
            curPos.setY(curPos.y() + 5);
            ui->pushButton->move(curPos);
            return ;
        }
        down = true;
    }

    if (event->key() == Qt::Key_Left) {
        if (event->isAutoRepeat()) {
            auto curPos = ui->pushButton->pos();
            curPos.setX(curPos.x() - 5);
            ui->pushButton->move(curPos);
            return ;
        }
        left = true;
    }

    if (event->key() == Qt::Key_Right) {
        if (event->isAutoRepeat()) {
            auto curPos = ui->pushButton->pos();
            curPos.setX(curPos.x() + 5);
            ui->pushButton->move(curPos);
            return ;
        }
        right = true;
    }


    auto curPos = ui->pushButton->pos();
    if (up) 		curPos.setY(curPos.y() - 5);
    if (down) 		curPos.setY(curPos.y() + 5);
    if (left)		curPos.setX(curPos.x() - 5);
    if (right)		curPos.setX(curPos.x() + 5);
    ui->pushButton->move(curPos);
}
