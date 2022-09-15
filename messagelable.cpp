#include "messagelable.h"

#include<QPropertyAnimation>
#include<QTimer>
#include<QFont>


//MessageLable::MessageLable(QWidget *parent)
//    : QLabel{parent}
//{

//}
    MessageLable::MessageLable()
    {

    }

     void MessageLable::initialize(QWidget *parent, QString message,QString color)
     {
         this->setParent(parent);
         this->setGeometry(0,0,parent->width(),30);
         this->setFrameShape(QFrame::Box);
         //this->setStyleSheet("border-width:1px;border-style:solid;border-color:rgb(255,0,0);");
         QString strStyle ="font-size:26px;%1;";
         this->setStyleSheet(strStyle.arg(color));//lab背景色：background-color: rgb(255,245,238);
         QFont font ("STXingkai");
         this->setFont(font);
         this->setText(message);
         this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter );//AlignVCenter竖直居中  AlignHCenter水平居中
         this->move((parent->width()-this->width())/2,-this->height());

     }


     void MessageLable::animation(int inDuration,int outDuration,int timInterval)
     {
         QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
         animation->setDuration(inDuration);
         animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
         animation->setEndValue(QRect(this->x(),this->y()+30,this->width(),this->height()));

         QPropertyAnimation * animation2 = new QPropertyAnimation(this,"geometry");
         animation2->setDuration(outDuration);
         animation2->setStartValue(QRect(this->x(),this->y()+30,this->width(),this->height()));
         animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

         QTimer * tim = new QTimer(this);
         tim->setInterval(timInterval);
         tim->setSingleShot(true);

         animation->start();
         tim->start();
         connect(tim,&QTimer::timeout,[=](){
            animation2->start();
         } );

     }


     MessageLable::~MessageLable()
     {

     }
