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

    //添加
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

    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    //fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
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
void TianJiaLiuShuiZhang::MysqlAddLiuShuiZhang(){//添加流水账按钮动作
    S_AddLiuShuiZhang st;
    st.date = ui->dateEdit->text();
    st.BeiZhu = ui->BeiZhu->toPlainText();
    st.bookKeeper = g_Name;
    st.chargeName = g_ChargeName;
    st.KuangXiangName = ui->KuangXiangName->toPlainText();

    if( ui->radioButton_sr->isChecked() )  st.KuangXiangType = QString::fromLocal8Bit("收入");
    else st.KuangXiangType = QString::fromLocal8Bit("支出");

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
        QMessageBox::about(NULL, SS("提示"), SS("图片上传成功"));
        PingzhengKey = strId;
    }else{
        QMessageBox::about(NULL, SS("错误提示"), SS("图片上传失败"));

    }


}
