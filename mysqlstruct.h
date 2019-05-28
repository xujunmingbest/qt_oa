#ifndef MYSQLSTRUCT_H
#define MYSQLSTRUCT_H

#include <QString>

struct S_AddLiuShuiZhang{
    QString date; //格式 2019/05/30
    QString KuangXiangType; //款项类别
    QString KuangXiangName; //款项名称
    double money;
    double moneyRemain;
    QString BeiZhu;
    QString Status; //状态
    QString bookKeeper; //记账员
    QString chargeName; //主管名字
    QString proof; //凭证
};



#endif // MYSQLSTRUCT_H
