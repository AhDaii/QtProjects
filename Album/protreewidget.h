#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QTreeWidget>
#include <QSet>

class ProTreeWidget : public QTreeWidget
{
public:
    ProTreeWidget(QWidget *parent = nullptr);
    void addProToTree(const QString &name, const QString &path);
private:
    QSet<QString> _set_path;
};

#endif // PROTREEWIDGET_H
