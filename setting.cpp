#include "setting.h"
#include "ui_setting.h"
#include <QDebug>
#include <QDialogButtonBox>

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    QRegExp rxPort("^[1-9]$|(^[1-9][0-9]$)|(^[1-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9]$)|(^[1-6][0-5][0-5][0-3][0-5]$)");
    QRegExp rxHost("^(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9])(.)(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9]|0)(.)(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9]|0)(.)(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[0-9])$");

    ui->hostAddrLdt->setValidator(new QRegExpValidator(rxHost));
    ui->hostPortLdt->setValidator(new QRegExpValidator(rxPort));

    connect(ui->buttonBox,SIGNAL(accepted()),
            this,SLOT(onButtonBoxAccepted()));

    connect(ui->buttonBox,SIGNAL(rejected()),
            this,SLOT(onButtonBoxRejected()));

    settingHost = new ConnectServer;
}

Setting::~Setting(){
    delete ui;
}
QHostAddress Setting::getHostAddr()
{
    if(ui->hostAddrLdt->text()!=""){
        return QHostAddress(ui->hostAddrLdt->text());
    }else{
        qDebug()<<"主机地址不能为空";
        return QHostAddress("127.0.0.1");
    }
}

qint16 Setting::getHostPort()
{
    if(ui->hostPortLdt->text()!=""){
         return ui->hostPortLdt->text().toInt();
    }else{
        qDebug()<<"主机端口不能为空";
        return qint16(9527);
    }

}

void Setting::onButtonBoxAccepted()
{
    if(ui->hostAddrLdt->text()==""){
        qDebug()<<"主机地址不能为空";
    }else if(ui->hostPortLdt->text()==""){
        qDebug()<<"主机端口不能为空";
    }else{
        this->settingHost->setHost(QHostAddress(ui->hostAddrLdt->text()));
        this->settingHost->setPort(ui->hostPortLdt->text().toInt());
        qDebug()<<"setHostInfoSetting";
        this->close();
   }

}
void Setting::onButtonBoxRejected()
{
    this->close();
}
