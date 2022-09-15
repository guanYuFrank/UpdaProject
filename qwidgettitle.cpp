#include "qwidgettitle.h"
#include "ui_qwidgettitle.h"
#include<QEvent>
#include<QMouseEvent>
#include<QPainter>
#include<QComboBox>
#include"mypushbutton.h"
#include<QFile>
#include<QDir>
#include<QCompleter>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include"mainproject.h"
#include<QPropertyAnimation>
#include<QTimer>

#include"messagelable.h"
#include"registerscreen.h"

QWidgetTitle::QWidgetTitle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QWidgetTitle)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);//设置QWidget无边框
    this->setStyleSheet("QWidget{border:0px;}");//设置主窗口为不规整显示
    //this->setAttribute(Qt::WA_TransparentForMouseEvents,true);


    //重新构建  关闭按钮
    ui->tbtn_close->setIcon( QIcon(":/res/btn_close.png") );
    //设置鼠标进入按钮背景显示
    QString str = "background-color: rgb(255, 129, 112);";
    ui->widget_tbtn_close->setBgRgb(str);

    //ui->tbtn_close->setStyleSheet( "QToolButton{border:0px}" );
    // ui->tbtn_close->setStyleSheet(" border:none");

    //实现 关闭按钮功能
    connect(ui->tbtn_close,&QToolButton::clicked,[=](){
        this->close();
    } );

    //重新构建  最小化按钮
    ui->tbtn_min->setIcon( QIcon(":/res/btn_min.png") );

    //设置鼠标进入按钮背景显示
    QString str2 = "background-color: rgb(76, 201, 255);";
    ui->widget_tbtn_min->setBgRgb(str2);

    //ui->tbtn_min->setStyleSheet( "QToolButton{border:0px}" );
    //ui->tbtn_min->setStyleSheet(" border:none");

    //实现 最小化按钮功能
    connect(ui->tbtn_min,&QToolButton::clicked,[=](){
        QWidgetTitle::showMinimized();
    } );


    //用户名输入comboBox设置
    ui->comboBox->setEditable(true);//设置用户输入comboBox为可编辑

    ui->comboBox->clear();
    QString path = "D:/upda/updaproject/comboBox_username.txt";
    QFile  file(path);
    //打开文件，读取保存的用户名
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream in(&file);
    //一直读，直至读取失败
    while(!in.atEnd()){
        QString username;
        //从文件中读取一个字符串
        in >> username;
        if(username != "")
        {
           ui->comboBox->addItem(username);
        }

        //qDebug() << username;
    }
    file.close();


    //构建comboBox在输入时可以自动补齐相似选项

    QStringList list;
    for(int i = 0; i < ui->comboBox->count(); i++)
    {
        //qDebug()<<ui->comboBox->itemText(i);
         list << ui->comboBox->itemText(i) ;

    }
    //qDebug()<<list;


    // 自动补全实例的构建
    QCompleter *comp = new QCompleter(list,ui->comboBox->model());

    // 设置匹配模式，只要包含就显示
    comp->setFilterMode(Qt::MatchContains);

    // 设置大小写区分，不区大小写
    comp->setCaseSensitivity(Qt::CaseInsensitive);

    // 设置向用户提供补全的方式
    comp->setCompletionMode(QCompleter::PopupCompletion);

    // 装载补全实例
    ui->comboBox->setCompleter(comp);



      QString str3 = "background-color: rgb(255, 230, 199);";
      ui->btn_register->setBgRGB(str3);
      ui->btn_login->setBgRGB(str3);

      //实例化系统主界面
      MainProject * mainProject = new MainProject;

      //实例化注册界面
      RegisterScreen * registerScreen = new RegisterScreen;

      //实例出登录失败提示lab，后面调用。
      QString errorLoginName = "用户不存在！请先完成注册。";
      MessageLable * errorLoginNameLab = new MessageLable();
      QString colorRed = "color:rgb(255,0,0)";
      errorLoginNameLab->initialize(this,errorLoginName,colorRed);

      QString errorLoginNameOrPwd = "用户名密码错误！请重新输入。";
      MessageLable * errorLoginNameOrPwdLab = new MessageLable();
      errorLoginNameOrPwdLab->initialize(this,errorLoginNameOrPwd,colorRed);

      //实例出登录成功提示lab，后面调用
      QString tipsLoginSucceed = "恭喜您，登录成功！";
      MessageLable * tipsLoginSucceedLab = new MessageLable();
      QString colorGreen = "color:rgb(0,128,0)";
      tipsLoginSucceedLab->initialize(this,tipsLoginSucceed,colorGreen);






      //注册按钮功能
      connect(ui->btn_register,&QPushButton::clicked,[=](){

          qDebug()<<"点击注册";
          //隐藏登录窗口 展示系统主窗口
          this->hide();
          //使注册界面初始展示的位置 和 登录窗口隐藏时位置一致
          registerScreen->setGeometry(this->geometry());
          registerScreen->show();
      });
      //注册界面返回按钮发出信号后 登录界面重新展示
      connect(registerScreen,&RegisterScreen::registerSceenBack,[=](){

          this->setGeometry(registerScreen->geometry());
          registerScreen->hide();
          this->show();
      } );


      //密码输入框lineEdit接收键盘回车键信号，触发登录按钮点击
      connect(ui->lineEdit,&QLineEdit::returnPressed,ui->btn_login,&QPushButton::click);

      //登录按钮功能
      connect(ui->btn_login,&QPushButton::clicked,[=](){

          qDebug()<<"点击登录";
          //先获取当前用户输入的 用户名和密码
          QString username = ui->comboBox->currentText().trimmed();
          //qDebug()<<"当前comboBox输入框的"<<username;

          QString pwd =ui->lineEdit->text();
          //qDebug()<<"用户输入的密码："<<pwd;

          //判断用户是否注册系统
          bool compareRet = this->compareForSql(username);
          if(!compareRet)
          {
              errorLoginNameLab->animation(600,1000,1500);
              qDebug()<<"用户不存在！请先完成注册。";
          }
          else
          {
              qDebug()<<"数据库存在此用户";
              //判断用户名密码是否正确
              bool pwdRet = this->compareForSql(username,pwd);
              if(pwdRet)
              {
                  qDebug()<<"用户名密码验证成功！";

                  tipsLoginSucceedLab->animation(1000,500,1500);

                  //登录成功后执行该用户名保存到comboBox配置文件中
                  bool ret = this->companiesBycomboBox(username);
                  if(ret)
                  {
                  QString path = "D:/upda/updaproject/comboBox_username.txt";
                  QFile  file(path);

                   if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
                   {
                          qDebug()<<"文件打开失败了";
                          return;
                   }
                   QTextStream out(&file);
                   //向文件中写入字符串
                   QString str ="\n";
                   out << (QString)username+str;
                   //关闭文件
                   file.close();
                  }

                  QTimer * tim = new QTimer(this);
                  tim->setInterval(2500);
                  tim->setSingleShot(true);
                  tim->start();

                  connect(tim,&QTimer::timeout,[=](){

                      //隐藏登录窗口 展示系统主窗口
                      this->hide();
                      //使主窗口初始展示的位置 和 登录窗口隐藏时位置一致
                      mainProject->setGeometry(this->geometry());
                      mainProject->show();

                  } );

              }
              else
              {
                  errorLoginNameOrPwdLab->animation(600,1000,1500);
                  qDebug()<<"用户名密码错误，请重新输入！";
              }

          }

      });




}


//重写鼠标按下事件
void QWidgetTitle::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        {
          m_whereismouse = event->pos();
        }
}
//重写鼠标移动事件
void QWidgetTitle::mouseMoveEvent(QMouseEvent *event)
{

    if(event->buttons() == Qt::LeftButton)
        {
            //当窗口最大化或最小化时也不进行触发
            if(QWidgetTitle::isMaximized() || QWidgetTitle::isMinimized())
            {
                return;
            }
            else
            {
                //当在按钮之内需要鼠标操作的地方不进行触发(防误触)
                if (ui->tbtn_close->underMouse()||ui->tbtn_min->underMouse())
                {
                }
                else
                {
                    QWidgetTitle::move(QWidgetTitle::mapToGlobal(event->pos()-m_whereismouse));//移动
                }
            }
        }
        event->accept();

}

//重写绘图事件
void QWidgetTitle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background.png");
    painter.drawPixmap(QRect(0,0,this->width(),this->height()),pix);
}

//判断文件是否含有相同的字符串
bool QWidgetTitle::companiesBycomboBox(QString &name)
{
    QString path = "D:/upda/updaproject/comboBox_username.txt";
    QFile  file(path);
    //打开文件，读取保存的用户名
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
    }
    QTextStream in(&file);
    //一直读，直至读取失败
    while(!in.atEnd())
    {
        QString username;
        //从文件中读取一个字符串
        in >> username;
        if(username == name)
        {
           return false;
        }

    }
    file.close();
}

//判断输入的用户名是否存在
bool QWidgetTitle::compareForSql(QString &username)
{

    //准备数据库连接参数
    //如果不设定数据库连接名 就调用默认连接名
    QSqlDatabase mysql;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        mysql = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        mysql = QSqlDatabase::addDatabase("QMYSQL");
    }

    //设置数据库连接参数
    mysql.setHostName("localhost");
    mysql.setDatabaseName("upda");
    mysql.setUserName("root");
    mysql.setPassword("123456");
    mysql.setPort(3306);
    //连接数据库

    if(!mysql.open())
    {
        qDebug()<<"连接数据库失败："<<mysql.lastError().text();
    }
    else
    {
        qDebug()<<"连接数据库成功";
    }
    //创建QSqlQuery对象
     QSqlQuery query;

    //准备查询语句
    QString queryStr = "SELECT * FROM `user`";
    //调用exec方法执行查询
    query.exec(queryStr);
    //利用while循环遍历查询的数据
    while (query.next()) //next()遍历上面查询表的记录 返回false 代表空 遍历结束
        {
            //取出当前记录的字段值
            //qDebug()<<query.value(1).toString();
           if(username == query.value(1).toString())
            {
                //qDebug()<<query.value(1).toString();
                return true;
                break;
            }

        }
        mysql.close();

}

//判断用户输入的用户名密码是否正确
bool QWidgetTitle::compareForSql(QString &username,QString &pwd)
{
    //准备数据库连接实例
    QSqlDatabase mysql;
    //如果不设定数据库连接名 就调用默认连接名
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        mysql = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        mysql = QSqlDatabase::addDatabase("QMYSQL");
    }
    //配置连接参数
    mysql.setHostName("localhost");
    mysql.setDatabaseName("upda");
    mysql.setUserName("root");
    mysql.setPassword("123456");
    mysql.setPort(3306);
    //建立连接 并判断是否成功
    if(!mysql.open())
    {
        qDebug()<<"连接数据库失败："<<mysql.lastError().text();
    }
    else
    {
        qDebug()<<"连接数据库成功";
    }
    //创建QSqlQuery对象
     QSqlQuery query;
    //准备查询语句
     QString str="SELECT PASSWORD FROM `user` WHERE userName ='%1'";
     QString queryStr = str.arg(username);
    //qDebug()<<queryStr;
    //调用exec方法执行查询
    query.exec(queryStr);
    //利用while循环遍历查询的数据
    while (query.next()) //next()遍历上面查询表的记录 返回false 代表空 遍历结束
        {
           qDebug()<<pwd;
           qDebug()<<query.value(0).toString();
           if(pwd == query.value(0).toString())
            {

                return true;
                break;
            }
           else
           {
                return false;
           }

        }
    mysql.close();

}



QWidgetTitle::~QWidgetTitle()
{
    delete ui;
}
