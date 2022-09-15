#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton{parent}
{

}


//进入QPushButton瞬间事件
void  MyPushButton::enterEvent(QEnterEvent *event)
{
    //qDebug()<<"鼠标进入按钮";
    this->setStyleSheet(m_bg);
}
//离开QPushButton瞬间事件
void MyPushButton::leaveEvent(QEvent *event)
{
    //qDebug()<<"鼠标离开按钮";
    this->setStyleSheet(0);
}

//设置背景颜色
void MyPushButton::setBgRGB (QString &bg)
{
    this->m_bg = bg;
}

//点击按钮返回界面 参数1 返回界面对象
void MyPushButton::backScreen(QWidget * widget)
{
    connect(this,&QPushButton::clicked,[=](){


    } );
}
