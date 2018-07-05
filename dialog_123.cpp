#include "dialog_123.h"
#include "ui_dialog_123.h"

Dialog_123::Dialog_123(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_123)
{
    ui->setupUi(this);
}

Dialog_123::~Dialog_123()
{
    delete ui;
}
