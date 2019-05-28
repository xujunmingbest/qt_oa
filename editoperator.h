#ifndef EDITOPERATOR_H
#define EDITOPERATOR_H

#include <QDialog>

namespace Ui {
class EditOperator;
}

class EditOperator : public QDialog
{
    Q_OBJECT

public:
    explicit EditOperator(QWidget *parent = 0);
    ~EditOperator();

private:
    Ui::EditOperator *ui;
};

#endif // EDITOPERATOR_H
