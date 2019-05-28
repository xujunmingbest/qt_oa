#ifndef XIUGAIMIMA_H
#define XIUGAIMIMA_H

#include <QWidget>

namespace Ui {
class XiuGaiMiMa;
}

class XiuGaiMiMa : public QWidget
{
    Q_OBJECT

public:
    explicit XiuGaiMiMa(QWidget *parent = 0);
    ~XiuGaiMiMa();

private:
    Ui::XiuGaiMiMa *ui;

private slots:
    void ButtonClick();
};

#endif // XIUGAIMIMA_H
