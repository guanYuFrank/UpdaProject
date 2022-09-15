#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include "qlabel.h"
#include <QWidget>
#include<QMouseEvent>

namespace Ui {
class RegisterScreen;
}

class RegisterScreen : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterScreen(QWidget *parent = nullptr);
    ~RegisterScreen();

    //lab动画播放函数 参数1 动画资源路径 参数2 动画播放总时长 参数3 播放的lab对象
    void palyAnimation(QString res,int sec, QLabel * lab);

    //重写鼠标按下事件 记录鼠标左键按下时位置
    void mousePressEvent(QMouseEvent *event);

    //重写鼠标移动事件,让界面可以随着鼠标拖拽移动
    void mouseMoveEvent(QMouseEvent *event);

    //申请重名检测
    bool checkUserName(QString username);

    //密码强度检测
    bool checkPwdLevel();

    //密码一致性检测
    bool checkPwdConsistent();

    //电话号码规则检查
    bool checkTel();

    //邮箱合规性检测
    bool checkEmail();


    //记录鼠标移动的位置
    QPoint m_whereismouse;

signals:
    //自定义信号 告诉登录界面 点击了返回
    void registerSceenBack();

private:
    Ui::RegisterScreen *ui;
};

#endif // REGISTERSCREEN_H
