#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QToolButton>

class MyButton : public QToolButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
signals:
    void mouseOver();
    void mouseLeave();
public slots:

};

#endif // MYBUTTON_H
