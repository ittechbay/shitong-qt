#include "clock.h"
#include "qpainter.h"
#include "qmath.h"

FTSClock::FTSClock(QWidget *parent) : QWidget(parent)
{

}

void FTSClock::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);


    painter.setPen(Qt::white);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    //painter.drawEclipse(0,0,30,190);
    painter.drawEllipse(QPoint(50,50), 50, 50);
    minuteArrawPos = 30;
    painter.setPen(Qt::red);
    //painter.drawLine(50,50,60,60);
    painter.drawLine(50,50, 50.0+50.0*sin(2.0*3.14*minuteArrawPos/360), 50.0-50.0*cos(2.0*3.14*minuteArrawPos/360));
    minuteArrawPos = 90;
    painter.drawLine(50,50, 50.0+50.0*sin(2.0*3.14*minuteArrawPos/360), 50.0-50.0*cos(2.0*3.14*minuteArrawPos/360));
    minuteArrawPos = 100;
    painter.drawLine(50,50, 50.0+50.0*sin(2.0*3.14*minuteArrawPos/360), 50.0-50.0*cos(2.0*3.14*minuteArrawPos/360));
    minuteArrawPos = 180;
    painter.drawLine(50,50, 50.0+50.0*sin(2.0*3.14*minuteArrawPos/360), 50.0-50.0*cos(2.0*3.14*minuteArrawPos/360));
    minuteArrawPos = 190;
    painter.drawLine(50,50, 50.0+50.0*sin(2.0*3.14*minuteArrawPos/360), 50.0-50.0*cos(2.0*3.14*minuteArrawPos/360));
    minuteArrawPos = 270;
    painter.drawLine(50,50, 50.0+50.0*sin(2.0*3.14*minuteArrawPos/360), 50.0-50.0*cos(2.0*3.14*minuteArrawPos/360));
    minuteArrawPos = 280;
    painter.drawLine(50,50, 50.0+50.0*sin(2.0*3.14*minuteArrawPos/360), 50.0-50.0*cos(2.0*3.14*minuteArrawPos/360));
    hourArrawPos = 300;
    painter.setPen(Qt::black);
    painter.drawLine(50,50, 50.0+30.0*sin(2.0*3.14*hourArrawPos/360), 50.0-30.0*cos(2.0*3.14*hourArrawPos/360));


}

void FTSClock::setHourArrawPos(int n)
{
    hourArrawPos = n;

}

void FTSClock::setMinuteArrawPos(int n)
{
    minuteArrawPos = n;
}
