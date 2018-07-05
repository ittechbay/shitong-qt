#include "dialog_b.h"
#include "ui_dialog_b.h"

Dialog_b::Dialog_b(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_b)
{
    ui->setupUi(this);
}

Dialog_b::~Dialog_b()
{
    delete ui;
}
