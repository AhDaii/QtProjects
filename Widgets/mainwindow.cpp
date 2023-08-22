#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QPixmap>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto listWidget = new QListWidget(this);
    QListWidgetItem * listWidgetItem = new QListWidgetItem;
    listWidgetItem->setText("listItem");
    QPixmap pixmap(50,50);
    pixmap.fill(Qt::blue);
    listWidgetItem->setIcon(pixmap);
    listWidgetItem->setToolTip("this is list item");
    listWidget->insertItem(1,listWidgetItem);

    QListWidgetItem * listWidgetItem2 = new QListWidgetItem;
    listWidgetItem2->setText("listItem2");
    QPixmap pixmap2(50,50);
    pixmap2.fill(Qt::green);
    listWidgetItem2->setIcon(pixmap2);
    listWidgetItem2->setToolTip("this is list item2");
    listWidget->insertItem(2,listWidgetItem2);

    //设置list为单选模式
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //启用拖动
    listWidget->setDragEnabled(true);
    //设置接受拖放
    listWidget->viewport()->setAcceptDrops(true);
    //设置显示将要放置的位置
    listWidget->setDropIndicatorShown(true);
    //设置拖放模式为移动项目，如果不设置，则为复制项目
    listWidget->setDragDropMode(QAbstractItemView::InternalMove);
    listWidget->sortItems(Qt::DescendingOrder);
    listWidget->show();
    this->setCentralWidget(listWidget);


    _tree_widget = new QTreeWidget();
    _tree_widget->setColumnCount(2);
    QStringList headers;
    headers << "name" << "year";
    _tree_widget->setHeaderLabels(headers);

    QTreeWidgetItem *grade1 = new QTreeWidgetItem(_tree_widget);
    grade1->setText(0, "Grade1");
    QTreeWidgetItem *student1 = new QTreeWidgetItem(grade1);
    student1->setText(0, "Zhang");
    student1->setText(1, "99");
    QTreeWidgetItem *student2 = new QTreeWidgetItem(grade1, student1);
    student2->setText(0, "Wang");
    student2->setText(1, "88");
    QTreeWidgetItem *grade2 = new QTreeWidgetItem(_tree_widget, grade1);
    grade2->setText(0, "Grade2");
    QTreeWidgetItem *student3 = new QTreeWidgetItem(grade2);
    student3->setText(0, "Li");
    student3->setText(1, "77");

    auto parent_student3 = student3->parent();
    auto index_student3 = parent_student3->indexOfChild(student3);
    delete parent_student3->takeChild(index_student3);
    auto parent_grade2 = grade2->parent();
    assert(parent_grade2 == nullptr);
    auto index_grade2 = _tree_widget->indexOfTopLevelItem(grade2);
    delete _tree_widget->takeTopLevelItem(index_grade2);
    _tree_widget->show();

    _table_widget = new QTableWidget(3, 2);
    QTableWidgetItem *item1 = new QTableWidgetItem("QT");
    _table_widget->setItem(1, 1, item1);
    QTableWidgetItem *headerH = new QTableWidgetItem("ID");
    _table_widget->setHorizontalHeaderItem(0, headerH);
    QTableWidgetItem *headerV = new QTableWidgetItem("FIRST");
    _table_widget->setVerticalHeaderItem(0, headerV);
    _table_widget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

