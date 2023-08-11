#ifndef MYACTION_H
#define MYACTION_H

#include <QWidgetAction>
#include <QLineEdit>

class MyAction : public QWidgetAction
{
    Q_OBJECT
signals:
    void getText(const QString& string);
public:
    explicit MyAction(QObject *parent);
protected:
    virtual QWidget* createWidget(QWidget* parent);
private slots:
    void sentText();

private:
    QLineEdit* lineEdit;

};

#endif // MYACTION_H
