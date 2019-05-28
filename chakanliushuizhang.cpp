#include "chakanliushuizhang.h"
#include "ui_chakanliushuizhang.h"

#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

#include "mysqloperate.h"

ChaKanLiuShuiZhang::ChaKanLiuShuiZhang(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChaKanLiuShuiZhang)
{
    ui->setupUi(this);
    {
        QStringList sl = MysqlOperate::GetAllJZY();
        for(int i=0;i<sl.count();i++){
            ui->comboBox_jzy->addItem(sl[i]);
        }
    }
    {
        GenerateSearchSql();
        QStandardItemModel  *model = new QStandardItemModel();
        ui->tableView->setModel(model);

        int recordNumber =  GetDataCount(); //��ȡ�ܵ���������
        UpdateData(1,30);
        int AllPAge =GetPageNum(recordNumber);
        ui->label_page->setText(QStringLiteral("%1 / %2 ҳ").arg(1).arg(AllPAge));

        //����ҳ�밴ťΪint����
        QIntValidator *validator = new QIntValidator();
        ui->lineEdit_page->setValidator(validator);
    }

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    /*
    {
        QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
        model->setQuery("select categoryType,categoryName,moneyAmount,moneyRemain,"
                        "remark,bookkeeper,chargeName,status from liushuizhang");

        QHeaderView *headerView = ui->tableView->verticalHeader();
        headerView->
       // QStringList headerView;
        headerView << QString::fromLocal8Bit("�������");
        headerView << QString::fromLocal8Bit("��������");
        headerView << QString::fromLocal8Bit("�������");
        headerView << QString::fromLocal8Bit("���");
        headerView << QString::fromLocal8Bit("��ע");
        headerView << QString::fromLocal8Bit("����Ա");
        headerView << QString::fromLocal8Bit("����");
        headerView << QString::fromLocal8Bit("״̬");
        headerView << QString::fromLocal8Bit("����");
        ui->tableView->setHorizontalHeader(headerView);
        //headerView->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("�������"));
        //headerView->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("��������"));
        //headerView->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("�������"));
        //headerView->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("���"));
        //headerView->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("��ע"));
        //headerView->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("����Ա"));
        //headerView->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("����"));
        //headerView->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("״̬"));
        //headerView->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("����"));
        ui->tableView->setModel(model);
        QPushButton *m_button = new QPushButton("Download");
        ui->tableView->setIndexWidget(model->index(model->rowCount() - 1, 8), m_button);


    }
    */
}
#include "windows.h"
#include "mysqloperate.h"
void ChaKanLiuShuiZhang::UpdateData(int page,int numberperpage){

    QStandardItemModel  *model = (QStandardItemModel *)ui->tableView->model();
    model->clear();
    //Sleep(200);
    model->setColumnCount(10);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("�������"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("��������"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("�������"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("���"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("��ע"));
    model->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("����Ա"));
    model->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("����"));
    model->setHeaderData(7,Qt::Horizontal,QString::fromLocal8Bit("״̬"));
    model->setHeaderData(8,Qt::Horizontal,QString::fromLocal8Bit("ʱ��"));
    model->setHeaderData(9,Qt::Horizontal,QString::fromLocal8Bit("����"));
    ui->tableView->setModel(model);
    {
        int i=0;
       QString slimit = QStringLiteral(" limit %1 offset %2").arg(numberperpage).arg((page-1)*numberperpage);
        QSqlQuery query(sqlSentence + slimit);
        if( query.isActive()){
            while(query.next()){
                QString KXType = query.value(0).toString();
                model->setItem(i,0,new QStandardItem(KXType));
                model->setItem(i,1,new QStandardItem(query.value(1).toString()));

                QString Money = query.value(2).toString();
                if(KXType == SS("֧��")) {
                    Money = "-" + Money;
                    model->setItem(i,2,new QStandardItem(Money));
                    model->item(i, 2)->setForeground(QBrush(QColor(255, 0, 0)));
                }
                else {
                    Money = "+" + Money;
                    model->setItem(i,2,new QStandardItem(Money));
                    model->item(i, 2)->setForeground(QBrush(QColor(0,128,0)));
                }


                model->setItem(i,3,new QStandardItem(query.value(3).toString()));
                model->setItem(i,4,new QStandardItem(query.value(4).toString()));
                model->setItem(i,5,new QStandardItem(query.value(5).toString()));
                model->setItem(i,6,new QStandardItem(query.value(6).toString()));
                model->setItem(i,7,new QStandardItem(query.value(7).toString()));
                model->setItem(i,8,new QStandardItem(query.value(8).toString()));
                QPushButton *m_button = new QPushButton(SS("�༭"));
                m_button->setProperty("id", query.value(9).toInt());
                ui->tableView->setIndexWidget(model->index(model->rowCount() - 1, 9), m_button);
                connect(m_button, SIGNAL(clicked(bool)), this, SLOT(EditButtonClick()));

                i++;
            }
        }else{
            QMessageBox::about(NULL, SS("������ʾ"), SS("��������ʧ��"));
        }
    }

}



ChaKanLiuShuiZhang::~ChaKanLiuShuiZhang()
{
    delete ui;
}

void ChaKanLiuShuiZhang::GenerateSearchSql(QString month,QString chargeName){

    QString sq = QStringLiteral("select categoryType,categoryName,moneyAmount,moneyRemain,"
                              "remark,bookkeeper,chargeName,status,rtime,id from liushuizhang "
                              "where rtime like '%1%' and chargeName = '%2'").arg(month).arg(chargeName);
    QString sqCount = QStringLiteral("select count(*) from liushuizhang where rtime like '%1%' and chargeName = '%2'").arg(month).arg(chargeName);
    sqlSentence = sq;
    sqlCountSentence = sqCount;
    freshA();

}

void ChaKanLiuShuiZhang::GenerateSearchSql(){
    QStringList slist;
    //ui->comboBox->currentText()
    if( ui->comboBox_kx->currentText() != SS("����")){
        slist << QString(" categoryType") +" = '" +ui->comboBox_kx->currentText() + "' ";
    }
    if( ui->comboBox_jzy->currentText() != SS("����Ա") ){
        slist <<  QString(" bookkeeper") +" = '" + ui->comboBox_jzy->currentText() + "' ";
    }
    if( ui->lineEdit_datebegin->text().trimmed() != "" && ui->lineEdit_dateend->text().trimmed() != ""){
        slist <<  QString(" rtime between '") + ui->lineEdit_datebegin->text().trimmed() + "' and '"
                  + ui->lineEdit_dateend->text().trimmed() + "' ";
    }
    if(ui->comboBox_status->currentText() != SS("״̬")){
        slist <<  QString(" status") +" = '" + ui->comboBox_status->currentText() + "' ";
    }

    QString sq=QStringLiteral("select categoryType,categoryName,moneyAmount,moneyRemain,"
                              "remark,bookkeeper,chargeName,status,rtime,id from liushuizhang ");

    QString sqCount = QStringLiteral("select count(*) from liushuizhang");

    if( slist.count() > 0){
        sqCount +=" where ";
        sq +=" where ";
    }
    for(int i=0;i< slist.count();i++){
        if( i != 0) {
            sq += " and ";
            sqCount +=" and ";
        }
        sq += slist[i];
        sqCount += slist[i];
    }

    sqlSentence = sq;
    sqlCountSentence = sqCount;


    return;
}

#include <QDebug>

void ChaKanLiuShuiZhang::freshA(){
    qDebug() << "freshA";
    UpdateData(1,30);
    int recordNumber = GetDataCount();
    int totalpage = GetPageNum(recordNumber);
    NowPage = 1;
    ui->label_page->setText(QStringLiteral("%1 / %2 ҳ").arg(NowPage).arg(totalpage));
}

#include "mysqloperate.h"
int ChaKanLiuShuiZhang::GetDataCount(){
    QSqlQuery query(sqlCountSentence);
    qDebug() << sqlCountSentence;
    if( query.isActive()){
        while(query.next()){
            int recordNumber = query.value(0).toInt();
            //��ʾ��������
            ui->label_count->setText(SS("��") + query.value(0).toString() + SS("��Ϣ"));
            return query.value(0).toInt();
        }
    }
    return 0;
}

int ChaKanLiuShuiZhang::GetPageNum(int recordNumber){
    int AllPAge = recordNumber / numberPerPage;
    int YuShu = recordNumber % numberPerPage;
    if(YuShu != 0 ) AllPAge++;
    return AllPAge;
}

void ChaKanLiuShuiZhang::FirstPage(){
    NowPage =1;
    int recordNumber = GetDataCount(); //��ȡ�ܵ���������
    UpdateData(1,numberPerPage);

    int AllPAge = GetPageNum(recordNumber);
    ui->label_page->setText(QStringLiteral("%1 / %2 ҳ").arg(1).arg(AllPAge));
}
void ChaKanLiuShuiZhang::LastPage(){
    int recordNumber = GetDataCount();
    int totalpage = GetPageNum(recordNumber);
    NowPage =totalpage;
    UpdateData(totalpage,numberPerPage);
    ui->label_page->setText(QStringLiteral("%1 / %2 ҳ").arg(totalpage).arg(totalpage));
}

void ChaKanLiuShuiZhang::FrontPage(){
    NowPage =   MAX(NowPage-1,1);
    int recordNumber = GetDataCount();
    UpdateData(NowPage,numberPerPage);
    ui->label_page->setText(QStringLiteral("%1 / %2 ҳ").arg(NowPage).arg(GetPageNum(recordNumber)));
}

void ChaKanLiuShuiZhang::nextPage(){
    int recordNumber = GetDataCount();
    int totalpage = GetPageNum(recordNumber);
    NowPage =   MIN(NowPage+1,totalpage);
    UpdateData(NowPage,numberPerPage);
    ui->label_page->setText(QStringLiteral("%1 / %2 ҳ").arg(NowPage).arg(totalpage));
}

void ChaKanLiuShuiZhang::GoPage(){
    int gopage = ui->lineEdit_page->text().toInt();
    int recordNumber = GetDataCount();
    int totalpage = GetPageNum(recordNumber);
    if( gopage < 1) gopage =1;
    else if( gopage > totalpage) gopage =totalpage;
    NowPage = gopage;
    UpdateData(gopage,numberPerPage);
    ui->label_page->setText(QStringLiteral("%1 / %2 ҳ").arg(NowPage).arg(totalpage));
}

//
void ChaKanLiuShuiZhang::ConditionalSearch(){
     GenerateSearchSql();
     FirstPage();
}
#include "editliushuizhang.h"
void ChaKanLiuShuiZhang::EditButtonClick(){
    if( g_Auth == SS("����Ա")){
         QMessageBox::about(NULL, SS("��ʾ"), SS("��û��Ȩ�ޱ༭��ˮ��"));
         return ;
    }
    QPushButton *btn = (QPushButton *)sender();
    int id = btn->property("id").toInt();
    EditLiuShuiZhang elsz;
    elsz.SetLiuShuiId(id);
    elsz.exec();

    //QString slimit = QStringLiteral(" select categoryType,categoryName,moneyAmount,moneyRemain,"
    //                                "remark,bookkeeper,chargeName,status,rtime from liushuizhang where id = %1").arg(id);
    //QSqlQuery query(sqlSentence + slimit);
    //if( query.isActive()){
    //    while(query.next()){
    //        QString KXType = query.value(0).toString();
    //    }
    //}
    //else{
    //     QMessageBox::about(NULL, SS("������ʾ"), SS("���ݻ�ȡʧ��"));
    //}
}
