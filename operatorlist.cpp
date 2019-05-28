#include "operatorlist.h"
#include "ui_operatorlist.h"

#include "mysqloperate.h"
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>
OperatorList::OperatorList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperatorList)
{
    ui->setupUi(this);
    QStandardItemModel  *model = new QStandardItemModel();
    ui->tableView->setModel(model);
    UpdateData();
}

OperatorList::~OperatorList()
{
    delete ui;
}

void OperatorList::UpdateData(){

    QStandardItemModel  *model = (QStandardItemModel *)ui->tableView->model();
    model->clear();
    //Sleep(200);
    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal,SS("�û���"));
    model->setHeaderData(1,Qt::Horizontal,SS("Ȩ������"));
    model->setHeaderData(2,Qt::Horizontal,SS("��������"));
    model->setHeaderData(3,Qt::Horizontal,SS("��������"));
    //model->setHeaderData(4,Qt::Horizontal,SS("�༭"));
    model->setHeaderData(4,Qt::Horizontal,SS("ɾ��"));

    ui->tableView->setModel(model);
    {
        int i=0;
       QString sq = QStringLiteral("select username,authtype,chargeName,iduser from user");
        QSqlQuery query(sq);
        if( query.isActive()){
            while(query.next()){
                model->setItem(i,0,new QStandardItem(query.value(0).toString()));
                model->setItem(i,1,new QStandardItem(query.value(1).toString()));
                model->setItem(i,2,new QStandardItem(query.value(2).toString()));
                int id = query.value(3).toInt();
                {
                    QPushButton *m_button = new QPushButton(SS("��������"));
                    m_button->setProperty("id", id);
                    ui->tableView->setIndexWidget(model->index(i, 3), m_button);
                    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(ResetPassword()));
                }
                //{
                //    QPushButton *m_button = new QPushButton(SS("�༭"));
                //    m_button->setProperty("id", id);
                //    ui->tableView->setIndexWidget(model->index(i, 4), m_button);
                //    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(EditButtonClick()));
                //}
                {
                    QPushButton *m_button = new QPushButton(SS("ɾ��"));
                    m_button->setProperty("id", id);
                    ui->tableView->setIndexWidget(model->index(i, 4), m_button);
                    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(DeleteUser()));
                }
                i++;
            }
        }else{
            QMessageBox::about(NULL, SS("������ʾ"), query.lastError().databaseText());
            QMessageBox::about(NULL, SS("������ʾ"), SS("��������ʧ��"));
        }
    }

}

void OperatorList::ResetPassword(){
     if( g_Auth == SS("����Ա")){
          QMessageBox::about(NULL, SS("��ʾ"), SS("��û��Ȩ���޸Ĳ���Ա"));
          return ;
     }


     QPushButton *btn = (QPushButton *)sender();
     int id = btn->property("id").toInt();

     switch( QMessageBox::warning(NULL, SS("����"),SS("ȷ��Ҫ����������?"),
                                  QMessageBox::Yes | QMessageBox::Default,
                                  QMessageBox::No | QMessageBox::Escape ))
     {

     case QMessageBox::Yes:
         if( MysqlOperate::RetSetPassword(id)){
             QMessageBox::about(NULL, SS("��ʾ"), SS("�޸�����ɹ�"));
         }
         break;

     }
}

void OperatorList::EditButtonClick(){


}

void OperatorList::DeleteUser(){
    if( g_Auth == SS("����Ա")){
         QMessageBox::about(NULL, SS("��ʾ"), SS("��û��Ȩ���޸Ĳ���Ա"));
         return ;
    }

    QPushButton *btn = (QPushButton *)sender();
    int id = btn->property("id").toInt();

    switch( QMessageBox::warning(NULL, SS("����"),SS("ȷ��Ҫɾ�����û���?"),
                                 QMessageBox::Yes | QMessageBox::Default,
                                 QMessageBox::No | QMessageBox::Escape ))
    {

    case QMessageBox::Yes:
        if( MysqlOperate::DeleteUser(id)){

            QMessageBox::about(NULL, SS("��ʾ"), SS("�û�ɾ���ɹ�"));
            UpdateData();
        }
        break;

    }

}
