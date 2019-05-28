#ifndef CHAKANLIUSHUIZHANG_H
#define CHAKANLIUSHUIZHANG_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
namespace Ui {
class ChaKanLiuShuiZhang;
}


class ChaKanLiuShuiZhang : public QWidget
{
    Q_OBJECT

public:
    explicit ChaKanLiuShuiZhang(QWidget *parent = 0);
    ~ChaKanLiuShuiZhang();


private:
    Ui::ChaKanLiuShuiZhang *ui;
    void UpdateData(int page,int numberperpage);
    int NowPage = 1;
    const int numberPerPage = 30;
    int GetDataCount();
    int GetPageNum(int recordNumber);
    QString sqlSentence; //��ѯ���
    QString sqlCountSentence; //ͳ�������������
public:
    //������������sql���
    void GenerateSearchSql();
    void GenerateSearchSql(QString month,QString chargeName);
public slots:
    void freshA();
private slots:
    void FirstPage();
    void LastPage();
    void FrontPage();
    void nextPage();
    void GoPage();
    void ConditionalSearch();
    void EditButtonClick();


};

#endif // CHAKANLIUSHUIZHANG_H
