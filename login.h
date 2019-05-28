#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    static bool LoginSuccess;

private:
    Ui::login *ui;

private slots:
   void LoginOperate();

};

#endif // LOGIN_H
