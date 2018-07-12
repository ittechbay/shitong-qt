#include "clock.h"
#include "qpainter.h"

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
}
