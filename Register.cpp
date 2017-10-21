#include "Register.h"
#include "ui_Register.h"
#include <QDebug>
Register::Register(QTcpSocket * socket,QWidget *parent) :
    socket(socket),QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    ui->btn_login->setStyleSheet("QPushButton{background: transparent;border-image: url(:/new/prefix1/login_a.jpg);color: rgb(255, 255, 255);font: 75 18pt 'Hannotate SC';}"
                                 "QPushButton:hover{border-image: url(:/new/prefix1/login_b.jpg);}"
                                 "QPushButton:pressed{border-image: url(:/new/prefix1/login_c.jpg);}");
    ui->btn_register->setStyleSheet("QPushButton{background: transparent;border-image: url(:/new/prefix1/login_a.jpg);color: rgb(255, 255, 255);font: 75 18pt 'Hannotate SC';}"
                                    "QPushButton:hover{border-image: url(:/new/prefix1/login_b.jpg);}"
                                    "QPushButton:pressed{border-image: url(:/new/prefix1/login_c.jpg);}");
    ui->btn_verification->setStyleSheet("QPushButton{background: transparent;color: rgb(36, 36, 234);font: 75 16pt 'Hannotate SC';}"
                                        "QPushButton:hover{color: rgb(13, 23, 183);}"
                                        "QPushButton:pressed{color: rgb(26, 30, 200);}");


    ui->le_nickname->setPlaceholderText("请输入昵称");
    ui->le_passwd->setPlaceholderText("请输入密码");
    ui->le_passrewd->setPlaceholderText("请再次输入密码");
    ui->le_phonenumber->setPlaceholderText("请输入手机号");
    ui->le_phoneverification->setPlaceholderText("请输入验证码");
    ui->le_passwd->setEchoMode(QLineEdit::Password);
    ui->le_passrewd->setEchoMode(QLineEdit::Password);
    QRegExp regx("[0-9]+$");
    QValidator *validatorv = new QRegExpValidator(regx,  ui->le_phoneverification );
    ui->le_phoneverification->setValidator(validatorv);
    /**
     * 验证手机号码
     *
     * 移动号码段:139、138、137、136、135、134、150、151、152、157、158、159、182、183、187、188、147
     * 联通号码段:130、131、132、136、185、186、145
     * 电信号码段:133、153、180、189
     *
     **/
    QRegExp regxnumber("^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\\d{8}$");
    QValidator *validator = new QRegExpValidator(regxnumber ,  ui->le_phonenumber );
    ui->le_phonenumber->setValidator( validator );
    ui->le_phonenumber->setMaxLength(11);
    ui->le_phoneverification->setMaxLength(6);


}

Register::~Register()
{
    delete ui;
}

void Register::on_btn_register_clicked()
{
    QString nickname = ui->le_nickname->text();
    QString passwd = ui->le_passwd->text();
    QString passwrewd = ui->le_passrewd->text();
    QString phonenumber = ui->le_phonenumber->text();
    QString verification = ui->le_phoneverification->text();

    if(nickname.isEmpty())
    {
        QMessageBox::critical(this,"QQ注册","请输入昵称");
        return ;
    }

    else if(passwd!=passwrewd)
    {
        QMessageBox::critical(this,"QQ注册","两次输入的密码不一致，请重新输入");
        return ;
    }
    else if(phonenumber.isEmpty())
    {
        QMessageBox::critical(this,"QQ注册","请输入手机号码");
        return ;
    } else if(verification.isEmpty())
    {
        QMessageBox::critical(this,"QQ注册","请输入验证码");
        return ;
    }
    else
    {
        //把信息 添加data ，然后传递给服务器  这个地方最好用json
        qDebug()<<"nickname:"<<nickname;
        qDebug()<<"passwd:"<<passwd  ;
        qDebug()<<"passwrewd:"<<passwrewd ;
        qDebug()<<"phonenumber:"<<phonenumber  ;
        qDebug()<<"verification:"<<verification;
        //接收回来的信息

        Packet data;
        strcpy(data.nickname,nickname.toStdString().data());
        strcpy(data.passwd,passwd.toStdString().data());
        strcpy(data.phonenumber,phonenumber.toStdString().data());
        data.type = TYPE_REG;
        socket->write((char*)&data,sizeof(data));




    }

}

void Register::on_btn_login_clicked()
{
    this->close();
}

void Register::on_btn_verification_clicked()
{
    // 判断是否是空
    QString phonenumber = ui->le_phonenumber->text();
    if(phonenumber.isEmpty())
    {
        QMessageBox::critical(this,"QQ注册","请输入手机号");
    }
    else
    {
        //从服务端获取验证码
    }
}
