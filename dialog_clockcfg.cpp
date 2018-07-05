#include "dialog_clockcfg.h"
#include "ui_dialog_clockcfg.h"

Dialog_clockcfg::Dialog_clockcfg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_clockcfg)
{
    ui->setupUi(this);
    QString style = "QPushButton {image: url(:/img/add.png);}";
    ui->pushButton->setStyleSheet(style);
}

Dialog_clockcfg::~Dialog_clockcfg()
{
    delete ui;
}
