#include "login.h"
#include "ui_login.h"
#include "QMessageBox.h"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}
#include <map>
using namespace std;

login::~login()
{
    delete ui;
}
#include "mysqloperate.h"
bool login::LoginSuccess = false;

void login::LoginOperate(){
     LoginSuccess = MysqlOperate::UserLogin(ui->UserName->text(),ui->Password->text());
     if( LoginSuccess == true) this->close();
     else QMessageBox::about(NULL, SS("������ʾ"), SS("�û������������,����ʧ��"));
}
