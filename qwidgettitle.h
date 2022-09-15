#ifndef QWIDGETTITLE_H
#define QWIDGETTITLE_H

#include "qsqlquery.h"
#include <QWidget>
#include<QPoint>



namespace Ui {
class QWidgetTitle;
}

class QWidgetTitle : public QWidget
{
    Q_OBJECT

public:
    explicit QWidgetTitle(QWidget *parent = nullptr);
    ~QWidgetTitle();

//    void tbtn_close_chicked();
//    void tbtn_min_chicked();
//    void tbtn_max_chicked();
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);

    //重写绘图事件
    void paintEvent(QPaintEvent *event);

    //记录鼠标移动的位置
    QPoint m_whereismouse;

    bool companiesBycomboBox(QString &name);

    //判断输入的用户名是否存在
    bool compareForSql(QString &username);

    //判断用户输入的用户名密码是否正确
    bool compareForSql(QString &username,QString &pwd);


    //用户是否存在数据库的标志
    bool m_flag = false;





private:
    Ui::QWidgetTitle *ui;
};

#endif // QWIDGETTITLE_H
