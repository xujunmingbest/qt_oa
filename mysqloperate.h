#ifndef MYSQLOPERATE_H
#define MYSQLOPERATE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>


#include "mysqlstruct.h"

class MysqlOperate
{
public:
    MysqlOperate();
    static bool MysqlOpen();  //数据库打开连接
    static bool UserLogin(QString name,QString password);  //用户登入
    static QSqlDatabase defaultDB;

    static QJsonObject GetAuth();
    static bool AddLiuShuiZhang(S_AddLiuShuiZhang &data);
    static bool UpdateLiuShuiZhang(int id,S_AddLiuShuiZhang &data);
    static QStringList GetAllJZY();
    static QStringList GetAllZG();
    static bool UpdatePassword(QString NewPassword);
    static bool AddJZY(QString Name,QString Password,QString chargeName); //添加记账员
    static bool AddZG(QString Name,QString Password); //添加主管
    static bool RetSetPassword(int userId); //添加主管
    static bool DeleteUser(int userId); //删除用户

    static double MonthStaticSR(QString DateMonth,QString ChargeName);
    static double MonthStaticZC(QString DateMonth,QString ChargeName);
    static double GetMoneyRemain();
};


extern QString g_Name; //登入名字
extern QString g_Auth;
extern QString g_ChargeName;

#define SS(str) QString::fromLocal8Bit(str)
#define MAX(x,y) (x)>(y)?(x):(y)
#define MIN(x,y) (x)>(y)?(y):(x)
#endif // MYSQLOPERATE_H
