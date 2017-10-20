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

private slots:
    void on_btn_register_clicked();

    void onError(QAbstractSocket::SocketError socketError);

    void onReadRead();
    void on_btn_login_clicked();

    void on_btn_forgetpass_clicked();

    void on_cb_remeberpw_stateChanged(int);

    void on_cb_autologin_stateChanged(int);

    void keyPressEvent(QKeyEvent * event);
private:
    Ui::LoginWindow *ui;
    Register* reg;
    QTcpSocket* socket;
    MainWindow* mainwindow;
    Utils* utils;
    int loginnumber;
};

#endif // LOGINWINDOW_H
