#include "usernamectrl.h"

UserNameCtrl::UserNameCtrl(QWidget *parent)
    : QLineEdit{parent}
{

    this->initData();
    this->initConnect();
    this->initDisplay();

}


void UserNameCtrl::initData()
{
   mainLayout = new QHBoxLayout;
   layout = new QHBoxLayout;
   m_label = new QLabel();
   m_combo = new QComboBox();
   m_combo->setEditable(true);
   _bTime = false;
   m_comPleter = nullptr;

}

void UserNameCtrl::initConnect()
{
    connect(m_combo,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slot_TextChanged(const QString &)));
}

void UserNameCtrl::initDisplay()
{
    mainLayout->addWidget(m_label);
    layout->addWidget(m_combo);
    mainLayout->addLayout(layout);
    mainLayout->setStretch(0,0);
    mainLayout->setStretch(1,1);

    setTextMargins(60,0,0,0);
    setContentsMargins(0,0,0,0);
    setLayout(mainLayout);

    m_combo->setCursor(Qt::PointingHandCursor);
}

//设置“用户名”字样
void UserNameCtrl::setTipInfo(QString sTip)
{
    m_label->setText(sTip);
}

//设置历史记录的多个QComboBox 用户名数据
void UserNameCtrl::setUerList(QStringList list)
{
    m_combo->addItems(list);
       if(nullptr != m_comPleter)
       {
           delete m_comPleter;
           m_comPleter = nullptr;
       }
       m_comPleter = new QCompleter(list, this);
       m_comPleter->setCaseSensitivity(Qt::CaseInsensitive);//补齐大小写不敏感
       m_comPleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);//大小写不敏感排序
       m_combo->setCompleter(m_comPleter);
}

//设置当前的用户名，若用户名存在则之间设置，不存在先插入QComboBox再设置
void UserNameCtrl::setCurText(QString sText)
{
    if(-1 == m_combo->findText(sText))//当前没有该用户
       {
           QStringList list;
           list.clear();
           m_combo->addItem(sText);
       }

       m_combo->setCurrentText(sText);

}

//获取当前设置的用户名
QString UserNameCtrl::curText()
{
  return m_combo->currentText();
}

//void UserNameCtrl::slot_TextChanged(const QString &text)
//{
//    if(text.length() > NAMEMAXLEN)
//    {
//        m_combo->setCurrentText(text.left(NAMEMAXLEN));
//        return ;
//    }
//    emit sig_TextChanged(text);
//}




UserNameCtrl:: ~UserNameCtrl()
{

}
