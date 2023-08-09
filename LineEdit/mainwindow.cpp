#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ipedit->setEchoMode(QLineEdit::Normal);
    QString ip_mask = "000.000.000.000;_";
    ui->ipedit->setInputMask(ip_mask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

