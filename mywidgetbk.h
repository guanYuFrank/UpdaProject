#ifndef MYWIDGETBK_H
#define MYWIDGETBK_H

#include <QWidget>
#include<QEvent>
#include<QDebug>
#include<QToolButton>
#include<QtEvents>

class myWidgetBk : public QWidget
{
    Q_OBJECT
public:
    explicit myWidgetBk(QWidget *parent = nullptr);

    //进入QWidget瞬间事件
    void  enterEvent(QEnterEvent *event);
    //离开QWidget瞬间事件
    void leaveEvent(QEvent *event);

    //设置当前背景色
    void setBgRgb(QString &rgb);

    QString m_rgb;


signals:

};

#endif // MYWIDGETBK_H
