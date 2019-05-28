#include "addoperator.h"
#include "ui_addoperator.h"
#include "mysqloperate.h"
#include <QMessageBox>


AddOperator::AddOperator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddOperator)
{
    ui->setupUi(this);
    {
        QStringList sl = MysqlOperate::GetAllZG();
        for(int i=0;i<sl.count();i++){
            ui->comboBox_jz_chargeNAme->addItem(sl[i]);
        }
    }
}

AddOperator::~AddOperator()
{
    delete ui;
}


void AddOperator::AddJZY(){//��Ӽ���Ա

    QString Name=ui->lineEdit_jz_name->text().trimmed();
    QString Password =ui->lineEdit_jz_mm->text().trimmed();
    QString PasswordQr =ui->lineEdit_jz_qr->text().trimmed();
    QString ChargeName = ui->comboBox_jz_chargeNAme->currentText();

    if( Name == ""){
        QMessageBox::about(NULL,SS("������ʾ"), SS("�û�������Ϊ��"));
        return ;
    }

    if( Password == ""){
        QMessageBox::about(NULL,SS("������ʾ"), SS("���벻��Ϊ��"));
        return ;
    }
    if(  Password != PasswordQr  ){
        QMessageBox::about(NULL, SS("������ʾ"), SS("���벻һ��"));
        return ;
    }
    bool ret = MysqlOperate::AddJZY(Name,Password,ChargeName);

    if( ret)  QMessageBox::about(NULL, SS("��ʾ"), SS("��Ӽ���Ա�ɹ�"));
}
void AddOperator::AddZG(){
    QString Name=ui->lineEdit_zg_name->text().trimmed();
    QString Password =ui->lineEdit_zg_mm->text().trimmed();
    QString PasswordQr =ui->lineEdit_zg_qr->text().trimmed();

    if( Name == ""){
        QMessageBox::about(NULL,SS("������ʾ"), SS("�û�������Ϊ��"));
        return ;
    }

    if( Password == ""){
        QMessageBox::about(NULL,SS("������ʾ"), SS("���벻��Ϊ��"));
        return ;
    }
    if(  Password != PasswordQr  ){
        QMessageBox::about(NULL, SS("������ʾ"), SS("���벻һ��"));
        return ;
    }
    bool ret = MysqlOperate::AddZG(Name,Password);

    if( ret)  QMessageBox::about(NULL, SS("��ʾ"), SS("������ܳɹ�"));

}
