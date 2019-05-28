#include "tianjialiushuizhang.h"
#include "ui_tianjialiushuizhang.h"
#include <QDebug>

TianJiaLiuShuiZhang::TianJiaLiuShuiZhang(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TianJiaLiuShuiZhang)
{
    ui->setupUi(this);
    ui->dateEdit->setDisplayFormat("yyyy/MM/dd");

    QObject::connect(ui->calendarWidget, SIGNAL(selectionChanged()),
                         this, SLOT(Showcalendar()));
    ui->calendarWidget->setVisible(false);

    btnGroupFruits = new QButtonGroup(this);
    btnGroupFruits->addButton(ui->radioButton_sr, 0);
    btnGroupFruits->addButton(ui->radioButton_zc, 1);
    ui->radioButton_sr->setChecked(true);

    //����
    connect(ui->radioButton_sr, SIGNAL(clicked()), this, SLOT(radioSelectChanged()));
    connect(ui->radioButton_zc, SIGNAL(clicked()), this, SLOT(radioSelectChanged()));

    QDoubleValidator *validator = new QDoubleValidator(0, 100, 2, this);
    ui->lineEdit_money->setValidator(validator);

    ui->groupBox->setAlignment(Qt::AlignHCenter);

}

TianJiaLiuShuiZhang::~TianJiaLiuShuiZhang()
{
    delete ui;
}

void TianJiaLiuShuiZhang::mousePressEvent(QMouseEvent* event){
    if(event->button()==Qt::LeftButton)
    {
        ui->calendarWidget->setVisible(false);
    }
}


void TianJiaLiuShuiZhang::Showcalendar(){
    ui->calendarWidget->setVisible(!ui->calendarWidget->isVisible());
    ui->dateEdit->setDate(ui->calendarWidget->selectedDate());
}

void TianJiaLiuShuiZhang::radioSelectChanged(){
    switch(btnGroupFruits->checkedId())
    {
    case 0:
        qDebug() << "0000";
        break;
    case 1:
        qDebug() << "1111";
        break;
    }

}


#include <QFileDialog>
void TianJiaLiuShuiZhang::SelectFile()
{

    //�����ļ��Ի�����
    QFileDialog *fileDialog = new QFileDialog(this);
    //�����ļ��Ի������
    fileDialog->setWindowTitle(tr("��ͼƬ"));
    //����Ĭ���ļ�·��
    //fileDialog->setDirectory(".");
    //�����ļ�������
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //������ͼģʽ
    fileDialog->setViewMode(QFileDialog::Detail);
    //��ӡ����ѡ����ļ���·��
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    for(auto tmp:fileNames){
        Pingzhengfile = tmp;
        QFileInfo fi;
        fi = QFileInfo(tmp);
        QString file_name = fi.fileName();
        ui->label_fileName->setText(file_name);
    }
}
#include "mysqlstruct.h"
#include "mysqloperate.h"
void TianJiaLiuShuiZhang::MysqlAddLiuShuiZhang(){//������ˮ�˰�ť����
    S_AddLiuShuiZhang st;
    st.date = ui->dateEdit->text();
    st.BeiZhu = ui->BeiZhu->toPlainText();
    st.bookKeeper = g_Name;
    st.chargeName = g_ChargeName;
    st.KuangXiangName = ui->KuangXiangName->toPlainText();

    if( ui->radioButton_sr->isChecked() )  st.KuangXiangType = QString::fromLocal8Bit("����");
    else st.KuangXiangType = QString::fromLocal8Bit("֧��");

    st.money = ui->lineEdit_money->text().toDouble();
    st.moneyRemain = MysqlOperate::GetMoneyRemain();
    st.Status = ui->status->currentText();
    st.proof = PingzhengKey;
    MysqlOperate::AddLiuShuiZhang(st);
}

#include <QUuid>
#include <QProcess>
#include <QMessageBox>
void TianJiaLiuShuiZhang::UploadPingZheng(){
    QProcess process;
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    QString cmd = QString("F:\\OA\\OA\\exe\\Project1.exe upload %1 %2").arg(strId).arg(Pingzhengfile);

    if( process.execute(cmd) == 1){
        QMessageBox::about(NULL, SS("��ʾ"), SS("ͼƬ�ϴ��ɹ�"));
        PingzhengKey = strId;
    }else{
        QMessageBox::about(NULL, SS("������ʾ"), SS("ͼƬ�ϴ�ʧ��"));

    }


}