#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QTreeWidget>
#include <QSet>
#include <QAction>
#include <QProgressDialog>

class ProTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    ProTreeWidget(QWidget *parent = nullptr);
    void addProToTree(const QString &name, const QString &path);
private:
    QSet<QString> _set_path;
    // 右键单击的item
    QTreeWidgetItem *_right_btn_item;
    QAction *_action_import;
    QAction *_action_setstart;
    QAction *_action_closepro;
    QAction *_action_slideshow;
    QProgressDialog *_dialog_process;

private slots:
    void slotItemPressed(QTreeWidgetItem *item, int column);
    void slotImport();
};

#endif // PROTREEWIDGET_H
