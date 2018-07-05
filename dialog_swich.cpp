#include "dialog_swich.h"
#include "ui_dialog_swich.h"

Dialog_swich::Dialog_swich(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_swich)
{
    ui->setupUi(this);
}

Dialog_swich::~Dialog_swich()
{
    delete ui;
}
