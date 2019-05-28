#ifndef TIANJIALIUSHUIZHANG_H
#define TIANJIALIUSHUIZHANG_H

#include <QWidget>
#include <QMouseEvent>
#include <QButtonGroup>

namespace Ui {
class TianJiaLiuShuiZhang;
}

class TianJiaLiuShuiZhang : public QWidget
{
    Q_OBJECT

public:
    explicit TianJiaLiuShuiZhang(QWidget *parent = 0);
    ~TianJiaLiuShuiZhang();

private:
    Ui::TianJiaLiuShuiZhang *ui;
    QButtonGroup *btnGroupFruits;
    QString Pingzhengfile;
    QString PingzhengKey;
protected:
    void mousePressEvent(QMouseEvent* event);

private slots:
    void Showcalendar();
    void radioSelectChanged();
    void SelectFile();
    void MysqlAddLiuShuiZhang();
    void UploadPingZheng(); //ÉÏ´«Æ¾Ö¤

};

#endif // TIANJIALIUSHUIZHANG_H
