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
    {//系统管理
        QMenu* Q =  ui->AuthMenu;
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("查看权限"));
            connect(action, SIGNAL(triggered()), this, SLOT(AuthShow()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("修改密码"));
            connect(action, SIGNAL(triggered()), this, SLOT(ChangePassword()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("添加记账员"));
            connect(action, SIGNAL(triggered()), this, SLOT(_AddOperator()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("操作员列表"));
            connect(action, SIGNAL(triggered()), this, SLOT(_OperatorList()));
        }
    }

    {//流水账管理
        QMenu* Q =  ui->menuLiuShuiZhang;
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("添加流水账"));
            connect(action, SIGNAL(triggered()), this, SLOT(_TianJiaLiuShuiZhang()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("查看流水账"));
            connect(action, SIGNAL(triggered()), this, SLOT(_ChaKanLiuShuiZhang()));
        }
        {
            QAction* action = Q->addAction(QString::fromLocal8Bit("数据统计"));
            connect(action, SIGNAL(triggered()), this, SLOT(ShuJuTongJi()));
        }
    }

    {
       // QToolBar* pToolBar = ui->mainToolBar;
       //
       // //QAction* pActionC = new QAction(QIcon(QPixmap(":/img/1.png")), "QZHER");
       // QAction* pActionC = new QAction("查看权限");
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
    QString Title = SS("查看权限");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea添加窗体
        ShowAuth *c1 = new ShowAuth;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }

}
#include "xiugaimima.h"
void MainWindow::ChangePassword(){
    QString Title = SS("修改密码");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea添加窗体
        XiuGaiMiMa *c1 = new XiuGaiMiMa;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }
}

#include "addoperator.h"
#include <QMessageBox>
void MainWindow::_AddOperator(){
    if( g_Auth == SS("记账员")){
         QMessageBox::about(NULL, SS("提示"), SS("没有权限"));
         return ;
    }
    QString Title = SS("添加记账员");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea添加窗体
        AddOperator *c1 = new AddOperator;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }

}

#include "operatorlist.h"
void MainWindow::_OperatorList(){
    QString Title = SS("操作员列表");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea添加窗体
        OperatorList *c1 = new OperatorList;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }

}
#include "tianjialiushuizhang.h"
void MainWindow::_TianJiaLiuShuiZhang(){
    QString Title = SS("添加流水账");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea添加窗体
        TianJiaLiuShuiZhang *c1 = new TianJiaLiuShuiZhang;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }
}
#include "ChaKanliushuizhang.h"

void MainWindow::_ChaKanLiuShuiZhang(){
    QString Title = SS("查看流水账");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea添加窗体
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
        {   //如果已经打开过，则获得焦点
            window->showMaximized();
            return window;
        }
    }
    return Q_NULLPTR;
}

#include "datastatistic.h"
void MainWindow::ShuJuTongJi(){
    QString Title = SS("数据统计");
    QMdiSubWindow *wnd =IssubWindowOpened(Title);
    if( wnd == Q_NULLPTR){
        //mdiarea添加窗体
        DataStatistic *c1 = new DataStatistic;
        mdiArea->addSubWindow(c1);
        c1->setWindowState(Qt::WindowMaximized);
        c1->setWindowTitle(Title);
    }
}

void MainWindow::receiveStatisticData(QString data){
    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        if ( window->windowTitle() == SS("查看流水账"))
        {   //如果已经打开过，则获得焦点
           //ChaKanLiuShuiZhang* cl = (ChaKanLiuShuiZhang*)window;
           //cl->freshA();
           qDebug() << "dagf" ;

           return ;
        }
    }

}
#include <QDebug>

