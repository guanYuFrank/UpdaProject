#ifndef USERNAMECTRL_H
#define USERNAMECTRL_H

#include "qboxlayout.h"
#include <QWidget>
#include<QLineEdit>
#include<QLabel>
#include<QComboBox>
#include<QCompleter>

#define NAMEMAXLEN 20//限制用户名的最大输入长度


class UserNameCtrl : public QLineEdit
{
    Q_OBJECT
public:
    explicit UserNameCtrl(QWidget *parent = nullptr);
    ~UserNameCtrl();

    //设置“用户名”字样
    void setTipInfo(QString sTip);

    //设置历史记录的多个QComboBox 用户名数据
    void setUerList(QStringList list);

    //设置当前的用户名，若用户名存在则之间设置，不存在先插入QComboBox再设置
    void setCurText(QString sText);

    //获取当前设置的用户名
    QString curText();


    void initData();
    void initConnect();
    void initDisplay();

    QLabel *m_label;
    QComboBox *m_combo;
    QHBoxLayout *mainLayout;
    QHBoxLayout *layout;
    QCompleter *m_comPleter;

    bool _bTime;


signals:
    void slot_TextChanged(const QString &text);
    void sig_TextChanged(const QString &sName);//当用户名数据有变化时发出的信号，内容为当前的用户名数据

};

#endif // USERNAMECTRL_H
