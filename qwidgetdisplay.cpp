#include "qwidgetdisplay.h"

QWidgetDisplay::QWidgetDisplay()
{
  QWidgetDisplay * qwidgetDisplay = new QWidgetDisplay;
}

//进入QWidget瞬间事件
void QWidgetDisplay::enterEvent(QEvent *)
{
 qDebug()<<"鼠标进入了";
}

//void setBackgroudRGB(QString &backgroundrgb)
//{

//}

//离开QWidget瞬间事件
//void  QWidgetDisplay::leaveEvent(QEvent *)
//{

//}
