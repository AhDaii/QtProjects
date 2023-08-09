#include "childdialog.h"
#include "ui_childdialog.h"

ChildDialog::ChildDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChildDialog), _parent(parent)
{
    ui->setupUi(this);
//    connect(ui->ShowMainButton, &QPushButton::clicked, this, &ChildDialog::showMainWindow);
    connect(ui->ShowMainButton, &QPushButton::clicked, this, &ChildDialog::showMainSig);
}

ChildDialog::~ChildDialog()
{
    delete ui;
}

void ChildDialog::showMainWindow()
{
    qDebug() << "Show main window" << Qt::endl;
    this->hide();

    emit showMainSig();
}
