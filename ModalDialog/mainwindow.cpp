#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto w = new QDialog(this);
    w->setWindowFlag(Qt::WindowStaysOnTopHint);
    w->setModal(true);
    w->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

