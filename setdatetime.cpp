#include "setdatetime.h"
#include "ui_setdatetime.h"
#include <QDateTime>
#include <QDateTimeEdit>
#include <QTimeZone>
#include <QDebug>

setDateTime::setDateTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setDateTime)
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
    //QTimeZone(const QByteArray &ianaId)
}

setDateTime::~setDateTime()
{
    delete ui;
}

void setDateTime::on_timeEdit_dateTimeChanged(const QDateTime &dateTime)
{

}
