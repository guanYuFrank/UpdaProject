#ifndef MESSAGELABLE_H
#define MESSAGELABLE_H

#include <QLabel>
#include<QWidget>

class MessageLable : public QLabel
{
    Q_OBJECT
public:
//    explicit MessageLable(QWidget *parent = nullptr);

    MessageLable();

    //参数1：传入mlab的父类 参数2：需要显示的信息 参数3 字体显示的颜色
    void initialize(QWidget *parent, QString message, QString color);
    //参数1 进入动画时间 参数2 离开动画时间 参数3 动画间定时器时间
    void animation(int inDuration,int outDuration,int timInterval);

    ~MessageLable();

signals:

};

#endif // MESSAGELABLE_H
