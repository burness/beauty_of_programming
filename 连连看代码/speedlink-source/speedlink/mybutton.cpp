#include "mybutton.h"
#include <QSound>

MyButton::MyButton(QWidget *parent) :
    QToolButton(parent)
{
}

void MyButton::enterEvent(QEvent *)
{
    emit mouseOver();
    QSound::play(QString("./sound/buttonMouseMove.wav"));
}

void MyButton::leaveEvent(QEvent *)
{
    emit mouseLeave();
}
