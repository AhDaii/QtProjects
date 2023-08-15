#include "widget.h"
#include "ui_widget.h"
#include <QWheelEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    line_edit = new MyEdit(this);
    line_edit->move(100, 100);
    line_edit->installEventFilter(this);
    ui->textEdit->installEventFilter(this);
    ui->spinBox->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

/*
 * 捕获特定的事件
 */
bool Widget::eventFilter(QObject *object, QEvent *event)
{
    if (object == line_edit) {
        if (event->type() == QEvent::KeyPress) {
            qDebug() << "Widget filter catched line_edit key press event";
            return true;
        }
        return false;
    }

    if (object == ui->textEdit) {
        if (event->type() == QEvent::Wheel) {
            QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(event);
            if (wheelEvent->angleDelta().y()  > 0) {
                qDebug() << "catch wheel event delta > 0";
                ui->textEdit->zoomIn();
            } else {
                qDebug() << "catch wheel event delta < 0";
                ui->textEdit->zoomOut();
            }
            return true;
        }
        return false;
    }

    if (object == ui->spinBox) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Space) {
                ui->spinBox->setValue(0);
                return true;
            }
            return false;
        }
        return false;
    }
    return QWidget::eventFilter(object, event);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Widget key press event";
}
