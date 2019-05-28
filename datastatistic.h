#ifndef DATASTATISTIC_H
#define DATASTATISTIC_H

#include <QWidget>

namespace Ui {
class DataStatistic;
}

class DataStatistic : public QWidget
{
    Q_OBJECT

public:
    explicit DataStatistic(QWidget *parent = 0);
    ~DataStatistic();

private:
    Ui::DataStatistic *ui;
signals:
    void  sendData(QString);
private slots:
    void SearchClick();
    void ChaKanMingXi();
};

#endif // DATASTATISTIC_H
