#include <QApplication>
#include <QDialog>
#include <QLabel>
#include "hellodialog2.h"
//#include "hellodialog.h"
//#include "ui_Hellodialog.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
//    QDialog w;
//    QLabel label(&w);
//    label.setText("Hello World");
//    w.resize(400, 300);
//    label.move(120, 120);

//    Ui::HelloDialog ui;
//    ui.setupUi(&w);
//    w.show();
    HelloDialog2 d;
    d.show();


    return a.exec();
}
