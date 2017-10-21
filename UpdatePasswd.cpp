#include "UpdatePasswd.h"
#include "ui_UpdatePasswd.h"

UpdatePasswd::UpdatePasswd(QTcpSocket *socket,Packet data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdatePasswd),socket(socket),data(data)
{
    ui->setupUi(this);
    ui->btn_update->setStyleSheet("QPushButton{background: transparent;border-image: url(:/new/prefix1/login_a.jpg);color: rgb(255, 255, 255);font: 75 18pt 'Hannotate SC';}"
                                  "QPushButton:hover{border-image: url(:/new/prefix1/login_b.jpg);}"
                                  "QPushButton:pressed{border-image: url(:/new/prefix1/login_c.jpg);}");
    ui->le_newpass->setPlaceholderText("请输入新密码");
    //密码，一般是用小黑点覆盖你所输入的字符
    ui->le_newpass->setEchoMode(QLineEdit::Password);
    ui->le_repass->setPlaceholderText("确认新密码");
    ui->le_newpass->setEchoMode(QLineEdit::Password);
}

UpdatePasswd::~UpdatePasswd()
{
    delete ui;
}
//确定更改密码
void UpdatePasswd::on_btn_update_clicked()
{
    Qt::CaseSensitivity cs = Qt::CaseSensitive;

    QString newpasswd = ui->le_newpass->text().trimmed();
    QString repasswd = ui->le_repass->text().trimmed();
    if (newpasswd.compare(repasswd, cs) == 0){
        //全词匹配
        strcpy(data.passwd,newpasswd.toStdString().data());
        data.type = TYPE_UPDATE;
        socket->write((char*)&data,sizeof(data));
    }else
    {
        QMessageBox::critical(this,"修改密码","两次输入的密码不一致");
    }
}
