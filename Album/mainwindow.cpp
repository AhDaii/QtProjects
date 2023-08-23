#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建菜单
    QMenu *menu_file = menuBar()->addMenu(tr("文件(&F)"));
    // 创建项目动作
    QAction *action_create_pro = new QAction(QIcon(":/icon/createpro.png"), tr("创建项目"), this);
    action_create_pro->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    menu_file->addAction(action_create_pro);
    // 打开项目动作
    QAction *action_open_pro = new QAction(QIcon(":/icon/openpro.png"), tr("打开项目"), this);
    action_open_pro->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    menu_file->addAction(action_open_pro);

    // 创建设置菜单
    QMenu *menu_set = menuBar()->addMenu(tr("设置(&S)"));
    // 设置背景音乐
    QAction *act_music = new QAction(QIcon(":/icon/music.png"), tr("背景音乐"), this);
    act_music->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_M));
    menu_set->addAction(act_music);

    // 连接信号与槽
    connect(action_create_pro, &QAction::triggered, this, &MainWindow::SlotCreatePro);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotCreatePro(bool)
{
    qDebug() << "slot create pro triggered!";
}
