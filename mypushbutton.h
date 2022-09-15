#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    //进入QPushButton瞬间事件
    void  enterEvent(QEnterEvent *event);

    //离开QPushButton瞬间事件
    void leaveEvent(QEvent *event);

    //设置背景颜色
    void setBgRGB (QString &bg);

    //点击按钮返回界面 参数1 返回界面对象
    void backScreen(QWidget * widget);


    //背景颜色
    QString m_bg;

signals:

};

#endif // MYPUSHBUTTON_H
