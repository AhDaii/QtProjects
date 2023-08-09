#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qcolordialog.h>
#include <qdir.h>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QWizard>
#include <QLabel>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_updateProgressDialog()
{
    ++ _count;
    if (_count > 5000) {
        _timer->stop();
        delete _timer;
        _timer = nullptr;
        delete _progressDialog;
        _progressDialog = nullptr;
        _count = 0;
        qDebug() << "计时完成" << Qt::endl;
        return;
    }
    _progressDialog->setValue(_count);
}

void MainWindow::on_cancelProgressDialog()
{
    _timer->stop();
    delete _timer;
    _timer = nullptr;
    _progressDialog = nullptr;
    _count = 0;
    qDebug() << "计时取消" << Qt::endl;
    return;
}


void MainWindow::on_pushButton_clicked()
{
//    QColorDialog colorDlg(Qt::blue, this);
//    colorDlg.setOption(QColorDialog::ShowAlphaChannel);
//    colorDlg.exec();
//    QColor color = colorDlg.currentColor();
//    qDebug() << "Current color is " << color << Qt::endl;
    QColor color = QColorDialog::getColor(Qt::blue, this, tr("选择颜色"), QColorDialog::ShowAlphaChannel);
    qDebug() << "Current color is " << color << Qt::endl;
}


void MainWindow::on_pushButton_2_clicked()
{
    QString path = QDir::currentPath();
    QString title = tr("文件对话框");
    QString filter = tr("文本文件(*.txt);;图片文件(*.png *.jpg *.gif);;所有文件(*.*)");
    QString filename = QFileDialog::getOpenFileName(this, title, path, filter);

    qDebug() << "File name is " << filename << Qt::endl;
}


void MainWindow::on_pushButton_3_clicked()
{
    QStringList items;
    items << tr("条目1") << tr("条目2");
    bool ret = false;
    auto itemData = QInputDialog::getItem(this, tr("条目输入对话框"), tr("输入或选择条目"), items, 0, true, &ret);
    if (ret) {
        qDebug() << "Item is " << itemData << Qt::endl;
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    bool ret = false;
    auto text = QInputDialog::getText(this, tr("文字对话框"), tr("请输入内容"), QLineEdit::Normal, tr("text"), &ret);
    if (ret) {
        qDebug() << "Text is " << text << Qt::endl;
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    bool ret = false;
    auto intData = QInputDialog::getInt(this, tr("整型输入对话框"), tr("请输入整数"), 0, -200, 200, 10, &ret);
    if (ret) {
        qDebug() << "Int is " << intData << Qt::endl;
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    bool ret = false;
    auto floatData = QInputDialog::getDouble(this, tr("浮点型输入对话框"), tr("输入浮点数"), 0, -1, 1, 2, &ret);
    if (ret) {
        qDebug() << "Float is " << floatData << Qt::endl;
    }
}



void MainWindow::on_pushButton_7_clicked()
{
    auto ret = QMessageBox::question(this, tr("问题对话框"), tr("对或错"), QMessageBox::Yes, QMessageBox::No);
    if (ret == QMessageBox::Yes || ret == QMessageBox::No) {
        qDebug() << "ret is " << (ret == QMessageBox::Yes ? "Yes" : "No") << Qt::endl;
    }

    auto ret2 = QMessageBox::information(this, tr("通知对话框"), tr("你好"), QMessageBox::Ok);
    if (ret2 == QMessageBox::Ok) {
        qDebug() << "ret2 is OK" << Qt::endl;
    }

    auto ret3 = QMessageBox::warning(this, tr("警告对话框"), tr("警告警告警告"), QMessageBox::Ok);
    if (ret3 == QMessageBox::Ok) {
        qDebug() << "ret3 is OK" << Qt::endl;
    }

    auto ret4 = QMessageBox::critical(this, tr("关键提示对话框"), tr("关键提示"), QMessageBox::Ok);
    if (ret4 == QMessageBox::Ok) {
        qDebug() << "ret4 is OK" << Qt::endl;
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    _count = 0;
    _progressDialog = new QProgressDialog(tr("正在计时"), tr("取消"),0, 5000, this);
    _progressDialog->setWindowTitle(tr("进度对话框"));
    _progressDialog->setWindowModality(Qt::ApplicationModal);
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::on_updateProgressDialog);
    connect(_progressDialog, &QProgressDialog::canceled, this, &MainWindow::on_cancelProgressDialog);
    _timer->start(2);
    qDebug() << "计时结束" << Qt::endl;
}


void MainWindow::on_pushButton_9_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("导航对话框练习"));

    QWizardPage *page1 = new QWizardPage();
    page1->setWindowTitle(tr("引导界面1"));
    QLabel *label1 = new QLabel();
    label1->setText("Label1");
    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addWidget(label1);
    page1->setLayout(layout1);
    wizard.addPage(page1);


    QWizardPage *page2 = new QWizardPage();
    page2->setWindowTitle(tr("引导界面2"));
    QButtonGroup *btnGroup = new QButtonGroup(page2);
    QRadioButton *btn1 = new QRadioButton();
    btn1->setText("btn1");
    QRadioButton *btn2 = new QRadioButton();
    btn2->setText("btn2");
    QRadioButton *btn3 = new QRadioButton();
    btn3->setText("btn3");
    btnGroup->addButton(btn1);
    btnGroup->addButton(btn2);
    btnGroup->addButton(btn3);
    QVBoxLayout *layout2 = new QVBoxLayout();
    for (size_t i = 0; i < btnGroup->buttons().size(); ++ i) {
        layout2->addWidget(btnGroup->buttons()[i]);
    }
    page2->setLayout(layout2);
    wizard.addPage(page2);

    wizard.show();
    wizard.exec();
}

