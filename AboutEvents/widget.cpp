#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    line_edit = new MyEdit(this);
    line_edit->move(100, 100);

}

Widget::~Widget()
{
    delete ui;
}
