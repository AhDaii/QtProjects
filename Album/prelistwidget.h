#ifndef PRELISTWIDGET_H
#define PRELISTWIDGET_H

#include <QMap>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QPoint>

class PreListWidget : public QListWidget
{
    Q_OBJECT
public:
    PreListWidget(QWidget* parent = nullptr);
    virtual ~PreListWidget();

public slots:
    void slotUpPreList(QTreeWidgetItem* tree_item);
    void slotUpSelect(QTreeWidgetItem* tree_item);
    void slotItemPressed(QListWidgetItem* item);

private:
    QMap<QString, QListWidgetItem*> _map_items;
    QPoint _pos_origin;
    int _cnt;
    int _last_index, _pre_index;
    void addListPath(const QString& path);

signals:
    void SigUpSelectShow(QString path);
};

#endif // PRELISTWIDGET_H
