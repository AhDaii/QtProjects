#ifndef PICSHOW_H
#define PICSHOW_H

#include <QDialog>
#include <QEvent>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPixmap>

namespace Ui {
class PicShow;
}

class PicShow : public QDialog
{
    Q_OBJECT

public:
    explicit PicShow(QWidget *parent = nullptr);
    ~PicShow();
protected:
    bool event(QEvent* event) override;
public slots:
    void slotSelectItem(const QString& path);
    void slotUpdatePic(const QString& path);
    void slotDeleteItem();
private:
    void showPreNextBtns(bool b_show);
    Ui::PicShow *ui;
    bool _b_btnvisible;
    QPropertyAnimation* _animation_show_pre;
    QPropertyAnimation* _animation_show_next;
    QString _selected_path;
    QPixmap _pix_map;

signals:
    void SigPreClicked();
    void SigNextClicked();
};

#endif // PICSHOW_H
