#include "settime.h"
#include "ui_settime.h"
#include <QDateTime>
#include <QDateTimeEdit>
#include <QTimeZone>
#include <QDebug>
//#include <QTimer>
#include <QTimer>

SetTime::SetTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTime)
{
    ui->setupUi(this);
    dt = new QDateTime();
    *dt = QDateTime::currentDateTime();
    ui->timeEdit->setDateTime(*dt);
    ui->dateEdit->setDateTime(*dt);
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
    timer = new QTimer();
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));

}

SetTime::~SetTime()
{
    delete ui;
}

void SetTime::onTimerOut()
{
    ui->timeEdit->setDateTime(*dt);
}

void SetTime::on_timeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    ui->timeEdit->setDateTime(dateTime);
}

void SetTime::on_timeEdit_timeChanged(const QTime &time)
{
    //qDebug() << "##on_timeEdit_timeChanged:" << endl;
    ui->timeEdit->setTime(time);
}

void SetTime::on_comboBox_currentIndexChanged(const QString &arg1)
{
     //qDebug() << arg1 << endl;
    QString s1;
s1 = dt->timeZone().displayName(QTimeZone::StandardTime, QTimeZone::LongName,QLocale::system());

 qDebug() << "##start:"<<s1<<endl;
     QTimeZone *tz = new QTimeZone(arg1.toUtf8());
     //dt->setTimeZone(*tz);
    *dt =  dt->toTimeZone(*tz);
    s1 = dt->timeZone().displayName(QTimeZone::StandardTime, QTimeZone::LongName,QLocale::system());
     qDebug() << "##"<<s1<<"##"<<dt->toString() << endl;
}

