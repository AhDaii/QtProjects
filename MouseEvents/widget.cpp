#include "widget.h"
#include "ui_widget.h"
#include <QCursor>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QCursor cursor;
    cursor.setShape(Qt::OpenHandCursor);
    setCursor(cursor);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
        offset = event->globalPos() - pos();
    } else if (event->button() == Qt::RightButton) {
        QCursor cursor(QPixmap(":/img/head.png"));
        QApplication::setOverrideCursor(cursor);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event) {
    QApplication::restoreOverrideCursor();
}


void Widget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (windowState() != Qt::WindowFullScreen)
            setWindowState(Qt::WindowFullScreen);
        else
            setWindowState(Qt::WindowNoState);
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        this->move(event->globalPos() - offset);
    }
}

// macos 无法实现，跳过
void Widget::wheelEvent(QWheelEvent *event) {
}
