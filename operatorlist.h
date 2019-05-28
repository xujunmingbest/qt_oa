#ifndef OPERATORLIST_H
#define OPERATORLIST_H

#include <QWidget>

namespace Ui {
class OperatorList;
}

class OperatorList : public QWidget
{
    Q_OBJECT

public:
    explicit OperatorList(QWidget *parent = 0);
    ~OperatorList();
    void UpdateData();
private:
    Ui::OperatorList *ui;

private slots:
    void ResetPassword();
    void EditButtonClick();
    void DeleteUser();
};

#endif // OPERATORLIST_H
