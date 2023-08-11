#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setText(const QString& string);

private slots:
    void on_action_N_triggered();

    void on_action_Dock_D_triggered();

    void on_action_open_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
