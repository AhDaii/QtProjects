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
}




