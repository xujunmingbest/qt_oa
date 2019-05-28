#include "mysqloperate.h"
#include "QMessageBox.h"
#include <QCryptographicHash>
QSqlDatabase MysqlOperate::defaultDB;



QString g_Name; //��������
QString g_Auth;
QString g_ChargeName;


MysqlOperate::MysqlOperate()
{


}


bool MysqlOperate::MysqlOpen(){
    defaultDB = QSqlDatabase::addDatabase("QMYSQL");
    {
        defaultDB.setDatabaseName( "userdata" );
        defaultDB.setUserName( "root" );
        defaultDB.setPassword( "123456" );
        defaultDB.setHostName( "127.0.0.1" );

        if ( defaultDB.open() ) {
            defaultDB.exec("SET NAMES 'gbk'");
            return true;
        }else{
              QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"), defaultDB.lastError().databaseText());
              return false;
        }
    }
}


bool MysqlOperate::UserLogin(QString name,QString password){
    QByteArray passwordmd5;
    passwordmd5 = QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5);

    QString sq=QStringLiteral("select * from user where username = '%1' and password = '%2'").arg(name,QString(passwordmd5.toHex()));
    qDebug() << sq;
    QSqlQuery query(sq);
    if( query.isActive()){
        while(query.next()){
            g_Auth = query.value(1).toString();
            g_ChargeName = query.value(2).toString();
            g_Name = query.value(3).toString();
            qDebug() << g_Auth;
            qDebug() << g_ChargeName;
            qDebug() << g_Name;
            return true;
        }
    }
    return false;
}

#include <QJsonObject>
#include <QJsonDocument>
QJsonObject MysqlOperate::GetAuth(){
    QJsonObject jo;
            QString AuthType;

    {
        QString sq=QStringLiteral("select module from user_authority where role = '%1'").arg(g_Auth);
        qDebug() << sq;
        QSqlQuery query(sq);
        if( query.isActive()){
            while(query.next()){
               QString jsonString = query.value(0).toString();

                QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toStdString().data());
                if( jsonDocument.isNull() ){
                    qDebug()<< "===> please check the string "<< jsonString;
                }
                jo = jsonDocument.object();
               return jo;

            }
        }else{
            QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"),QString::fromLocal8Bit("Ȩ�޻�ȡʧ��"));
            return jo;
        }
    }

}



bool MysqlOperate::AddLiuShuiZhang(S_AddLiuShuiZhang &data){

    {
        QString sq=QStringLiteral("insert into liushuizhang ("
                                  "categoryType,categoryName,moneyAmount,moneyRemain,"
                                  "remark,bookkeeper,chargeName,status,"
                                  "rtime,proof) values("
                                  "'%1','%2',%3,%4,'%5','%6','%7','%8','%9','%10')")
                .arg(data.KuangXiangType).arg(data.KuangXiangName).arg(data.money).arg(data.moneyRemain).
                     arg(data.BeiZhu).arg(data.bookKeeper).arg(data.chargeName).arg(data.Status)
                .arg(data.date).arg(data.proof);
        qDebug() << sq;
        QSqlQuery query;
        query.exec(sq);
        if( query.isActive()){
            QMessageBox::about(NULL, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�����ˮ�˳ɹ�"));
            return true;
        }else{
            QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"), query.lastError().databaseText());
            QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("�����ˮ��ʧ��"));
            return false;
        }
    }

}

bool MysqlOperate::UpdateLiuShuiZhang(int id,S_AddLiuShuiZhang &data){
    {
        QString sq=QStringLiteral("update liushuizhang set "
                                  "categoryType = '%1',categoryName = '%2',moneyAmount = %3,moneyRemain = %4,"
                                  "remark= '%5',status= '%6',rtime= '%7' "
                                  " where id = %8")
                .arg(data.KuangXiangType).arg(data.KuangXiangName).arg(data.money).arg(data.moneyRemain).
                     arg(data.BeiZhu).arg(data.Status)
                .arg(data.date).arg(id);
        qDebug() << sq;
        QSqlQuery query;
        query.exec(sq);
        if( query.isActive()){
            QMessageBox::about(NULL, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޸���ˮ�˳ɹ�"));
            return true;
        }else{
            QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"), query.lastError().databaseText());
            QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("�����ˮ��ʧ��"));
            return false;
        }
    }

}

QStringList MysqlOperate::GetAllJZY(){
    QStringList sl;
    QString sq=QStringLiteral("select username from user where authtype = '%1'").arg(SS("����Ա"));
    qDebug()<< sq;
    QSqlQuery query(sq);
    if( query.isActive()){
        while(query.next()){
           QString NameString = query.value(0).toString();
           sl << NameString;
           qDebug()<< NameString;
        }
    }else{
        QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"),QString::fromLocal8Bit("����Ա��ȡʧ��"));
    }
    return sl;
}
QStringList MysqlOperate::GetAllZG(){
    QStringList sl;
    QString sq=QStringLiteral("select username from user where authtype = '%1'").arg(SS("����"));
    qDebug()<< sq;
    QSqlQuery query(sq);
    if( query.isActive()){
        while(query.next()){
           QString NameString = query.value(0).toString();
           sl << NameString;
           qDebug()<< NameString;
        }
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
        QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"),QString::fromLocal8Bit("���ܻ�ȡʧ��"));
    }
    return sl;

}
bool MysqlOperate::UpdatePassword(QString NewPassword){
    QByteArray passwordmd5;
    passwordmd5 = QCryptographicHash::hash(NewPassword.toLatin1(),QCryptographicHash::Md5);
    QString sq=QStringLiteral("update user set password = '%1' where username = '%2'").arg(QString(passwordmd5.toHex())).arg(g_Name);
    QSqlQuery query;
    query.exec(sq);
    if( query.isActive()){
        return true;
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
        QMessageBox::about(NULL, SS("������ʾ"), SS("�޸�����ʧ��"));
        return false;
    }
}


bool MysqlOperate::AddJZY(QString Name,QString Password,QString chargeName) //��Ӽ���Ա
{
    QByteArray passwordmd5;
    passwordmd5 = QCryptographicHash::hash(Password.toLatin1(),QCryptographicHash::Md5);
    QString pw = QString(passwordmd5.toHex());
    QString sq=QStringLiteral("insert into user(authType,ChargeName,username,password) values('����Ա','%1','%2','%3')")
            .arg(chargeName).arg(Name).arg(pw);
    QSqlQuery query;
    query.exec(sq);
    if( query.isActive()){
        return true;
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
        QMessageBox::about(NULL, SS("������ʾ"), SS("��Ӽ���Աʧ��"));
        return false;
    }
}

bool MysqlOperate::AddZG(QString Name,QString Password) //�������
{
    QByteArray passwordmd5;
    passwordmd5 = QCryptographicHash::hash(Password.toLatin1(),QCryptographicHash::Md5);
    QString pw = QString(passwordmd5.toHex());

    QString sq=QStringLiteral("insert into user(authType,ChargeName,username,password) values('����','-','%2','%3')")
            .arg(Name).arg(pw);
    QSqlQuery query;
    query.exec(sq);
    if( query.isActive()){
        return true;
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
        QMessageBox::about(NULL, SS("������ʾ"), SS("�������ʧ��"));
        return false;
    }
}

bool MysqlOperate::RetSetPassword(int userId){

    QByteArray passwordmd5;
    passwordmd5 = QCryptographicHash::hash(QString("123456").toLatin1(),QCryptographicHash::Md5);
    QString pw = QString(passwordmd5.toHex());

    QString sq=QStringLiteral("update user set password = '%1' where iduser = '%2'").arg(pw).arg(userId);
    QSqlQuery query;
    query.exec(sq);
    if( query.isActive()){
        return true;
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
        QMessageBox::about(NULL, SS("������ʾ"), SS("��������ʧ��"));
        return false;
    }
}

bool MysqlOperate::DeleteUser(int userId){
    QString sq=QStringLiteral("delete from user where iduser = '%1'").arg(userId);
    QSqlQuery query;
    query.exec(sq);
    if( query.isActive()){
        return true;
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
        QMessageBox::about(NULL, SS("������ʾ"), SS("ɾ���û�ʧ��"));
        return false;
    }
}

double MysqlOperate::MonthStaticSR(QString DateMonth , QString ChargeName){
    QString sq=QStringLiteral("SELECT sum(moneyAmount) FROM liushuizhang where categoryType = '����' and rtime like '%1%' "
                              "and chargeName = '%2'").arg(DateMonth).arg(ChargeName);
    QSqlQuery query;
    query.exec(sq);
    if( query.isActive()){
        while(query.next()){
           double SR = query.value(0).toDouble();
           return SR;
        }
        return true;
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
        QMessageBox::about(NULL, SS("������ʾ"), SS("��ȡ����ͳ��ʧ��"));
        return 0.0;
    }
}

double MysqlOperate::MonthStaticZC(QString DateMonth,QString ChargeName){
    QString sq=QStringLiteral("SELECT sum(moneyAmount) FROM liushuizhang where categoryType = '֧��' and rtime like '%1%' "
                              "and chargeName = '%2'").arg(DateMonth).arg(ChargeName);
    QSqlQuery query;
    query.exec(sq);
    if( query.isActive()){
        while(query.next()){
           double ZC = query.value(0).toDouble();
           return ZC;
        }
        return true;
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
        QMessageBox::about(NULL, SS("������ʾ"), SS("��ȡ֧��ͳ��ʧ��"));
        return 0.0;
    }

}

double MysqlOperate::GetMoneyRemain(){
    double moneyRemain = 0.0;
    QString sq=QStringLiteral("select moneyRemain from liushuizhang where status = '��ȷ��' order by id desc limit 1");
    qDebug()<< sq;
    QSqlQuery query(sq);
    if( query.isActive()){
        while(query.next()){
            qDebug() << query.value(0).toDouble();
            moneyRemain = query.value(0).toDouble();
        }
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
        QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"),QString::fromLocal8Bit("����ȡʧ��"));
    }
    return moneyRemain;
}
