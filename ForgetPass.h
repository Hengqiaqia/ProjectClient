#ifndef FORGETPASS_H
#define FORGETPASS_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include "Utils.h"
#include "ClickableLabel.h"


namespace Ui {
class ForgetPass;
}

class ForgetPass : public QWidget
{
    Q_OBJECT

public:
    explicit ForgetPass(QWidget *parent = 0);
    ~ForgetPass();

signals:

private slots:
    void on_btn_phoneverification_clicked();

    void on_btn_resetpass_clicked();
    //超时 限制
    void on_btn_verification_clicked();

private:
    Ui::ForgetPass *ui;
    QTimer m_timer;
    QString m_captcha;
    Qt::GlobalColor* m_color;
    Utils utils;
protected:
    void paintEvent(QPaintEvent* evt);

};

#endif // FORGETPASS_H
