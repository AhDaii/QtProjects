#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextEdit>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QActionGroup>
#include <QAction>
#include "myaction.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto editMenu = ui->menubar->addMenu("编辑(&E)");
    editMenu->addSeparator();
    auto action_open = editMenu->addAction("打开文件(&O)");
    action_open->setShortcut(QKeySequence("Ctrl+O"));
    connect(action_open, &QAction::triggered, this, &MainWindow::on_action_open_triggered);

    auto group = new QActionGroup(this);
    auto action_l = group->addAction("左对齐(&L)");
    auto action_r = group->addAction("右对齐(&R)");
    auto action_m = group->addAction("居中(&C)");
    action_l->setCheckable(true);
    action_r->setCheckable(true);
    action_m->setCheckable(true);
    editMenu->addAction(action_l);
    editMenu->addAction(action_m);
    editMenu->addAction(action_r);


    MyAction *action = new MyAction(this);
    editMenu->addAction(action);
    connect(action, &MyAction::getText, this, &MainWindow::setText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setText(const QString &string)
{
    ui->textEdit->setText(string);
}


void MainWindow::on_action_N_triggered()
{
    qDebug() << "新建文件" << endl;
    auto textEdit = new QTextEdit(this);
    auto childWindow = ui->mdiArea->addSubWindow(textEdit);
    childWindow->setWindowTitle(tr("文本编辑子窗口"));
    childWindow->show();

}

void MainWindow::on_action_Dock_D_triggered()
{
    qDebug() << "显示Dock" << endl;
    ui->dockWidget->show();
}

void MainWindow::on_action_open_triggered() {
    qDebug() << "打开文件" << endl;
}

