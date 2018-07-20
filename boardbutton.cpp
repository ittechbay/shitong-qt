#include "boardbutton.h"
#include "ui_boardbutton.h"

BoardButton::BoardButton(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BoardButton)
{
    ui->setupUi(this);
}

BoardButton::~BoardButton()
{
    delete ui;
}

void BoardButton::setBoard(const QString &boardName)
{
    ui->label->setText(boardName);
    ui->label_2->setText(QString());
    ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(QString());
    ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(QString());
    ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(QString());
    ui->widget_5->setStyleSheet(QString());


}

void BoardButton::setBoard(const QString &boardName,const QString &s1)
{
    ui->label->setText(boardName);
    ui->label_2->setText(s1);
    //ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(QString());
    ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(QString());
    ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(QString());
    ui->widget_5->setStyleSheet(QString());


}

void BoardButton::setBoard(const QString &boardName,const QString &s1, const QString &s2)
{
    ui->label->setText(boardName);
    ui->label_2->setText(s1);
    //ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(s2);
    //ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(QString());
    ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(QString());
    ui->widget_5->setStyleSheet(QString());
}

void BoardButton::setBoard(const QString &boardName,const QString &s1, const QString &s2, const QString &s3)
{
    ui->label->setText(boardName);
    ui->label_2->setText(s1);
    //ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(s2);
    //ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(s3);
    //ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(QString());
    ui->widget_5->setStyleSheet(QString());
}

void BoardButton::setBoard(const QString &boardName,const QString &s1, const QString &s2, const QString &s3, const QString &s4)
{
    ui->label->setText(boardName);
    ui->label_2->setText(s1);
    //ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(s2);
    //ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(s3);
    //ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(s4);
    //ui->widget_5->setStyleSheet(QString());
}

