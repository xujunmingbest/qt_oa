#ifndef SHOWAUTH_H
#define SHOWAUTH_H

#include <QWidget>

namespace Ui {
class ShowAuth;
}

class ShowAuth : public QWidget
{
    Q_OBJECT

public:
    explicit ShowAuth(QWidget *parent = 0);
    ~ShowAuth();

private:
    Ui::ShowAuth *ui;
};

#endif // SHOWAUTH_H
