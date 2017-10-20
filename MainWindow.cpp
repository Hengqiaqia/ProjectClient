#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QHostAddress>
#include <QMessageBox>
#include <string.h>
#include <QDebug>
#include <vector>
using namespace std;
MainWindow::MainWindow(QTcpSocket* socket,Packet data,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),socket(socket),data(data)
{
    ui->setupUi(this);

    // 此处用线程 单独去单个单个的循环出来
    on_SignalAllUser();//查询用户列表
    //右侧显示成员
    QString personnumber = "成员1/"+QString::number(userlist.size());
    ui->lable_personnumber->setText(personnumber);
    //进入欢迎界面
    showLayout(3);
    QString username(data.username);
    ui->label_welcome->setText(username+"欢迎使用聊天系统");
    ui->label_welcome->setAlignment(Qt::AlignCenter);

    //监听 发送框
    ui->te_sendcontent->installEventFilter(this);
    ui->te_singalsendcontent->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




//发送表情
void MainWindow::on_btn_face_clicked()
{

}
// 发送截图
void MainWindow::on_btn_screanshot_clicked()
{

}
// 发送文件
void MainWindow::on_btn_sendfile_clicked()
{

}
//语音
void MainWindow::on_btn_voice_clicked()
{

}
//视频
void MainWindow::on_btn_video_clicked()
{

}
//搜索联系人
void MainWindow::on_btn_search_clicked()
{
    ui->le_serachpn->show();
    ui->lable_personnumber->hide();
    ui->le_serachpn->setPlaceholderText("搜索...");
}

//接收信号
void MainWindow::on_SignalAllUser()
{
    qDebug()<<"接收所有人数据";
    QString nickname(data.nickname);
    QString username(data.username);
    QString passwd(data.passwd);
    QString phonenumber(data.phonenumber);
    User user(nickname, passwd, phonenumber, username);
    user.printlf();
    userlist.append(user);
    if(userlist.size()>0){
        standardItemModel = new QStandardItemModel(this);
        for(int i=0;i<userlist.size();i++)
        {
            QString string = static_cast<QString>(userlist.at(i).getNickname());
            QStandardItem *item = new QStandardItem(string);
            standardItemModel->appendRow(item);
        }
        ui->lv_personnumber->setModel(standardItemModel);
        //临时列表
        ui->lv_history->setModel(standardItemModel);
    }else{
        data.type = TYPE_SELALL;
        socket->write((char*)&data,sizeof(data));
    }
}
//在线联系人列表
void MainWindow::on_lv_personnumber_clicked(const QModelIndex &index)
{
    ui->le_serachpn->hide();
    qDebug() << "单机了这个"<<index.data().toString();
    ui->chatName->setText(index.data().toString());
    showLayout(1);
}
//历史聊天联系人
void MainWindow::on_lv_history_clicked(const QModelIndex &index)
{
    qDebug() << "左侧这个"<<index.data().toString();
    ui->chatName->setText(index.data().toString());
    showLayout(2);//根据单击的进行判断
}
//显示布局
void MainWindow::showLayout(int flag)
{
    if(flag == 1)//单聊
    {
        ui->chatName->show();
        ui->btn_face->show();
        ui->btn_screanshot->show();
        ui->btn_search->show();
        ui->btn_sendfile->show();
        ui->btn_video->show();
        ui->btn_voice->show();

        ui->lw_singlerescord->show();
        ui->te_singalsendcontent->show();

        ui->label_notity->hide();
        ui->lable_personnumber->hide();
        ui->le_serachpn->hide();
        ui->lv_chatrecord->hide();
        ui->lv_personnumber->hide();
        ui->te_sendcontent->hide();
        ui->label_welcome->hide();
    }
    else if(flag == 2)//群聊
    {
        ui->chatName->show();
        ui->btn_face->show();
        ui->btn_screanshot->show();
        ui->btn_search->show();
        ui->btn_sendfile->show();
        ui->btn_video->show();
        ui->btn_voice->show();

        ui->lw_singlerescord->hide();
        ui->te_singalsendcontent->hide();

        ui->label_notity->show();
        ui->lable_personnumber->show();
        ui->lv_chatrecord->show();
        ui->lv_personnumber->show();
        ui->te_sendcontent->show();
        ui->label_welcome->hide();
    }
    else if(flag == 3)// 欢迎界面
    {

        ui->chatName->hide();
        ui->btn_face->hide();
        ui->btn_screanshot->hide();
        ui->btn_search->hide();
        ui->btn_sendfile->hide();
        ui->btn_video->hide();
        ui->btn_voice->hide();

        ui->lw_singlerescord->hide();
        ui->te_singalsendcontent->hide();

        ui->label_notity->hide();
        ui->lable_personnumber->hide();
        //在线联系人 搜索 隐藏
        ui->le_serachpn->hide();
        ui->lv_chatrecord->hide();
        ui->lv_personnumber->hide();
        ui->te_sendcontent->hide();
        ui->label_welcome->show();
    }

}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    Q_ASSERT(obj == ui->te_sendcontent||obj==ui->te_singalsendcontent);
     QString   sendcontent = "";
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *event = static_cast<QKeyEvent*>(e);
        //            此处根据选项 进行判断
        if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
        {
            // sendMsg(); //发送消息的槽

            if(obj==ui->te_sendcontent)
            {
                ui->te_sendcontent->append("\n");
                qDebug()<<"enter back line 198";
            }
            if(obj==ui->te_singalsendcontent)
            {
                ui->te_singalsendcontent->append("\n");
                qDebug()<<"enter back line 203";
            }
            return true;
        }
        else if(event->key() == Qt::Key_Return)
        {
            if(obj==ui->te_singalsendcontent)
            {
                    sendcontent = ui->te_singalsendcontent->toPlainText();
                qDebug()<<"单聊："<<sendcontent;
                ui->te_singalsendcontent->clear();
            }
            if(obj==ui->te_sendcontent)
            {
                   sendcontent = ui->te_sendcontent->toPlainText();
                qDebug()<<"群聊："<<sendcontent;
                ui->te_sendcontent->clear();
            }
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, e);
}
