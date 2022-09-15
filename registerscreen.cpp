#include "registerscreen.h"
#include "ui_registerscreen.h"
#include<QMovie>
#include<QTimer>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QRegExp>
#include<QRegularExpression>
#include<QValidator>
#include<QRegularExpressionValidator>
#include<QPixmap>



RegisterScreen::RegisterScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterScreen)
{
    ui->setupUi(this);

/*********************************************************************/
/*************************界面初始化************************************/
/********************************************************************/

    //界面的基本属性
    this->setFixedSize(1200,675);
    this->setStyleSheet("background-color: rgb(255,245,238);");
    this->setWindowFlags(Qt::FramelessWindowHint);//设置QWidget无边框

    //播放界面左侧动画
    QString resLeftScreen = ":/res/registerMovie.gif";
    int movieInterval = 32000;
    this->palyAnimation(resLeftScreen,movieInterval,ui->movieLab);

    //底部三个按钮初始化属性
    QString backBtnBackground = "background-color: rgb(0, 0, 255);";
    QString quitBtnBackground = "background-color: rgb(255, 0, 0);";
    QString submitBtnBackground = "background-color: rgb(0, 255, 0);";

    ui->backBtn->setBgRGB(backBtnBackground);
    ui->quitBtn->setBgRGB(quitBtnBackground);
    ui->submitBtn->setBgRGB(submitBtnBackground);

/*********************************************************************/
/************************监控lineEdit输入数据***************************/
/********************************************************************/

    //用户名重复注册检查
    connect(ui->userNameEdit,&QLineEdit::editingFinished,[=](){

        this->checkUserName(ui->userNameEdit->text());

    });

    //密码强度检测
    connect(ui->passWordEdit,&QLineEdit::editingFinished,[=](){

        this->checkPwdLevel();

    } );

    //密码一致性检查
    connect(ui->surePassWordEdit,&QLineEdit::editingFinished,[=](){

        this->checkPwdConsistent();

    } );

    //电话号码合规性检测
    connect(ui->telephoneEdit,&QLineEdit::editingFinished,[=](){

        this->checkTel();

    } );

    //email合规性检测
    connect(ui->emailEdit,&QLineEdit::editingFinished,[=](){

        this->checkEmail();

    } );

/*********************************************************************/
/*************************按钮功能*************************************/
/********************************************************************/

    //点击返回按钮 发送信号 注册界面响应
    connect(ui->backBtn,&QPushButton::clicked,[=](){

        emit this->registerSceenBack();

    } );

    //点击退出按钮
    connect(ui->quitBtn,&MyPushButton::clicked,[=](){

        this->close();

    } );

    //点击申请按钮
    connect(ui->submitBtn,&QPushButton::clicked,[=](){

        //获取用户输入的数据
        QString username = ui->userNameEdit->text();
        QString password = ui->passWordEdit->text();
        QString surepassword = ui->surePassWordEdit->text();
        QString telephone = ui->telephoneEdit->text();
        QString email = ui->emailEdit->text();
        QString role = ui->roleComboBox->currentText().trimmed();


    } );



}


void RegisterScreen::palyAnimation(QString res, int sec,QLabel * lab)//lab动画播放函数
{

    QMovie * movie = new QMovie(res);
    QSize si(lab->width(),lab->height());
    movie->setScaledSize(si);
    lab->setMovie(movie);
    movie->start();

    QTimer * tim = new QTimer(lab);
    tim->setInterval(sec);
    tim->setSingleShot(true);
    tim->start();
    connect(tim,&QTimer::timeout,[=](){
        movie->stop();
    });
}
//重写鼠标按下事件 记录鼠标左键按下时位置
void RegisterScreen::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        {
          m_whereismouse = event->pos();
        }
}

//重写鼠标移动事件,让界面可以随着鼠标拖拽移动
void RegisterScreen::mouseMoveEvent(QMouseEvent *event)
{
    //当窗口最大化或最小化时不进行触发
    if(RegisterScreen::isMaximized() || RegisterScreen::isMinimized())
    {
        return;
    }
    else
    {
        //当按钮之内需要鼠标操作的地方不进行触发
        if(ui->backBtn->underMouse() || ui->quitBtn->underMouse() || ui->submitBtn->underMouse())
        {

        }
        else
        {
            RegisterScreen::move(RegisterScreen::mapToGlobal(event->pos()-m_whereismouse));
        }
    }
    event->accept();
}

//申请重名检测
bool RegisterScreen::checkUserName(QString username)
{
    //username是否已注册
    QSqlDatabase mysql;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        mysql = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        mysql = QSqlDatabase::addDatabase("QMYSQL");
    }

    mysql.setHostName("localhost");
    mysql.setDatabaseName("upda");
    mysql.setUserName("root");
    mysql.setPassword("123456");
    mysql.setPort(3306);

    if(!mysql.open())
    {
        qDebug()<<"连接数据库失败："<<mysql.lastError().text();
    }
    else
    {
        qDebug()<<"连接数据库成功!";
    }

    QSqlQuery query;
    QString str = "SELECT * FROM `user` WHERE userName = '%1'";
    QString queryStr = str.arg(username);
    query.exec(queryStr);

    //下面写 判断注册的用户名是否已存在
    if(query.next())
    {
        //qDebug()<<"数据库存在此用户名";
        QPixmap pix(":/res/false.svg");
        ui->userNameLab_tips->setPixmap(pix);
        ui->userNameLab_tips_2->setText("用户名已存在");

    }
    else if(ui->userNameEdit->text().isEmpty())
    {
        //qDebug()<<"未输入任何内容";
        QPixmap pix(":/res/false.svg");
        ui->userNameLab_tips->setPixmap(pix);
        ui->userNameLab_tips_2->setText("必须输入一个用户名");
    }
    else
    {
        //qDebug()<<"数据库无此用户名";
        QPixmap pix(":/res/sure.svg");
        ui->userNameLab_tips->setPixmap(pix);
        ui->userNameLab_tips_2->setText("");
        return true;
    }
    mysql.close();

}

//密码强度检测
bool RegisterScreen::checkPwdLevel()
{
    QRegularExpression expStrong ("(?=^.{8,16}$)((?=.*\\d)|(?=.*\\W+))(?![.\\n])(?=.*[A-Z])(?=.*[a-z]).*$");
    QValidator * valStrong = new QRegularExpressionValidator(expStrong,this);
    int pos = 0;
    QString password = ui->passWordEdit->text();
    if(valStrong->validate(password,pos)==QValidator::Acceptable)
    {
        //qDebug()<<"满足密码强度要求";
        QPixmap pix(":/res/sure.svg");
        ui->passWordLab_tips->setPixmap(pix);
        ui->passWordLab_tips_2->setText("");
        return true;
    }
    else
    {
        //qDebug()<<"不满足，重新输入";
        QPixmap pix(":/res/false.svg");
        ui->passWordLab_tips->setPixmap(pix);
        ui->passWordLab_tips_2->setText("密码需要满足8位以上且包含数字和大小写字母");
    }

}

//密码一致性检测
bool RegisterScreen::checkPwdConsistent()
{
    QString password = ui->passWordEdit->text();
    QString surepassword = ui->surePassWordEdit->text();
    //两次password是否一致
    if(password==surepassword)
    {
        //qDebug()<<"两次输入的密码一致";
        QPixmap pix(":/res/sure.svg");
        ui->surePassWordLab_tips->setPixmap(pix);
        ui->surePassWordLab_tips_2->setText("");
        return true;
    }
    else
    {
        //qDebug()<<"两次输入的密码不一致，请重新输入";
        QPixmap pix(":/res/false.svg");
        ui->surePassWordLab_tips->setPixmap(pix);
        ui->surePassWordLab_tips_2->setText("两次输入的密码不一致，请重新输入");
    }
}

//电话号码规则检查
bool RegisterScreen::checkTel()
{
    //利用正则表达式和QValidator校验器 限制输入正确的手机电话号码
    QRegularExpression expTel("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    QValidator * valTel = new QRegularExpressionValidator(expTel, this);
    //ui->telephoneEdit->setValidator(valTel);

    //电话号码验证

    QString telephone = ui->telephoneEdit->text();
    int pos = 0;
    if(valTel->validate(telephone,pos)==QValidator::Acceptable)
    {
        qDebug()<<"输入的电话号码正确";
        QPixmap pix(":/res/sure.svg");
        ui->telephoneLab_tips->setPixmap(pix);
        ui->telephoneLab_tips_2->setText("");
        return true;
    }
    else
    {
        qDebug()<<"输入的不是手机号";
        QPixmap pix(":/res/false.svg");
        ui->telephoneLab_tips->setPixmap(pix);
        ui->telephoneLab_tips_2->setText("输入的不是手机号码");
    }

}

//邮箱合规性检测
bool RegisterScreen::checkEmail()
{
    //限制邮箱的输入格式
    QRegularExpression expEmail("[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+\\.[a-zA-Z]+");
    QValidator * valEmail = new QRegularExpressionValidator(expEmail, this);
    //ui->emailEdit->setValidator(valEmail);

    //邮箱验证
    QString email = ui->emailEdit->text();
    int pos = 0;
    if(valEmail->validate(email,pos)==QValidator::Acceptable)
    {
        qDebug()<<"输入的邮箱正确";
        QPixmap pix(":/res/sure.svg");
        ui->emailLab_tips->setPixmap(pix);
        ui->emailLab_tips_2->setText("");
        return true;
    }
    else
    {
        qDebug()<<"请输入正确的邮箱";
        QPixmap pix(":/res/false.svg");
        ui->emailLab_tips->setPixmap(pix);
        ui->emailLab_tips_2->setText("请输入正确的邮箱");
    }

}


RegisterScreen::~RegisterScreen()
{
    delete ui;
}
