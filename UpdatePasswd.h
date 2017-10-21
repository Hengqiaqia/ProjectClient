#ifndef UPDATEPASSWD_H
#define UPDATEPASSWD_H

#include <QWidget>
#include <QTcpSocket>
#include "packet.h"
#include <QMessageBox>
namespace Ui {
class UpdatePasswd;
}

class UpdatePasswd : public QWidget
{
    Q_OBJECT

public:
    explicit UpdatePasswd(QTcpSocket* socket,Packet data,QWidget *parent = 0);
    ~UpdatePasswd();

private slots:
    void on_btn_update_clicked();

private:
    Ui::UpdatePasswd *ui;
    QTcpSocket* socket;
    Packet data;

};

#endif // UPDATEPASSWD_H
