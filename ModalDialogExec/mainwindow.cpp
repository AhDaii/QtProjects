#include "mainwindow.h"
#include "mydialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    close();
    MyDialog my_dialog;

    if (my_dialog.exec() == QDialog::Accepted) {
        this->show();
    }
    else {
        return ;
    }
}

