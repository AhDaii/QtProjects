#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include "protreethread.h"
#include <QTreeWidget>
#include <QSet>
#include <QAction>
#include <QProgressDialog>
#include "OpenTreeThread.h"

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
    QTreeWidgetItem *_selected_item;
    QAction *_action_import;
    QAction *_action_setstart;
    QAction *_action_closepro;
    QAction *_action_slideshow;
    QProgressDialog *_dialog_progress;
    QProgressDialog *_dialog_open_progress;
    std::shared_ptr<ProTreeThread> _thread_import_pro;
    std::shared_ptr<OpenTreeThread> _thread_open_pro;
    
private slots:
    void slotItemPressed(QTreeWidgetItem *item, int column);
    void slotImport();
    void slotUpdateProgress(int count);
    void slotFinishProgress();
    void slotCancelProgress();
    void slotSetActive();
    void slotClosePro();

    void slotUpdateOpenProgress(int count);
    void slotFinishOpenProgress();
    void slotCancelOpenProgress();
public slots:
    void slotOpenPro(const QString& path);

signals:
    void SigCancelProgress();
    void SigCancelOpenProgress();
};

#endif // PROTREEWIDGET_H
