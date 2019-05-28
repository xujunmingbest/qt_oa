#ifndef ADDOPERATOR_H
#define ADDOPERATOR_H

#include <QWidget>

namespace Ui {
class AddOperator;
}

class AddOperator : public QWidget
{
    Q_OBJECT

public:
    explicit AddOperator(QWidget *parent = 0);
    ~AddOperator();

private:
    Ui::AddOperator *ui;

private slots:
    void AddJZY(); //ÃÌº”º«’À‘±
    void AddZG();
};

#endif // ADDOPERATOR_H
