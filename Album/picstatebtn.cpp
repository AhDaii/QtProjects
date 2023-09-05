#include "picstatebtn.h"

PicStateBtn::PicStateBtn(QWidget *parent): QPushButton(parent)
{

}

void PicStateBtn::setIcons(const QString &normal, const QString &hover, const QString &pressed, const QString &normal_2, const QString &hover_2, const QString &pressed_2)
{
    _normal = normal;
    _hover = hover;
    _pressed = pressed;

    _normal_2 = normal_2;
    _hover_2 = hover_2;
    _pressed_2 = pressed_2;

    QPixmap tmp;
    tmp.load(normal);
    this->resize(tmp.size());
    this->QAbstractButton::setIcon(tmp);
    this->setIconSize(tmp.size());
    _cur_state = Normal;
}

bool PicStateBtn::event(QEvent *e)
{
    switch(e->type()) {
    case QEvent::Enter:
        if (_cur_state < PicBtnState::Normal_2) {
            setHoverIcon();
        } else {
            setHover2Icon();
        }
        break;
    case QEvent::Leave:
        if (_cur_state < PicBtnState::Normal_2) {
            setNormalIcon();
        } else {
            setNormal2Icon();
        }
        break;
    case QEvent::MouseButtonPress:
        if (_cur_state < PicBtnState::Normal_2) {
            setPressIcon();
        } else {
            setPress2Icon();
        }
        break;
    case QEvent::MouseButtonRelease:
        if (_cur_state < PicBtnState::Normal_2) {
            setHover2Icon();
        } else {
            setHoverIcon();
        }
        break;
    default:
        break;
    }
    return QPushButton::event(e);
}

void PicStateBtn::setNormalIcon()
{
    QPixmap tmp;
    tmp.load(_normal);
    this->setIcon(tmp);
    _cur_state = Normal;
}

void PicStateBtn::setHoverIcon()
{
    QPixmap tmp;
    tmp.load(_hover);
    this->setIcon(tmp);
    _cur_state = Hover;
}

void PicStateBtn::setPressIcon()
{
    QPixmap tmp;
    tmp.load(_pressed);
    this->setIcon(tmp);
    _cur_state = Pressed;
}

void PicStateBtn::setNormal2Icon()
{
    QPixmap tmp;
    tmp.load(_normal_2);
    this->setIcon(tmp);
    _cur_state = Normal_2;
}

void PicStateBtn::setHover2Icon()
{
    QPixmap tmp;
    tmp.load(_hover_2);
    this->setIcon(tmp);
    _cur_state = Hover_2;
}

void PicStateBtn::setPress2Icon()
{
    QPixmap tmp;
    tmp.load(_pressed_2);
    this->setIcon(tmp);
    _cur_state = Pressed_2;
}

void PicStateBtn::slotStart()
{
    setNormal2Icon();
}

void PicStateBtn::slotStop()
{
    setNormalIcon();
}
