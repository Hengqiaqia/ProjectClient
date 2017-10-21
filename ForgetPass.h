#ifndef FORGETPASS_H
#define FORGETPASS_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include "Utils.h"
#include "ClickableLabel.h"
#include "packet.h"
#include <QTcpSocket>

namespace Ui {
class ForgetPass;
}

class ForgetPass : public QWidget
{
    Q_OBJECT

public:
    explicit ForgetPass(QTcpSocket* scoket,QString username="",QWidget *parent = 0);
    ~ForgetPass();

signals:

private slots:
    void on_btn_phoneverification_clicked();

    void on_btn_resetpass_clicked();
    //超时 限制
    void on_btn_verification_clicked();

    void on_sendverification(QString);
private:
    Ui::ForgetPass *ui;
    QTimer m_timer;
    QString m_captcha;//图片验证码
    Qt::GlobalColor* m_color;
    Utils utils;
    QString phoneverification;//收到的验证码

    QTcpSocket* socket;
    QString username;

protected:
    void paintEvent(QPaintEvent* evt);

};

#endif // FORGETPASS_H
