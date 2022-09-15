#ifndef QWIDGETDISPLAY_H
#define QWIDGETDISPLAY_H

#include <QWidget>
#include<QDebug>

class QWidgetDisplay
{
public:
    QWidgetDisplay();

    void enterEvent(QEvent *); //进入QWidget瞬间事件
    //void leaveEvent(QEvent *); //离开QWidget瞬间事件

    void setBackgroudRGB(QString &backgroundrgb);

    QWidgetDisplay * m_qwidgetDisplay=NULL;

};

#endif // QWIDGETDISPLAY_H
