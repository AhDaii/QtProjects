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

//    QListView listView;
//    listView.setModel(&model);
//    listView.show();

    QTableView tableView;
    tableView.setModel(&model);
    tableView.show();
    model.insertRows(1, 3);
    model.removeRows(4, 2);
    return a.exec();
}
