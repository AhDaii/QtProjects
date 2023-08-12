#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextDocument>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QTextCursor>
#include <QAction>
#include <QTextBlock>
#include <QTextCharFormat>
#include <QFont>
#include <QTextImageFormat>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextDocument *doc = ui->textEdit->document();
    QTextFrameFormat fmt;
    fmt.setBorderBrush(Qt::blue);
    fmt.setBorder(3);
    doc->rootFrame()->setFrameFormat(fmt);
    ui->textEdit->insertPlainText("Hello World!\n");
    ui->textEdit->insertPlainText("Hello Qt!");

    QTextFrameFormat fmt2;
    fmt2.setBorderBrush(Qt::red);
    fmt2.setMargin(10);
    fmt2.setPadding(20);
    fmt2.setBorder(2);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertFrame(fmt2);
    ui->textEdit->insertPlainText("Inner!\n");
    ui->textEdit->insertPlainText("Hiiii");

    QAction *action = new QAction("Frame", this);
    ui->menubar->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::showTextFrame);


    QAction *action2 = new QAction("Block", this);
    ui->menubar->addAction(action2);
    connect(action2, &QAction::triggered, this, &MainWindow::showTextBlock);


    QAction *action3 = new QAction("Font", this);
    action3->setCheckable(true);
    ui->menubar->addAction(action3);
    connect(action3, &QAction::triggered, this, &MainWindow::setFont);

    QAction *action4 = new QAction("Image", this);
    ui->menubar->addAction(action4);
    connect(action4, &QAction::triggered, this, &MainWindow::insertImage);


    QAction *action5 = new QAction("Find", this);
    ui->menubar->addAction(action5);
    connect(action5, &QAction::triggered, this, &MainWindow::showDialog);
    dialog = new QDialog(this);
    btn = new QPushButton(dialog);
    lineEdit = new QLineEdit(dialog);
    btn->setText("查找下一个");
    connect(btn, &QPushButton::clicked, this, &MainWindow::searchText);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(lineEdit);
    vLayout->addWidget(btn);
    dialog->setLayout(vLayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTextFrame()
{
    auto doc = ui->textEdit->document();
    auto rootFrame = doc->rootFrame();

    for (auto it = rootFrame->begin(); it != rootFrame->end(); ++ it) {
        auto cur_frame = it.currentFrame();
        auto cur_block = it.currentBlock();
        if (cur_frame) {
            qDebug() << "Current node is Frame" << Qt::endl;
        } else if (cur_block.isValid()){
            qDebug() << "Current node is Text, text is " << cur_block.text() << Qt::endl;
        }
    }
}

void MainWindow::showTextBlock()
{
    auto doc = ui->textEdit->document();
    auto block = doc->firstBlock();
    for (int i = 0; i < doc->blockCount(); ++i) {
        qDebug() << QString("文本块%1，文本块首行行号%2，长度%3，内容%4").arg(i).arg(block.firstLineNumber()).arg(block.length())
        .arg(block.text());
        block = block.next();
    }

}

void MainWindow::setFont(bool checked)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (checked) {
        QTextBlockFormat bfmt;
        bfmt.setAlignment(Qt::AlignCenter);
        cursor.insertBlock(bfmt);
        QTextCharFormat cfmt;
        cfmt.setBackground(Qt::darkGray);
        cfmt.setForeground(Qt::blue);
        cfmt.setFont(QFont("华文仿宋", 15, QFont::Bold, true));
        cfmt.setFontUnderline(true);
        cursor.setCharFormat(cfmt);
        cursor.insertText("华文仿宋");
    } else {
        QTextBlockFormat bfmt2;
        bfmt2.setAlignment(Qt::AlignLeft);
        cursor.insertBlock(bfmt2);
        QTextCharFormat cfmt2;
        cfmt2.setBackground(Qt::white);
        cfmt2.setForeground(Qt::black);
        cfmt2.setFontUnderline(false);
        cursor.setCharFormat(cfmt2);
        cursor.insertText("默认字体");
    }

}

void MainWindow::insertImage()
{
    QTextImageFormat fmt;
    fmt.setName(":/img/head.png");
    ui->textEdit->textCursor().insertImage(fmt);
}

void MainWindow::showDialog()
{
    dialog->show();
}

void MainWindow::searchText()
{
    QString str = lineEdit->text();
    bool isFind = ui->textEdit->find(str);
    if (isFind) {
        qDebug() << QString("行号%1 列号%2").arg(ui->textEdit->textCursor().blockNumber()).arg(ui->textEdit->textCursor().columnNumber());
    }
}

