#include "mywidgetbk.h"

myWidgetBk::myWidgetBk(QWidget *parent)
    : QWidget{parent}
{
    //设置默认追踪鼠标，否则在触发鼠标移动时，必须先点一下才有效
    this->setMouseTracking(true);

}


//进入QWidget瞬间事件
void  myWidgetBk::enterEvent(QEnterEvent *event)
{
    //qDebug()<<"鼠标进入了！";
    this->setStyleSheet(m_rgb);
}
//离开QWidget瞬间事件
void myWidgetBk::leaveEvent(QEvent *event)
{
  //qDebug()<<"鼠标离开了！";
  this->setStyleSheet(0);
}

//设置当前背景色
void myWidgetBk::setBgRgb(QString &rgb)
{
    this->m_rgb = rgb;
}
