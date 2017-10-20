#include "ForgetPass.h"
#include "ui_ForgetPass.h"
#include <QPainter>
#include <QTime>
#include <QMessageBox>
ForgetPass::ForgetPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgetPass)
{
    ui->setupUi(this);
    //登录按钮的鼠标划过事件
    ui->btn_resetpass->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/login_a.jpg);color: rgb(255, 255, 255);font: 75 18pt 'Hannotate SC';}"
                                     "QPushButton:hover{border-image: url(:/new/prefix1/login_b.jpg);}"
                                     "QPushButton:pressed{border-image: url(:/new/prefix1/login_c.jpg);}");
    //注册按钮
    ui->btn_phoneverification->setStyleSheet("QPushButton{color: rgb(0, 0, 255);font: 75 16pt 'Hannotate SC';}"
                                             "QPushButton:hover{color: rgb(32, 32, 251);}"
                                             "QPushButton:pressed{color: rgb(52, 52, 231);}");
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
    //比较相同
    if(utils.lineEditStr(m_captcha, ui->le_verificaition))
    {
        qDebug()<<"根据手机号 验证码正确";
    }else{
        qDebug()<<"根据手机号 验证码凑庑";
    }
}
//重置密码
void ForgetPass::on_btn_resetpass_clicked()
{
    //比较相同
    if(utils.lineEditStr(m_captcha, ui->le_verificaition))
    {
        qDebug()<<"重置密码 验证码正确";
    }else{
        qDebug()<<"重置密码 验证码凑庑";
    }
}


void ForgetPass::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    //第一个参数 左右，第二个参数 上下 越小向上，
    painter.fillRect(180, 90, 84, 30, Qt::white);
      painter.setFont(QFont("75 16pt Comic Sans MS"));
    for(int i = 0; i < 100; i++)
    {
        painter.setPen(m_color[i % 4]);
        painter.drawPoint(180 + (qrand() % 84), 90 + (qrand() % 30));
    }
    for(int i = 0; i < 4; i++)
    {
        painter.setPen(m_color[i]);
        QFont font;
        font.setPixelSize(22);
        painter.setFont(font);
        painter.drawText(180 + 20 * i, 90, 20, 30, Qt::AlignCenter, QString(m_captcha[i]));
    }


}

//点击更换 验证码
void ForgetPass::on_btn_verification_clicked()
{
    m_color = utils.getColor();
    m_captcha = utils.getCaptcha();
    update();
}
