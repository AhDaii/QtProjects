#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _child_dialog = new ChildDialog(this);

    //qt4 风格的Slot和Signal 只是宏转换，字符串定义不能检测编译错误
    //    connect(ui->ShowChildButton, SIGNAL(clicked(bool)), this, SLOT(showChildDialog()));

    // qt5
    connect(ui->ShowChildButton, &QPushButton::clicked, this, &MainWindow::showChildDialog);
    connect(_child_dialog, &ChildDialog::showMainSig, this, &MainWindow::showMainDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (_child_dialog) {
        delete _child_dialog;
        _child_dialog = nullptr;
    }
}

void MainWindow::showChildDialog()
{
    qDebug() << "Show child dialog" << Qt::endl;
    _child_dialog->show();
    this->hide();
}

void MainWindow::showMainDialog()
{
    this->show();
}

