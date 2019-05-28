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
        QMessageBox::about(NULL,QString::fromLocal8Bit("错误提示"), QString::fromLocal8Bit("密码不能为空"));
        return ;
    }
    if(ui->lineEdit_qr->text() != ui->lineEdit_new->text()  ){
        QMessageBox::about(NULL, QString::fromLocal8Bit("错误提示"), QString::fromLocal8Bit("密码不一致"));
        return ;
    }

    bool ret = MysqlOperate::UpdatePassword(ui->lineEdit_new->text());
    if( ret)  QMessageBox::about(NULL, SS("提示"), SS("密码修改成功"));
    else QMessageBox::about(NULL, SS("错误提示"), SS("密码修改失败"));
}
