#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItem>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QItemSelection>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(7, 4, this);
    for (int i = 0; i < 7; ++ i)
        for (int j = 0; j < 4; ++ j) {
            QStandardItem *item = new QStandardItem(QString("(%1, %2)").arg(i).arg(j));
            model->setItem(i, j, item);
        }

    _table_view = new QTableView;
    _table_view->setModel(model);
    setCentralWidget(_table_view);
    this->resize(800, 600);

    QItemSelectionModel *selection_model = _table_view->selectionModel();
    QModelIndex top_left, bottom_right;
    top_left = model->index(1, 1);
    bottom_right = model->index(5, 2);
    QItemSelection selection(top_left, bottom_right);
    selection_model->select(selection, QItemSelectionModel::Select);

    QMenu *menu = new QMenu("Function");
    menu->addAction("print", this, &MainWindow::getCurrentItemData);
    menu->addAction("toggle", this, &MainWindow::toggleSelection);
    ui->menubar->addMenu(menu);

    _table_view2 = new QTableView;
    _table_view2->setWindowTitle("Table View 2");
    _table_view2->resize(400, 300);
    _table_view2->setModel(model);
    _table_view2->setSelectionModel(selection_model);
    _table_view2->show();

    connect(selection_model, &QItemSelectionModel::selectionChanged, this, &MainWindow::updateSection);
    connect(selection_model, &QItemSelectionModel::currentChanged, this, &MainWindow::changeCurrent);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getCurrentItemData()
{
    auto currentDatas = _table_view->selectionModel()->selectedIndexes();
    qDebug() << QString("当前已选%1个项目, 内容为: ").arg(currentDatas.size());
    for (auto &it : currentDatas)
        qDebug() << it.data().toString();
}

void MainWindow::toggleSelection()
{
    QModelIndex topLeft = _table_view->model()->index(0, 0);
    auto max_row = _table_view->model()->rowCount();
    auto max_col = _table_view->model()->columnCount();
    QModelIndex bottomRight = _table_view->model()->index(max_row - 1, max_col - 1);
    QItemSelection selection(topLeft, bottomRight);
    _table_view->selectionModel()->select(selection, QItemSelectionModel::Toggle);
}

void MainWindow::updateSection(const QItemSelection &selected, const QItemSelection &dselected)
{
    QModelIndex index;
    QModelIndexList list = selected.indexes();

    for (int i = 0; i < list.size(); ++ i) {
        QString text = QString("(%1, %2)").arg(list[i].row()).arg(list[i].column());
        _table_view->model()->setData(list[i], text);
    }

    list = dselected.indexes();
    for (int i = 0; i < list.size(); ++ i)
        _table_view->model()->setData(list[i], "");
}

void MainWindow::changeCurrent(const QModelIndex &current, const QModelIndex &previous)
{
    qDebug() << QString("(%1, %2) -> (%3, %4)").arg(previous.row()).arg(previous.column())
                    .arg(current.row()).arg(current.column());
}

