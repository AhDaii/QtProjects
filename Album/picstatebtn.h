#ifndef PICSTATEBTN_H
#define PICSTATEBTN_H

#include <QPushButton>
#include <QEvent>
#include "const.h"

class PicStateBtn : public QPushButton
{
public:
    PicStateBtn(QWidget* parent = nullptr);
    void setIcons(const QString& normal, const QString& hover, const QString& pressed,
                 const QString& normal_2, const QString& hover_2, const QString& pressed_2);
    virtual ~PicStateBtn() {}
protected:
    virtual bool event(QEvent* e) override;
private:
    void setNormalIcon();
    void setHoverIcon();
    void setPressIcon();

    void setNormal2Icon();
    void setHover2Icon();
    void setPress2Icon();

    QString _normal, _hover, _pressed;
    QString _normal_2, _hover_2, _pressed_2;
    PicBtnState _cur_state;
public slots:
    void slotStart();
    void slotStop();
};

#endif // PICSTATEBTN_H
