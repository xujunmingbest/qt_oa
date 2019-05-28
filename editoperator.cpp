#include "editoperator.h"
#include "ui_editoperator.h"

EditOperator::EditOperator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditOperator)
{
    ui->setupUi(this);
}

EditOperator::~EditOperator()
{
    delete ui;
}
