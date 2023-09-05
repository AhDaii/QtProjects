#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QShortcut>
#include <QFileDialog>
#include "wizard.h"
#include "protree.h"
#include "picshow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->hide();
//    this->showFullScreen();
//    this->setMinimumSize(800, 600);

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
    connect(action_open_pro, &QAction::triggered, this, &MainWindow::SlotOpenPro);

    // 左侧区域
    _protree = new ProTree();
    ui->proLayout->addWidget(_protree);
    QTreeWidget* tree_widget = dynamic_cast<ProTree*>(_protree)->getTreeWidget();
    auto* pro_tree_widget = dynamic_cast<ProTreeWidget*>(tree_widget);
    connect(this, &MainWindow::SigOpenPro, pro_tree_widget, &ProTreeWidget::slotOpenPro);

    // 右侧区域
    _picshow = new PicShow();
    ui->picLayout->addWidget(_picshow);
    auto* pro_pic_show = dynamic_cast<PicShow*>(_picshow);
    connect(pro_tree_widget, &ProTreeWidget::SigUpdateSelected, pro_pic_show, &PicShow::slotSelectItem);

    // 图片切换
    connect(pro_pic_show, &PicShow::SigPreClicked, pro_tree_widget, &ProTreeWidget::slotPreShow);
    connect(pro_pic_show, &PicShow::SigNextClicked, pro_tree_widget, &ProTreeWidget::slotNextShow);
    connect(pro_tree_widget, &ProTreeWidget::SigUpdatePic, pro_pic_show, &PicShow::slotUpdatePic);

    // 项目关闭时清空图片区域
    connect(pro_tree_widget, &ProTreeWidget::SigClearSelected, pro_pic_show, &PicShow::slotDeleteItem);


    // 音乐播放
    connect(act_music, &QAction::triggered, pro_tree_widget, &ProTreeWidget::slotSetMusic);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotCreatePro(bool)
{
    // qDebug() << "slot create pro triggered!";
    Wizard wizard(this);
    wizard.setWindowTitle(tr("创建项目"));
    auto *page = wizard.page(0);
    page->setTitle(tr("设置项目配置"));
    // 连接信号与槽, 把项目配置传回
    connect(&wizard, &Wizard::sigProSettings, dynamic_cast<ProTree*>(_protree), &ProTree::AddProToTree);

    wizard.show();
    wizard.exec();
    // 断开所有信号
    disconnect(&wizard);
}

void MainWindow::SlotOpenPro(bool)
{
    QFileDialog file_dialog;
    QStringList file_names;
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle("选择导入的文件夹");
    file_dialog.setDirectory(QDir::currentPath());
    file_dialog.setViewMode(QFileDialog::Detail);
    if (!file_dialog.exec()) {
        return ;
    }
    file_names = file_dialog.selectedFiles();
    if (file_names.length() <= 0)
        return ;

    QString import_path = file_names.at(0);
    emit SigOpenPro(import_path);
}

