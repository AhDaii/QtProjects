#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "register.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    Register *reg = new Register(this);
    reg->show();
    reg->exec();
}

