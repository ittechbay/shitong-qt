#include "setdate.h"
#include "ui_setdate.h"
#include <QDateTime>
#include <QDateTimeEdit>
#include <QTimeZone>
#include <QDebug>

setDate::setDate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setDate)
{
    ui->setupUi(this);
    ui->timeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    //QTimeZone::availableTimeZoneIds();
    //QTimeZone QTimeZone::systemTimeZone()
    //QTimeZone::QTimeZone(const QByteArray &ianaId)
    //QList<QByteArray> QTimeZone::availableTimeZoneIds()
    QList<QByteArray> li = QTimeZone::availableTimeZoneIds();


    QList<QByteArray>::const_iterator it;
    for (it = li.begin(); it != li.end(); ++it)
    {
        //qDebug() << "##test zbl##:" << it->data() << endl;
        ui->comboBox->addItem(it->data());
       //addItem
        if (it->startsWith("UTC"))
        {
            QTimeZone *tz = new QTimeZone(*it);
              //qDebug() << "##test#:"<<tz->displayName(QTimeZone::StandardTime, QTimeZone::LongName,QLocale::system()) <<"##" << tz->comment() << endl;
        }

    }



}

setDate::~setDate()
{
    delete ui;
}

void setDate::on_pushButton_5_clicked()
{
    this->destroy();
}
//QTimeZone::systemTimeZone()
//QDateTime::currentDateTime
