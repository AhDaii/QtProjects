#include "myedit.h"
#include <QDebug>
#include <QLineEdit>

MyEdit::MyEdit(QWidget *parent): QLineEdit(parent)
{
}

void MyEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MyEdit key press event";
    QLineEdit::keyPressEvent(event);
    event->ignore();
}

/*
 * 所有event的都需要先经过event函数处理，再根据不同事件调用对应的函数
 */
bool MyEdit::event(QEvent *pevent)
{
    if (pevent->type() == QEvent::KeyPress) {
        qDebug() << "MyEdit event";
    }
    return QLineEdit::event(pevent);
}




