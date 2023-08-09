#include "hellodialog.h"

HelloDialog::HelloDialog(): _ui(new Ui::HelloDialog)
{
    _ui->setupUi(this);
}

HelloDialog::~HelloDialog() {
    delete _ui;
}
