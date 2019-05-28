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
    model->setHeaderData(0,Qt::Horizontal,SS("用户名"));
    model->setHeaderData(1,Qt::Horizontal,SS("权限类型"));
    model->setHeaderData(2,Qt::Horizontal,SS("主管名称"));
    model->setHeaderData(3,Qt::Horizontal,SS("重置密码"));
    //model->setHeaderData(4,Qt::Horizontal,SS("编辑"));
    model->setHeaderData(4,Qt::Horizontal,SS("删除"));

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
                    QPushButton *m_button = new QPushButton(SS("重置密码"));
                    m_button->setProperty("id", id);
                    ui->tableView->setIndexWidget(model->index(i, 3), m_button);
                    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(ResetPassword()));
                }
                //{
                //    QPushButton *m_button = new QPushButton(SS("编辑"));
                //    m_button->setProperty("id", id);
                //    ui->tableView->setIndexWidget(model->index(i, 4), m_button);
                //    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(EditButtonClick()));
                //}
                {
                    QPushButton *m_button = new QPushButton(SS("删除"));
                    m_button->setProperty("id", id);
                    ui->tableView->setIndexWidget(model->index(i, 4), m_button);
                    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(DeleteUser()));
                }
                i++;
            }
        }else{
            QMessageBox::about(NULL, SS("错误提示"), query.lastError().databaseText());
            QMessageBox::about(NULL, SS("错误提示"), SS("数据搜索失败"));
        }
    }

}

void OperatorList::ResetPassword(){
     if( g_Auth == SS("记账员")){
          QMessageBox::about(NULL, SS("提示"), SS("您没有权限修改操作员"));
          return ;
     }


     QPushButton *btn = (QPushButton *)sender();
     int id = btn->property("id").toInt();

     switch( QMessageBox::warning(NULL, SS("警告"),SS("确定要重置密码吗?"),
                                  QMessageBox::Yes | QMessageBox::Default,
                                  QMessageBox::No | QMessageBox::Escape ))
     {

     case QMessageBox::Yes:
         if( MysqlOperate::RetSetPassword(id)){
             QMessageBox::about(NULL, SS("提示"), SS("修改密码成功"));
         }
         break;

     }
}

void OperatorList::EditButtonClick(){


}

void OperatorList::DeleteUser(){
    if( g_Auth == SS("记账员")){
         QMessageBox::about(NULL, SS("提示"), SS("您没有权限修改操作员"));
         return ;
    }

    QPushButton *btn = (QPushButton *)sender();
    int id = btn->property("id").toInt();

    switch( QMessageBox::warning(NULL, SS("警告"),SS("确定要删除该用户吗?"),
                                 QMessageBox::Yes | QMessageBox::Default,
                                 QMessageBox::No | QMessageBox::Escape ))
    {

    case QMessageBox::Yes:
        if( MysqlOperate::DeleteUser(id)){

            QMessageBox::about(NULL, SS("提示"), SS("用户删除成功"));
            UpdateData();
        }
        break;

    }

}
