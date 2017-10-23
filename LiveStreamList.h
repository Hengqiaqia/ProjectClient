#ifndef LIVESTREAMLIST_H
#define LIVESTREAMLIST_H

#include <QDialog>
#include <QWidget>
#include <QDialog>
#include"user.h"
#include<QTcpSocket>
#include"ClientSocket.h"
#include<QCloseEvent>
#include"LiveStream.h"
#include<QListWidgetItem>
namespace Ui {
class LiveStreamList;
}

class LiveStreamList : public QDialog
{
    Q_OBJECT

public:
    explicit LiveStreamList(ClientSocket *cs,  QTcpSocket *socket, user_t user, QWidget *parent = 0);
    ~LiveStreamList();
    void showRoomName();    //刚进入二级界面时通知服务器
protected:
    void closeEvent (QCloseEvent *); //关闭客户端
signals:
private slots:
    void onsigRoomName(user_t user);//刚进入二级界面添加到的聊天室列表
    void on_chatroom_itemDoubleClicked(QListWidgetItem *item);//双击进入聊天室

    void on_destory_clicked();//切换用户

    void on_exit_btn_clicked();//退出客户端

    void on_roomlist_btn_clicked();//刷新按钮
    void onsigRoomList(user_t user);//显示房间列表

private:
    Ui::LiveStreamList *ui;
    user_t user;
    QTcpSocket *socket;
    ClientSocket *cs;
    LiveStream *chatroom;

};

#endif // LIVESTREAMLIST_H
