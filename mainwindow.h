#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMdiArea *mdiArea;
    QMdiSubWindow *IssubWindowOpened(QString title);
public slots:
    void AuthShow();
    void ChangePassword();
    void _AddOperator();
    void _OperatorList();
    void _TianJiaLiuShuiZhang();
    void _ChaKanLiuShuiZhang();
    void ShuJuTongJi();

private slots:
    void receiveStatisticData(QString data);
};


#endif // MAINWINDOW_H
