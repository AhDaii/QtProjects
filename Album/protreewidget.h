#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include "protreethread.h"
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
    QTreeWidgetItem *_active_item;
    QAction *_action_import;
    QAction *_action_setstart;
    QAction *_action_closepro;
    QAction *_action_slideshow;
    QProgressDialog *_dialog_progress;
    std::shared_ptr<ProTreeThread> _thread_import_pro;

private slots:
    void slotItemPressed(QTreeWidgetItem *item, int column);
    void slotImport();
    void slotUpdateProgress(int count);
    void slotFinishProgress();
    void slotCancelProgress();
    void slotSetActive();

signals:
    void SigCancelProgress();
};

#endif // PROTREEWIDGET_H
