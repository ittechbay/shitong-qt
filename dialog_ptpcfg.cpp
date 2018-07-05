#include "dialog_ptpcfg.h"
#include "ui_dialog_ptpcfg.h"

Dialog_ptpcfg::Dialog_ptpcfg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ptpcfg)
{
    ui->setupUi(this);

}

Dialog_ptpcfg::~Dialog_ptpcfg()
{
    delete ui;
}
