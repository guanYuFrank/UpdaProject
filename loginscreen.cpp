#include "loginscreen.h"
#include "ui_loginscreen.h"
#include"ui_qwidgettitle.h"
#include "qwidgettitle.h"

LoginScreen::LoginScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginScreen)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->hide();



    //this->setStyleSheet("background-color:rgb(255,255,255)");

    //测试
//    connect(ui->pushButton,&QPushButton::clicked,[=](){
//       QWidgetTitle * title = new QWidgetTitle;
//       title->show();
//    });


}

LoginScreen::~LoginScreen()
{
    delete ui;
}

