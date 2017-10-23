#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "Register.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <string.h>
#include "packet.h"
#include <QMovie>
#include "MainWindow.h"
#include <QKeyEvent>
#include "Utils.h"
#include "ForgetPass.h"
#include "UpdatePasswd.h"
#include "LiveStreamList.h"
#include "userpacket.h"


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
signals:
    void sendverification(QString);
private slots:
    void on_btn_register_clicked();

    void onError(QAbstractSocket::SocketError socketError);

    void onReadRead();
    void on_btn_login_clicked();

    void on_btn_forgetpass_clicked();

    void on_cb_remeberpw_stateChanged(int);

    void on_cb_autologin_stateChanged(int);

    void keyPressEvent(QKeyEvent * event);

    void onSigReg(user_t user);//注册
    void onSigLogin(user_t user);//登录

private:
    Ui::LoginWindow *ui;
    Register* reg;// 注册页面
    QTcpSocket* socket;
    MainWindow* mainwindow;//登录成功主页面
    Utils* utils;
    int loginnumber;
    ForgetPass* forgetpass;//忘记密码页面
    UpdatePasswd* updatepasswd;

    LiveStreamList *liveStreamList;
    ClientSocket *cs;
    QMessageBox box;
};

#endif // LOGINWINDOW_H
