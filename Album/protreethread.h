#ifndef PROTREETHREAD_H
#define PROTREETHREAD_H

#include <QThread>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class ProTreeThread : public QThread
{
public:
    ProTreeThread(const QString& src_path, const QString& dist_path, QTreeWidgetItem* parent_item, int file_count,
                QTreeWidget* self, QTreeWidgetItem* root, QObject* parent = nullptr);
    ~ProTreeThread();
protected:
    virtual void run();
private:
    void createProTree(const QString& src_path, const QString& dist_path, QTreeWidgetItem* parent_item,
QTreeWidget* self, QTreeWidgetItem* root, QObject* parent = nullptr);

    QString _src_path, _dist_path;
    int _file_count;
    QTreeWidgetItem *_parent_item, *_root;
    QTreeWidget *_self;
    bool _bstop;
};

#endif // PROTREETHREAD_H
