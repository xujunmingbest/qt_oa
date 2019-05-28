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
    static bool MysqlOpen();  //���ݿ������
    static bool UserLogin(QString name,QString password);  //�û�����
    static QSqlDatabase defaultDB;

    static QJsonObject GetAuth();
    static bool AddLiuShuiZhang(S_AddLiuShuiZhang &data);
    static bool UpdateLiuShuiZhang(int id,S_AddLiuShuiZhang &data);
    static QStringList GetAllJZY();
    static QStringList GetAllZG();
    static bool UpdatePassword(QString NewPassword);
    static bool AddJZY(QString Name,QString Password,QString chargeName); //��Ӽ���Ա
    static bool AddZG(QString Name,QString Password); //�������
    static bool RetSetPassword(int userId); //�������
    static bool DeleteUser(int userId); //ɾ���û�

    static double MonthStaticSR(QString DateMonth,QString ChargeName);
    static double MonthStaticZC(QString DateMonth,QString ChargeName);
    static double GetMoneyRemain();
};


extern QString g_Name; //��������
extern QString g_Auth;
extern QString g_ChargeName;

#define SS(str) QString::fromLocal8Bit(str)
#define MAX(x,y) (x)>(y)?(x):(y)
#define MIN(x,y) (x)>(y)?(y):(x)
#endif // MYSQLOPERATE_H
