#include "Utils.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QJsonParseError>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonDocument>
#include <vector>
#include <QJsonArray>

using namespace std;
Utils::Utils()
{

}

QString Utils::groupjson(QString username, QString passwd)
{
    QJsonObject json;
    json.insert("username", username);
    json.insert("passwd", passwd);

    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    qDebug()<<"utils line 29 :json_str:"<<byte_array;
    return  json_str;
}

QString Utils::savejson(int n,QString context)
{
    QJsonArray json;
    json.insert(n,context);
    QJsonDocument document;
    document.setArray(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    qDebug()<<"utils line 44:savejson:"<<json_str;
    return json_str;
}
//解析
User Utils::analysis(QString context)
{
    vector<User> users;
    vector<User>::iterator it;
    User userback;
    QByteArray byte_array = context.toLatin1();
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isArray())
        {
            QJsonArray array = parse_doucment.array();
            int size = array.size();
            for(int i=0; i<size;i++)
            {
                User user;
                QJsonValue value = array.at(i);
                if(value.isString())
                {
                    QString jsonstr = value.toString();
                    QByteArray bytearr = jsonstr.toLatin1();
                    QJsonParseError json_error;
                    QJsonDocument parse_doucment = QJsonDocument::fromJson(bytearr, &json_error);
                    if(json_error.error == QJsonParseError::NoError)
                    {
                        if(parse_doucment.isObject())
                        {
                            QJsonObject obj = parse_doucment.object();
                            if(obj.contains("username"))
                            {
                                QJsonValue name_value = obj.take("username");
                                if(name_value.isString())
                                {
                                    QString name = name_value.toString();
                                    user.setUserName(name);
                                }
                            }
                            if(obj.contains("passwd"))
                            {
                                QJsonValue passwd_value = obj.take("passwd");
                                if(passwd_value.isString())
                                {
                                    QString passwd = passwd_value.toString();
                                    user.setPasswd(passwd);
                                }
                            }
                        }
                    }
                }
                users.push_back(user);
            }
        }
    }

    for(it=users.begin();it!=users.end();it++)
    {
        //传递过来的字符串 包含 用户名
        if(context.contains(it->getUsername()))
        {
            userback.setUserName(it->getUsername());
            //如果包含用户名，是否包含密码
            if(context.contains(it->getPasswd()))
            {
                userback.setPasswd(it->getPasswd());
            }
        }
    }
    return userback;
}
void Utils::write(int n,QString context)
{
    QString file_name = "/Users/Cary/Documents/Qt_workspace/ProjectClient/userinfo.txt";
    //以传入的文件名建立一个文件，传入的文件名包含有目录信息在里面
    QFile file(file_name);
    //以只写和文本的方式打开该文件
    if(!file.open(QFile::ReadWrite | QFile::Text))
    {
        qDebug () << "Utils line 25:Could not open the file by reading";
        return;
    }
    //out其实是一个缓冲区
    QTextStream out(&file);
    QString text = savejson(n,context);
     qDebug()<<"128内容为："<<text;
    //输出内容到缓冲区
    out << text;
    qDebug()<<"内容为："<<savejson(n,context);
    file.flush();//将缓冲区的内容输出的文本
    file.close();//关闭文件

}

User Utils::read()
{
    User user ;
    QString file_name = "/Users/Cary/Documents/Qt_workspace/ProjectClient/userinfo.txt";
    QFile file(file_name);
    //以只读和文本的方式打开该文件
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug () << "uitls line 45:Could not open the file by reading";
        return user;
    }
    QTextStream in(&file);
    QString text;
    //in >> text;//如果是用这句的话则只是独到了1句而已，即内容hello
    text = in.readAll();//这也写可以全部读完
    user = analysis(text);
    qDebug () << "read:"<<text;

    file.close();//关闭文件
    return user;
}



