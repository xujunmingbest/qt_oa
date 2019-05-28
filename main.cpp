#include "mainwindow.h"
#include <QApplication>
#include "login.h"
#include <QTextCodec>
#include "mysqloperate.h"

#include "qiniu/http.h"
#include "qiniu/rs.h"
#include "qiniu/conf.h"
#include "qiniu/resumable_io.h"

#include <tchar.h>
#include <iostream>
#include <urlmon.h>
#pragma comment(lib,"urlmon.lib")

#include "picture.h"
using namespace std;


#include <QProcess>
#include <QDebug>
#include <QUuid>

#include <QSettings>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));

     //读取配置文件
   // QSettings settings("F:\\OA\\pz1.ini",QSettings::IniFormat);
   //
   // settings.clear();
   // settings.beginGroup("MAIN FILE INFO");
   // settings.setValue("exeTitle", "1111122");
   // settings.setValue("curDir", QApplication::applicationDirPath());
   // settings.endGroup();
   // for (int i = 0; i < 5; ++i) {
   //     settings.beginGroup(QString("Torrents%1").arg(i));
   //     settings.setValue("sourceFileName", i);
   //     settings.setValue("destinationFolder",i);
   //     settings.setValue("uploadedBytes", i);
   //     settings.setValue("downloadedBytes", i);
   //     settings.setValue("resumeState", i);
   //     settings.endGroup();
   // }
   // settings.sync();

    //配置文件读取
    //QSettings setting("F:\\OA\\pz.ini",QSettings::IniFormat);
    //QVariant aaa =setting.value("info/color");
    //qDebug() << aaa.toString();

    MysqlOperate::MysqlOpen();


    MainWindow w;
    login l;
    l.exec();
    if(login::LoginSuccess){
        w.show();
        w.showMaximized();
    }
    return a.exec();
}
