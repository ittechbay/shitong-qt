#include "dialog_power.h"
#include "ui_dialog_power.h"

Dialog_power::Dialog_power(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_power)
{
    ui->setupUi(this);
}

Dialog_power::~Dialog_power()
{
    delete ui;
}
