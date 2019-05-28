#include "showauth.h"
#include "ui_showauth.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QTextCodec>
#include "mysqloperate.h"
#include <QJsonObject>

ShowAuth::ShowAuth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowAuth)
{
    ui->setupUi(this);
    QStandardItemModel  *model = new QStandardItemModel();

    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("-ģ����-"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("-�ɶ���д-"));
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    QJsonObject jo  = MysqlOperate::GetAuth();


    QJsonObject::Iterator it;
    QString keyString="";
    int RWcode = 0;
    int i=0;
    for(it=jo.begin();it!=jo.end();it++,i++)
    {
        model->setItem(i,0,new QStandardItem(it.key()));
        int authCode = it.value().toInt();

        if( authCode == 1 ){ // no read or write
            model->setItem(i,1,new QStandardItem(QString::fromLocal8Bit("���ɶ�")));

        }else if(authCode == 2){
            model->setItem(i,1,new QStandardItem(QString::fromLocal8Bit("�ɶ�����д")));

        }
        else if(authCode == 3){
            model->setItem(i,1,new QStandardItem(QString::fromLocal8Bit("�ɶ���д")));

        }
    }
}

ShowAuth::~ShowAuth()
{
    delete ui;
}
