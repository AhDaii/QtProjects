#ifndef OPENTREETHREAD_H
#define OPENTREETHREAD_H

#include <QThread>
#include <QTreeWidget>

class OpenTreeThread : public QThread
{
    Q_OBJECT
public:
    explicit OpenTreeThread(const QString& src_path, int file_count,
                            QTreeWidget* self, QObject *parent = nullptr);
    void openProTree(const QString& src_path, int& file_count, QTreeWidget* self);
protected:
    virtual void run();
private:
    void RecursiveProTree(const QString& src_path, int& file_count, QTreeWidget* self,
                          QTreeWidgetItem* root, QTreeWidgetItem* parent, QTreeWidgetItem* preitem);
    QString _src_path;
    int _file_count;
    QTreeWidget *_self;
    QTreeWidgetItem *_root;
    QTreeWidgetItem *_pre_item;
    bool _bstop;

signals:
    void SigUpdateProgress(int count);
    void SigFinishProgress(int count);

public slots:
    void slotCancelProgress();
};

#endif // OPENTREETHREAD_H
