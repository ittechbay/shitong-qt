#include "setptp.h"
#include "ui_setptp.h"

setPTP::setPTP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setPTP)
{
    ui->setupUi(this);
}

setPTP::~setPTP()
{
    delete ui;
}
