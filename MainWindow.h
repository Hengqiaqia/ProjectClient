#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>
#include "User.h"
#include <QTcpSocket>
#include "packet.h"
#include <QKeyEvent>
#include <QTextCodec>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QTcpSocket* socket,Packet data,QWidget *parent = 0);
    ~MainWindow();
     void on_SignalAllUser();// 接收所有人的数据
    void showLayout(int);//显示单个
protected:
    bool eventFilter(QObject *obj, QEvent *e);  //安装
signals:
//void SignalAllUser(Packet);
private slots:

    void on_btn_face_clicked();

    void on_btn_screanshot_clicked();

    void on_btn_sendfile_clicked();

    void on_btn_voice_clicked();

    void on_btn_video_clicked();

    void on_btn_search_clicked();

    void on_lv_personnumber_clicked(const QModelIndex &index);


    void on_lv_history_clicked(const QModelIndex &index);

    void on_btn_addroom_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *standardItemModel;
    QTcpSocket* socket;
    Packet data;
    QList<User> userlist ;//所有用户的数据



};

#endif // MAINWINDOW_H
