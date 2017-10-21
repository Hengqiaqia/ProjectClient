#include "ForgetPass.h"
#include "ui_ForgetPass.h"
#include <QPainter>
#include <QTime>
#include <QMessageBox>
ForgetPass::ForgetPass(QTcpSocket* socket, QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgetPass),socket(socket),username(username)
{
    ui->setupUi(this);
    //登录按钮的鼠标划过事件
    ui->btn_resetpass->setStyleSheet("QPushButton{background: transparent;border-image: url(:/new/prefix1/login_a.jpg);color: rgb(255, 255, 255);font: 75 18pt 'Hannotate SC';}"
                                     "QPushButton:hover{border-image: url(:/new/prefix1/login_b.jpg);}"
                                     "QPushButton:pressed{border-image: url(:/new/prefix1/login_c.jpg);}");
    //注册按钮
    ui->btn_phoneverification->setStyleSheet("QPushButton{background: transparent;color: rgb(36, 36, 234);font: 75 16pt 'Hannotate SC';}"
                                             "QPushButton:hover{color: rgb(13, 23, 183);}"
                                             "QPushButton:pressed{color: rgb(26, 30, 200);}");

    ui->btn_verification->setStyleSheet("QPushButton{background: transparent;}");

    ui->le_phonenumber->setPlaceholderText("请输入手机号");
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
    //图片验证码
    QRegExp regx("[a-zA-Z0-9]+$");
    QValidator *validatorver = new QRegExpValidator(regx, ui->le_verificaition );
    ui->le_verificaition->setValidator( validatorver );
    ui->le_verificaition->setMaxLength(4);
    //手机号验证码
    QRegExp regxnumberver("[0-9]+$");
    QValidator *validatornumberver = new QRegExpValidator(regxnumberver, ui->le_phoneverification );
    ui->le_phoneverification->setValidator( validatornumberver );
    ui->le_phoneverification->setMaxLength(4);
    //connect(m_timer, SIGNAL(timeout()), this, SLOT(Timer_Timeout()));

    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    m_captcha = utils.getCaptcha();
    m_color = utils.getColor();
    //    m_timer.start(200);


}

ForgetPass::~ForgetPass()
{
    delete ui;
}
//根据手机号获取验证码
void ForgetPass::on_btn_phoneverification_clicked()
{
    QString userName = ui->le_username->text();//获取当前页面的账号
    //判断获取账号  前面传过来数据，当前页面没有数据  用前面的 否则用当前页面的
    if(!username.isEmpty()&&userName.isEmpty())
    {
        userName=username;
    }
    if(ui->le_phonenumber->text().isEmpty())
    {
        QMessageBox::critical(this,"重置密码","请输入手机号码");
    }else if(username.isEmpty()&&userName.isEmpty())
    {
        QMessageBox::critical(this,"重置密码","请输入账号");
    }else{
        //比较相同
        if(utils.lineEditStr(m_captcha, ui->le_verificaition))
        {
            qDebug()<<"根据手机号 验证码正确："<<m_captcha;
            //发送信号 提示服务端生成验证码
            Packet data;
            strcpy(data.username,userName.toStdString().data());
            strcpy(data.phonenumber,ui->le_phonenumber->text().toStdString().data());
            data.type = TYPE_SEND_VER;
            socket->write((char*)&data,sizeof(data));


        }else if(ui->le_verificaition->text().isEmpty()){
            QMessageBox::critical(this,"重置密码","请输入图片中的验证码");
        }else{
            QMessageBox::critical(this,"重置密码","输入图片中的验证码错误");
        }
    }
}
//重置密码
void ForgetPass::on_btn_resetpass_clicked()
{
    QString userName = ui->le_username->text();//获取当前页面的账号
    //判断获取账号  前面传过来数据，当前页面没有数据  用前面的 否则用当前页面的
    if(!username.isEmpty()&&userName.isEmpty())
    {
        userName=username;
    }

    if(ui->le_phonenumber->text().isEmpty())
    {
        QMessageBox::critical(this,"重置密码","请输入手机号码");
    }else{
        //比较相同
        if(utils.lineEditStr(m_captcha, ui->le_verificaition))
        {
            qDebug()<<"重置密码 图片验证码正确";
            if(utils.lineEditStr(phoneverification,ui->le_phoneverification))
            {
                qDebug()<<"进入修改密码界面";
                Packet data;
                strcpy(data.username,userName.toStdString().data());
                strcpy(data.phonenumber,ui->le_phonenumber->text().toStdString().data());
                uppasswd=new UpdatePasswd(socket,data);
                uppasswd->show();

            }else if(ui->le_verificaition->text().isEmpty()){
                QMessageBox::critical(this,"重置密码","请输入收到的验证码");
            }else{
                QMessageBox::critical(this,"重置密码",phoneverification);
            }
        }else if(ui->le_verificaition->text().isEmpty()){
            QMessageBox::critical(this,"重置密码","请输入图片中的验证码");
        }else{
            QMessageBox::critical(this,"重置密码","输入图片中的验证码错误");
        }
    }
}


void ForgetPass::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    //第一个参数 左右，第二个参数 上下 越小向上，
    painter.fillRect(180, 130, 84, 30, Qt::white);
    painter.setFont(QFont("75 16pt Comic Sans MS"));
    for(int i = 0; i < 100; i++)
    {
        painter.setPen(m_color[i % 4]);
        painter.drawPoint(180 + (qrand() % 84), 130 + (qrand() % 30));
    }
    for(int i = 0; i < 4; i++)
    {
        painter.setPen(m_color[i]);
        QFont font;
        font.setPixelSize(22);
        painter.setFont(font);
        painter.drawText(180 + 20 * i, 130, 20, 30, Qt::AlignCenter, QString(m_captcha[i]));
    }


}

//点击更换 验证码
void ForgetPass::on_btn_verification_clicked()
{
    m_color = utils.getColor();
    m_captcha = utils.getCaptcha();
    update();
}
//接收到验证码数据 响应
void ForgetPass::on_sendverification(QString verificaiton)
{
    phoneverification = verificaiton;
    if(verificaiton.size()==4)
    {
        ui->le_phoneverification->setText(verificaiton);
    }else{
        QMessageBox::critical(this,"重置密码",verificaiton);
    }
}
