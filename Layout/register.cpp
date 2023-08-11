#include "register.h"
#include "ui_register.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

//    this->setMaximumSize(400, 300);
//    this->setMinimumSize(400, 300);

    auto v_box = new QVBoxLayout();
    auto v_top_spacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    v_box->addSpacerItem(v_top_spacer);

    auto name_h_box = new QHBoxLayout();
    auto h_name_spacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    auto name_label = new QLabel();
    name_label->setText("用户：");
    auto name_lineedit = new QLineEdit();
    auto h_name_spacer2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    name_h_box->addItem(h_name_spacer);
    name_h_box->addWidget(name_label);
    name_h_box->addWidget(name_lineedit);
    name_h_box->addItem(h_name_spacer2);
    v_box->addItem(name_h_box);

    auto pwd_h_box = new QHBoxLayout();
    auto h_pwd_spacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    auto pwd_label = new QLabel();
    pwd_label->setText("密码：");
    auto pwd_lineedit = new QLineEdit();
    pwd_lineedit->setEchoMode(QLineEdit::Password);
    auto h_pwd_spacer2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    pwd_h_box->addItem(h_pwd_spacer);
    pwd_h_box->addWidget(pwd_label);
    pwd_h_box->addWidget(pwd_lineedit);
    pwd_h_box->addItem(h_pwd_spacer2);
    auto v_mid_spacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
    v_box->addItem(v_mid_spacer);
    v_box->addItem(pwd_h_box);

    auto reg_h_box = new QHBoxLayout();
    auto reg_spacer = new QSpacerItem(130, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    auto reg_btn = new QPushButton("注册");
    auto reg_spacer2 = new QSpacerItem(130, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    reg_h_box->addItem(reg_spacer);
    reg_h_box->addWidget(reg_btn);
    reg_h_box->addItem((reg_spacer2));
    v_box->addItem(reg_h_box);


    auto v_top_spacer2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);
    v_box->addSpacerItem(v_top_spacer2);
    this->setLayout(v_box);
    this->setModal(true);
}

Register::~Register()
{
    delete ui;
}
