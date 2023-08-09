#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>
#include <QWidget>
#include "ui_Hellodialog.h"

class HelloDialog : public QDialog
{
public:
    HelloDialog();
    ~HelloDialog();
private:
    Ui::HelloDialog *_ui;
};

#endif // HELLODIALOG_H
