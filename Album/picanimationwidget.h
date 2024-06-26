#ifndef PICANIMATIONWIDGET_H
#define PICANIMATIONWIDGET_H

#include <QMap>
#include <QPaintEvent>
#include <QWidget>
#include <QTimer>
#include <QTreeWidget>

class PicAnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PicAnimationWidget(QWidget *parent = nullptr);
    ~PicAnimationWidget();
    void setPixmap(QTreeWidgetItem* item);
    void start();
    void stop();

    void slidePre();
    void slideNext();

public slots:
    void slotUpSelectShow(QString path);
    void slotStartOrStop();

protected:
    virtual void paintEvent(QPaintEvent* e) override;

private:
    bool _b_start;
    float _factor;
    QTimer* _timer;
    QPixmap _pixmap1, _pixmap2;
    QTreeWidgetItem *_cur_item;
    QMap<QString, QTreeWidgetItem*> _map_items;

    void upSelectPixmap(QTreeWidgetItem* item);

signals:
    void SigUpPreList(QTreeWidgetItem*);
    void SigSelectItem(QTreeWidgetItem*);
    void SigStart();
    void SigStop();
    void SigStartMusic();
    void SigStopMusic();

private slots:
    void timeOut();
};

#endif // PICANIMATIONWIDGET_H
