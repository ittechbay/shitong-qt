#include "dialog_rb.h"
#include "ui_dialog_rb.h"

Dialog_rb::Dialog_rb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_rb)
{
    ui->setupUi(this);
}

Dialog_rb::~Dialog_rb()
{
    delete ui;
}
