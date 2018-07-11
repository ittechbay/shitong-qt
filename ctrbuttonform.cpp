#include "ctrbuttonform.h"
#include "qpainter.h"
#include "ui_ctrbuttonform.h"

ctrButtonForm::ctrButtonForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ctrButtonForm)
{
    //ui->setupUi(this);
    //ledMain->load(":/img/green.png");
    setGeometry(0,0,30,165);
    setStyleSheet("background-color:white;");
}

ctrButtonForm::~ctrButtonForm()
{
    delete ui;
}

void ctrButtonForm::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
 //   QPixmap *pix = led.at(0);

 //   painter.drawPixmap(0,0, pix->width(),pix->height() ,*pix);

 //   painter.drawText(30,30, tr("test111"));

    //draw main led
    painter.setPen(Qt::white);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawRect(0,0,30,160);


    painter.setFont(QFont("宋体",7, QFont::Normal));
    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(QPoint(15, 15), 8,8);

    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(QPoint(15, 40), 5,5);
    painter.setPen(Qt::black);
    painter.drawText(QRect(0,45, 30,10), Qt::AlignCenter, tr("10MHz"), NULL);

    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(QPoint(15, 70), 5,5);
    painter.setPen(Qt::black);
    painter.drawText(QRect(0,75, 30,10), Qt::AlignCenter, tr("1pps"), NULL);
    //painter.setFont(QFont("Arial", 30));
    //painter.drawText

    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(QPoint(15, 100), 5,5);
    painter.setPen(Qt::black);
    painter.drawText(QRect(0,105, 30,10), Qt::AlignCenter, tr("TOD"), NULL);

    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(QPoint(15, 130), 5,5);
    painter.setPen(Qt::black);
    painter.drawText(QRect(0,135, 30,10), Qt::AlignCenter, tr("B"), NULL);
    painter.setFont(QFont("宋体",7, QFont::Bold));
    painter.drawText(QRect(0,150, 30,10), Qt::AlignCenter, tr("切换板"), NULL);
}

void ctrButtonForm::addSubTitle(QString &s)
{
    subTitle.append(s);
    led.append(new QPixmap(":/img/green.png"));
}

void ctrButtonForm::addSubLed(QPixmap *pixmap)
{
    led.append(pixmap);
}
