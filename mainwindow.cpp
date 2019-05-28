#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiArea.h>
#include <QMdiSubWindow.h>
#include "mysqloperate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea(this);
    this->setCentralWidget(mdiArea);
    {//ϵͳ����
        QMenu* Q =  ui->AuthMenu;
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("�鿴Ȩ��"));
            connect(action, SIGNAL(triggered()), this, SLOT(AuthShow()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("�޸�����"));
            connect(action, SIGNAL(triggered()), this, SLOT(ChangePassword()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("��Ӽ���Ա"));
            connect(action, SIGNAL(triggered()), this, SLOT(_AddOperator()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("����Ա�б�"));
            connect(action, SIGNAL(triggered()), this, SLOT(_OperatorList()));
        }
    }

    {//��ˮ�˹���
        QMenu* Q =  ui->menuLiuShuiZhang;
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("�����ˮ��"));
            connect(action, SIGNAL(triggered()), this, SLOT(_TianJiaLiuShuiZhang()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("�鿴��ˮ��"));
            connect(action, SIGNAL(triggered()), this, SLOT(_ChaKanLiuShuiZhang()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("����ͳ��"));
            connect(action, SIGNAL(triggered()), this, SLOT(ShuJuTongJi()));
        }
    }

    {
       // QToolBar* pToolBar = ui->mainToolBar;
       //
       // //QAction* pActionC = new QAction(QIcon(QPixmap(":/img/1.png")), "QZHER");
       // QAction* pActionC = new QAction("�鿴Ȩ��");
       // pToolBar->addAction(pActionC);
       //
       // //QObject::connect(pActionC, SIGNAL(triggered(bool)), this, SLOT(caozuo3()));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "showauth.h"

void MainWindow::AuthShow(){
    QString Title = SS("�鿴Ȩ��");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea��Ӵ���
        ShowAuth *c1 = new ShowAuth;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }

}
#include "xiugaimima.h"
void MainWindow::ChangePassword(){
    QString Title = SS("�޸�����");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea��Ӵ���
        XiuGaiMiMa *c1 = new XiuGaiMiMa;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }
}

#include "addoperator.h"
#include <QMessageBox>
void MainWindow::_AddOperator(){
    if( g_Auth == SS("����Ա")){
         QMessageBox::about(NULL, SS("��ʾ"), SS("û��Ȩ��"));
         return ;
    }
    QString Title = SS("��Ӽ���Ա");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea��Ӵ���
        AddOperator *c1 = new AddOperator;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }

}

#include "operatorlist.h"
void MainWindow::_OperatorList(){
    QString Title = SS("����Ա�б�");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea��Ӵ���
        OperatorList *c1 = new OperatorList;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }

}
#include "tianjialiushuizhang.h"
void MainWindow::_TianJiaLiuShuiZhang(){
    QString Title = SS("�����ˮ��");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea��Ӵ���
        TianJiaLiuShuiZhang *c1 = new TianJiaLiuShuiZhang;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }
}
#include "ChaKanliushuizhang.h"

void MainWindow::_ChaKanLiuShuiZhang(){
    QString Title = SS("�鿴��ˮ��");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea��Ӵ���
        ChaKanLiuShuiZhang *c1 = new ChaKanLiuShuiZhang;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }
}

QMdiSubWindow * MainWindow::IssubWindowOpened(QString title){

    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        if ( window->windowTitle() == title)
        {   //����Ѿ��򿪹������ý���
            window->showMaximized();
            return window;
        }
    }
    return Q_NULLPTR;
}

#include "datastatistic.h"
void MainWindow::ShuJuTongJi(){
    QString Title = SS("����ͳ��");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea��Ӵ���
        DataStatistic *c1 = new DataStatistic;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }
}

void MainWindow::receiveStatisticData(QString data){
    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        if ( window->windowTitle() == SS("�鿴��ˮ��"))
        {   //����Ѿ��򿪹������ý���
           //ChaKanLiuShuiZhang* cl = (ChaKanLiuShuiZhang*)window;
           //cl->freshA();
           qDebug() << "dagf" ;

           return ;
        }
    }

}
#include <QDebug>

