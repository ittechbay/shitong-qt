#include "setntp.h"
#include "ui_setntp.h"

setNTP::setNTP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setNTP)
{
    ui->setupUi(this);
}

setNTP::~setNTP()
{
    delete ui;
}
