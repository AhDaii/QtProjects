#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ipedit->setEchoMode(QLineEdit::Normal);
    QString ip_mask = "000.000.000.000;_";
    ui->ipedit->setInputMask(ip_mask);


    ui->macedit->setEchoMode(QLineEdit::Normal);
    QString mac_mask = "HH:HH:HH:HH:HH:HH;_";
    ui->macedit->setInputMask(mac_mask);


    ui->emailedit->setEchoMode(QLineEdit::Normal);
    QRegularExpression reg("[a-zA-Z0-9-_]+@[a-zA-Z0-9]+\.[a-zA-Z0-9]+");
    QValidator *validator = new QRegularExpressionValidator(reg, ui->emailedit);
    ui->emailedit->setValidator(validator);

    ui->pwdedit->setEchoMode(QLineEdit::Password);

}

MainWindow::~MainWindow()
{
    delete ui;
}

