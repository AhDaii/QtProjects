#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QVariant>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void getCurrentItemData();
    void toggleSelection();
    void updateSection(const QItemSelection &selected, const QItemSelection &dselected);
    void changeCurrent(const QModelIndex &current, const QModelIndex &previous);

private:
    Ui::MainWindow *ui;
    QTableView *_table_view, *_table_view2;
};
#endif // MAINWINDOW_H
