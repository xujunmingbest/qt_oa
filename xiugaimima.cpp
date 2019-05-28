#include "xiugaimima.h"
#include "ui_xiugaimima.h"

XiuGaiMiMa::XiuGaiMiMa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XiuGaiMiMa)
{
    ui->setupUi(this);
}

XiuGaiMiMa::~XiuGaiMiMa()
{
    delete ui;
}

#include "mysqloperate.h"
#include <QMessageBox>
void XiuGaiMiMa::ButtonClick(){
    if(  ui->lineEdit_new->text() == ""){
        QMessageBox::about(NULL,QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("���벻��Ϊ��"));
        return ;
    }
    if(ui->lineEdit_qr->text() != ui->lineEdit_new->text()  ){
        QMessageBox::about(NULL, QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("���벻һ��"));
        return ;
    }

    bool ret = MysqlOperate::UpdatePassword(ui->lineEdit_new->text());
    if( ret)  QMessageBox::about(NULL, SS("��ʾ"), SS("�����޸ĳɹ�"));
    else QMessageBox::about(NULL, SS("������ʾ"), SS("�����޸�ʧ��"));
}
