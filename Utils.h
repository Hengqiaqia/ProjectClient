#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFileInfo>
#include "User.h"
class Utils
{
public:
    Utils();
    QString groupjson(QString username,QString passwd);//将数据组合为json串
    QString savejson(int key,QString context);//存储传递过来的数据
    User  analysis(QString context);//解析传递过来的数据
   void  write(int username,QString context);
   User  read();
   QString jsonObjecstr;//json 第一层串
};

#endif // UTILS_H
