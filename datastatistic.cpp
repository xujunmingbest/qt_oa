#include "datastatistic.h"
#include "ui_datastatistic.h"

#include "mysqloperate.h"
DataStatistic::DataStatistic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataStatistic)
{
    ui->setupUi(this);
    QStringList sl = MysqlOperate::GetAllZG();
    for(int i=0;i<sl.count();i++){
        ui->comboBox->addItem(sl[i]);
    }
    ui->dateEdit->setDisplayFormat("yyyy/MM");
}




DataStatistic::~DataStatistic()
{
    delete ui;
}

void DataStatistic::SearchClick(){
    QString month = ui->dateEdit->text();
    QString chargeName = ui->comboBox->currentText();
    double SR = MysqlOperate::MonthStaticSR(month,chargeName);
    double ZC = MysqlOperate::MonthStaticZC(month,chargeName);

    ui->label_sr->setText(QStringLiteral("%1 元").arg(SR));
    ui->label_zc->setText(QStringLiteral("%1 元").arg(ZC));
    ui->label_ts->setText(chargeName);
}

#include <QMdiArea>
#include <QMdiSubWindow>
#include "mainwindow.h"
#include "chakanliushuizhang.h"
#include <thread>
using namespace std;
void a(QMdiArea *mdiArea){
    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        if ( window->windowTitle() == SS("查看流水账"))
        {   //如果已经打开过，则获得焦点
            window->showMaximized();
            ((ChaKanLiuShuiZhang *)window)->freshA();
            return ;
        }
    }

}

void DataStatistic::ChaKanMingXi(){
    QMdiArea *mdiArea  = ((QMdiSubWindow*)this->parent())->mdiArea();
    QString month = ui->dateEdit->text();
    QString chargeName = ui->comboBox->currentText();

    ((MainWindow*)mdiArea->parentWidget())->_ChaKanLiuShuiZhang();
    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        if ( window->windowTitle() == SS("查看流水账"))
        {   //如果已经打开过，则获得焦点
           ChaKanLiuShuiZhang* cl = (ChaKanLiuShuiZhang*)window->widget();
           cl->GenerateSearchSql(month,chargeName);
           return ;
        }
    }
}
