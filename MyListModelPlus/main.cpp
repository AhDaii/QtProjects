#include "mainwindow.h"

#include <QApplication>
#include "stringlistmodel.h"
#include <QListView>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList list;
    list << "a" << "b" << "c";
    StringListModel model(list);

    QListView listView;
    listView.setModel(&model);
    //设置选择模式为单选(可扩展)
    listView.setSelectionMode(QAbstractItemView::ExtendedSelection);
    //设置可拖拽
    listView.setDragEnabled(true);
    //设置可拖放
    listView.setAcceptDrops(true);
    //设置显示拖放位置
    listView.setDropIndicatorShown(true);
    listView.show();

//    QTableView tableView;
//    tableView.setModel(&model);
//    tableView.show();
//    model.insertRows(1, 3);
//    model.removeRows(4, 2);
    return a.exec();
}
