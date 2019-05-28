#ifndef EDITLIUSHUIZHANG_H
#define EDITLIUSHUIZHANG_H

#include <QDialog>

namespace Ui {
class EditLiuShuiZhang;
}

class EditLiuShuiZhang : public QDialog
{
    Q_OBJECT

public:
    explicit EditLiuShuiZhang(QWidget *parent = 0);
    ~EditLiuShuiZhang();
    int LiuShuiID = 0;
    void SetLiuShuiId(int id);
    void LoadData();
private:
    Ui::EditLiuShuiZhang *ui;

private slots:
    void MysqlUpdateLiuShuiZhang();
};

#endif // EDITLIUSHUIZHANG_H
