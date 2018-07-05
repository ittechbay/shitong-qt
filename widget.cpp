#include "widget.h"
#include "ui_widget.h"


#include "dialog_clockcfg.h"
#include "dialog_ptpcfg.h"
#include "dialog_power.h"
#include "dialog_swich.h"
#include "dialog_b.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton->setAutoFillBackground(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Dialog_power dp;
    dp.exec();

}

void Widget::on_pushButton_2_pressed()
{

}

void Widget::on_pushButton_2_clicked()
{
    di_ptp.exec();
}

void Widget::on_Widget_destroyed()
{

}

void Widget::on_pushButton_3_clicked()
{
   // QString style = "QFrame {background-image: url(:/img/green.png);}";
   //ui->frame->setStyleSheet(style);
    Dialog_ptpcfg dp;
    dp.exec();
}

void Widget::on_pushButton_9_clicked()
{
    Dialog_clockcfg dp;
    dp.exec();
}

void Widget::on_pushButton_11_clicked()
{
    Dialog_clockcfg dp;
    dp.exec();
}

void Widget::on_pushButton_10_clicked()
{
    Dialog_swich dp;
    dp.exec();
}

void Widget::on_pushButton_20_clicked()
{
    Dialog_power dp;
    dp.exec();
}

void Widget::on_pushButton_19_clicked()
{
    Dialog_power dp;
    dp.exec();
}

void Widget::on_pushButton_24_clicked()
{
    Dialog_b dp;
    dp.exec();
}
