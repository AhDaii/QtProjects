#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void showTextFrame();
    void showTextBlock();
    void setFont(bool checked);
    void insertImage();
    void showDialog();
    void searchText();

private:
    Ui::MainWindow *ui;
    QDialog *dialog;
    QPushButton *btn;
    QLineEdit *lineEdit;

};
#endif // MAINWINDOW_H
