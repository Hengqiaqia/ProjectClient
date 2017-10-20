#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QMessageBox>
#include <QTcpSocket>
#include "packet.h"
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QTcpSocket* scoket,QWidget *parent = 0);
    ~Register();

private slots:
    void on_btn_register_clicked();

    void on_btn_login_clicked();

    void on_btn_verification_clicked();

private:
    Ui::Register *ui;
    QTcpSocket * socket;
};

#endif // REGISTER_H
