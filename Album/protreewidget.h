#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include "protreethread.h"
#include <QTreeWidget>
#include <QKeyEvent>
#include <QSet>
#include <QAction>
#include <QProgressDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "OpenTreeThread.h"

class SlideShowDialog;

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
    std::shared_ptr<SlideShowDialog> _slide_show_dialog;
    QMediaPlayer* _player;
    QMediaPlaylist* _playlist;

    
private slots:
    void slotItemPressed(QTreeWidgetItem *item, int column);
    void slotDoubleClickItem(QTreeWidgetItem* doubleitem, int column);
    void slotImport();
    void slotUpdateProgress(int count);
    void slotFinishProgress();
    void slotCancelProgress();
    void slotSetActive();
    void slotClosePro();
    void slotSlideShow();

    void slotUpdateOpenProgress(int count);
    void slotFinishOpenProgress();
    void slotCancelOpenProgress();
public slots:
    void slotOpenPro(const QString& path);
    void slotPreShow();
    void slotNextShow();
    void slotSetMusic();
    void slotStartMusic();
    void slotStopMusic();
protected:
    void keyPressEvent(QKeyEvent* e) override;

signals:
    void SigCancelProgress();
    void SigCancelOpenProgress();
    void SigUpdateSelected(const QString& path);
    void SigUpdatePic(const QString& path);
    void SigKeyUp();
    void SigKeyDown();
    void SigClearSelected();
};

#endif // PROTREEWIDGET_H
