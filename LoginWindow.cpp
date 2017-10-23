#include "LoginWindow.h"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    //头像
    ui->label_imge->setScaledContents(true);
    ui->label_imge->resize(60,60);
    QMovie *movie = new QMovie(":/new/prefix1/login_head.gif");
    ui->label_imge->setMovie(movie);
    movie->start();

    //登录按钮的鼠标划过事件
    ui->btn_login->setStyleSheet("QPushButton{background: transparent;border-image: url(:/new/prefix1/login_a.jpg);color: rgb(255, 255, 255);font: 75 18pt 'Hannotate SC';}"
                                 "QPushButton:hover{border-image: url(:/new/prefix1/login_b.jpg);}"
                                 "QPushButton:pressed{border-image: url(:/new/prefix1/login_c.jpg);}");
    //注册按钮
    ui->btn_register->setStyleSheet("QPushButton{background: transparent;color: rgb(0, 0, 255);font: 75 16pt 'Hannotate SC';}"
                                    "QPushButton:hover{color: rgb(32, 32, 251);}"
                                    "QPushButton:pressed{color: rgb(52, 52, 231);}");
    //忘记密码
    ui->btn_forgetpass->setStyleSheet("QPushButton{background: transparent;color: rgb(36, 36, 247);font: 75 16pt 'Hannotate SC';}"
                                      "QPushButton:hover{color: rgb(34, 34, 229);}"
                                      "QPushButton:pressed{color: rgb(46, 46, 244);}");

    ui->le_username->setPlaceholderText("请输入账号(数字)");
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx,  ui->le_username );
    ui->le_username->setValidator( validator );
    ui->le_username->setMaxLength(10);
    ui->le_passwd->setPlaceholderText("请输入密码");
    //密码，一般是用小黑点覆盖你所输入的字符
    ui->le_passwd->setEchoMode(QLineEdit::Password);

    socket = new QTcpSocket(this);
    //    QObject::connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
    //                     this,SLOT(onError(QAbstractSocket::SocketError)));
    //    QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(onReadRead()));
    //    socket->connectToHost(QHostAddress::Any,8888);

    qRegisterMetaType<user_t>("user_t");        //向Qt注册user_t结构体

    cs = new ClientSocket(socket);
    QThread *th = new QThread();

    //连接断开时删除子线程的内存
    connect(socket, SIGNAL(disconnected()),
            cs, SLOT(deleteLater()));
    //连接断开时结束子线程
    connect(socket, SIGNAL(disconnected()),
            th, SLOT(quit()));
    //接收到子线程返回的注册信息
    connect(cs,SIGNAL(sigReg(user_t)),
            this, SLOT(onSigReg(user_t)));
    //接收到子线程返回的登录信息
    connect(cs, SIGNAL(sigLogin(user_t)),
            this, SLOT(onSigLogin(user_t)));

    cs->moveToThread(th);   //客户端创建线程，在子线程执行读操作
    th->start();

    //    QHostAddress addr("192.168.1.103");
    //    socket->connectToHost(addr, 8888);
    socket->connectToHost(QHostAddress::LocalHost, 8888);

    User user =  utils->read();
    if(!user.getUsername().isEmpty())
    {
        ui->le_username->setText(user.getUsername());
        if(!user.getPasswd().isEmpty())
        {
            ui->le_passwd->setText(user.getPasswd());
        }
    }else
    {
        ui->le_username->setText("");
        ui->le_passwd->setText( "");
    }

}

LoginWindow::~LoginWindow()
{
    delete ui;
}
void LoginWindow::onError(QAbstractSocket::SocketError socketError)
{
    qDebug()<<"端口错误";
    QMessageBox::critical(this,"警告","服务器关闭");

}


// 进入注册界面
void LoginWindow::on_btn_register_clicked()
{
    reg = new Register(socket);
    reg->show();
}

void LoginWindow::on_btn_login_clicked()
{
    QString username = ui->le_username->text() ;
    QString passwd = ui->le_passwd->text() ;
    if(username.size()==0||passwd.size()==0)
    {
        QMessageBox::critical(this,"QQ登录","用户名或密码不能为空");
    }
    else
    {

        user_t user;
        memset(&user, 0, sizeof(user_t));
        ui->le_username->clear();
        char* pname = username.toLocal8Bit().data();
        strncpy(user.username, pname, 20);

        ui->le_passwd->clear();
        char* ppasswd = passwd.toLocal8Bit().data();
        strncpy(user.userpasswd,ppasswd,20);

        user.type = LOGIN;
        socket->write((char*)&user, sizeof(user));
#if  0
        // 进入连接服务器 进入显示判断
        Packet data;
        strcpy(data.username,username.toStdString().data());
        strcpy(data.passwd,passwd.toStdString().data());
        data.type = TYPE_LOGIN;
        socket->write((char*)&data,sizeof(data));
#endif
    }


}

//接收回来的信息
void LoginWindow::onReadRead()
{
    bool autologinflag =ui->cb_autologin->isChecked() ;
    bool remepassflag = ui->cb_remeberpw->isChecked();
    Packet data;
    user_t user;

    socket->read((char*)&data,sizeof(data));
    QString username(data.username);
    qDebug()<<"data.msg:"<<data.msg;
    switch (data.type) {
    case TYPE_LOGIN:

        break;
    case  TYPE_LOGIN_ERROR:
        QMessageBox::critical(this,"QQ登录",data.msg);
        break;
    case  TYPE_LOGIN_SUCCESS:
        //登录成功查询所有数据，将type 改为查询 查询成功跳转
        qDebug()<<username<<":登录 成功";
        data.type = TYPE_SELALL;
        socket->write((char*)&data,sizeof(data));
        break;
    case TYPE_REG_SUCCESS:
        qDebug()<<"注册 成功"<<username;
        QMessageBox::information(this,"QQ注册","注册成功\n记住此用户名:"+username);
        break;
    case TYPE_REG_ERROR:
        QMessageBox::critical(this,"QQ注册","注册失败"+QString(data.msg));
        break;
    case TYPE_SELALL_SUCCESS:
        this->close();
#if 1
        //此页面仿QQ
        mainwindow = new MainWindow(socket,data);
        mainwindow->show();
#endif
        qDebug()<<username<<":登录 成功跳转页面";
        //如果选中自动登录或者记住密码 保存数据到文件中
        if(autologinflag||remepassflag)
        {
            utils->write(0,utils->groupjson(ui->le_username->text(),ui->le_passwd->text()));
        }else{
            utils->write(0,utils->groupjson(ui->le_username->text(),""));
        }

        break;
    case TYPE_SELALL_ERROR:
        qDebug()<<username<<":登录失败";
        QMessageBox::information(this,"QQ登录","登录失败\n"+QString(data.msg));
        break;
    case TYPE_SEND_VERSUCSS:case TYPE_SEND_VERERROR:

        emit sendverification(QString(data.msg));
        qDebug()<<"获取手机验证码:"<<QString(data.msg);
        break;
    case TYPE_UPDATE_SUCCESS:

        //         updatepasswd = new UpdatePasswd(socket,data);
        //         updatepasswd->close();
        //         forgetpass = new ForgetPass(socket,"");
        //         forgetpass->close();
        QMessageBox::information(this,"修改密码","修改成功，点击确认");
        //修改密码
        ui->le_username->setText(QString(data.username));
        ui->le_passwd->setText("");
        break;
    case TYPE_UPDATE_ERROR:
        QMessageBox::critical(this,"修改密码","修改失败"+QString(data.msg));
        break;
    default:
        break;
    }

}
// 忘记密码
void LoginWindow::on_btn_forgetpass_clicked()
{
    //this->close();
    forgetpass = new ForgetPass(socket,ui->le_username->text());
    forgetpass->show();
    connect(this,SIGNAL(sendverification(QString)),
            forgetpass,SLOT(on_sendverification(QString)));
}
//记住密码
void LoginWindow::on_cb_remeberpw_stateChanged(int state)
{
    if (state == Qt::Checked) // "选中"
    {
        qDebug()<<"记住密码";
    }
    //        else if(state == Qt::PartiallyChecked) // "半选"
    //        {
    //            m_pLabel->setText("PartiallyChecked");
    //        }
    else // 未选中 - Qt::Unchecked
    {
        bool autologinflag =ui->cb_autologin->isChecked() ;
        qDebug()<<"autologinflag:"<<autologinflag;
        if(autologinflag)
        {
            ui->cb_autologin->setCheckState(Qt::Unchecked);
        }
        qDebug()<<"不记住密码";
    }
}

void LoginWindow::on_cb_autologin_stateChanged(int state)
{
    if (state == Qt::Checked) // "选中"
    {
        ui->cb_remeberpw->setCheckState(Qt::Checked);
        qDebug()<<"自动登录";
    }
    else // 未选中 - Qt::Unchecked
    {
        qDebug()<<"不自动登录";
    }
}
//整体的界面   回车按键
void LoginWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Return)
    {
        on_btn_login_clicked();
    }
}
/*
函数功能：注册
参数：user_t user
返回值：无
*/
void LoginWindow::onSigReg(user_t user)
{
    QString text = user.data;
    if(text != "注册成功"){
        box.warning(this, "警告", text);
    }
    else{
        box.information(this, "提示", text);
    }
}


/*
函数功能：登录
参数：user_t user
返回值：无
*/
void LoginWindow::onSigLogin(user_t user)
{
    bool autologinflag =ui->cb_autologin->isChecked() ;
    bool remepassflag = ui->cb_remeberpw->isChecked();

    QString text = user.data;
    qDebug()<<"登录："<<text;
    if(text != "登陆成功"){
        box.warning(this, "警告", text);
    }
    else{
        this->close();
        QString strtitle;
        liveStreamList = new LiveStreamList(cs, socket, user, this);
        strtitle= QString::fromLocal8Bit (user.username);
        strtitle += ", 欢迎来到悦播";
        liveStreamList->setWindowTitle (strtitle);
        liveStreamList->move (1000,60);
        liveStreamList->show();
        if(autologinflag||remepassflag)
        {
            utils->write(0,utils->groupjson(ui->le_username->text(),ui->le_passwd->text()));
        }else{
            utils->write(0,utils->groupjson(ui->le_username->text(),""));
        }
    }
}
