#include "editliushuizhang.h"
#include "ui_editliushuizhang.h"

EditLiuShuiZhang::EditLiuShuiZhang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLiuShuiZhang)
{
    ui->setupUi(this);
    ui->dateEdit->setDisplayFormat("yyyy/MM/dd");

    QObject::connect(ui->calendarWidget, SIGNAL(selectionChanged()),
                         this, SLOT(Showcalendar()));
    ui->calendarWidget->setVisible(false);

    //btnGroupFruits = new QButtonGroup(this);
    //btnGroupFruits->addButton(ui->radioButton_sr, 0);
    //btnGroupFruits->addButton(ui->radioButton_zc, 1);
    ui->radioButton_sr->setChecked(true);

    //添加
    //connect(ui->radioButton_sr, SIGNAL(clicked()), this, SLOT(radioSelectChanged()));
    //connect(ui->radioButton_zc, SIGNAL(clicked()), this, SLOT(radioSelectChanged()));

    QDoubleValidator *validator = new QDoubleValidator(0, 100, 2, this);
    ui->lineEdit_money->setValidator(validator);

    ui->groupBox->setAlignment(Qt::AlignHCenter);

}

EditLiuShuiZhang::~EditLiuShuiZhang()
{
    delete ui;
}
#include "mysqloperate.h"
#include <QMessageBox>

void EditLiuShuiZhang::LoadData(){
    QString sq=QStringLiteral("select categoryType,categoryName,moneyAmount,"
                              "remark,status,rtime from liushuizhang where id = %1").arg(LiuShuiID);
    QSqlQuery query(sq);
    qDebug() << sq;
    if( query.isActive()){
        while(query.next()){
            QString categoryType = query.value(0).toString();
            if( categoryType == SS("收入")){
                ui->radioButton_sr->setChecked(true);
            }else if( categoryType == SS("支出")){
                ui->radioButton_zc->setChecked(true);
            }
            QString categoryName = query.value(1).toString();
            ui->KuangXiangName->setText(categoryName);
            QString moneyAmount = query.value(2).toString();
            ui->lineEdit_money->setText(moneyAmount);
            ui->BeiZhu->setText(query.value(3).toString());
            QString status_s = query.value(4).toString();
            ui->status->setCurrentText(status_s);
            QString rtime = query.value(5).toString();
            QDateTime::fromString(rtime, "yyyy/MM/dd");
            ui->dateEdit->setDate(QDate::fromString(rtime, "yyyy/MM/dd"));

            return;
        }
    }
    else{
        QMessageBox::about(NULL, QString::fromLocal8Bit("错误提示"), query.lastError().databaseText());
        QMessageBox::about(NULL, SS("错误提示"),SS("获取流水数据失败"));
    }
    return;
}

void EditLiuShuiZhang::SetLiuShuiId(int id){
    LiuShuiID =id;
    LoadData();
}


#include "mysqlstruct.h"
#include "mysqloperate.h"
void EditLiuShuiZhang::MysqlUpdateLiuShuiZhang(){//添加流水账按钮动作
    S_AddLiuShuiZhang st;
    st.date = ui->dateEdit->text();
    st.BeiZhu = ui->BeiZhu->toPlainText();
    st.date = ui->dateEdit->text();
    st.KuangXiangName = ui->KuangXiangName->toPlainText();

    if( ui->radioButton_sr->isChecked() )  st.KuangXiangType = SS("收入");
    else st.KuangXiangType = SS("支出");

    st.money = ui->lineEdit_money->text().toDouble();
    //st.moneyRemain = 10000.00;
    st.Status = ui->status->currentText();
    double moneyRemain = MysqlOperate::GetMoneyRemain();
    st.moneyRemain = moneyRemain;
    if(st.Status == SS("已确认") ){
        //已确认进行余额的修改
        if( st.KuangXiangType == SS("收入")){
            st.moneyRemain = moneyRemain + st.money ;
        }else if(st.KuangXiangType == SS("支出")){
            if(st.money > moneyRemain ){
                QMessageBox::about(NULL, SS("错误提示"),SS("您的余额不足"));
                return ;
            }
            st.moneyRemain = moneyRemain - st.money ;
        }
    }
    if( MysqlOperate::UpdateLiuShuiZhang(LiuShuiID,st) ){
        this->close();
    }

}


