#ifndef MYEDIT_H
#define MYEDIT_H

#include <QLineEdit>
#include <QWidget>
#include <QDebug>
#include <QKeyEvent>

class MyEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyEdit(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MYEDIT_H
