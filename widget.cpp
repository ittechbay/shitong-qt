#include "widget.h"
#include "qpainter.h"
#include "ctrbuttonform.h"
#include "clock.h"




#include <QLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QDateTimeEdit>


#if 0
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{


   QGridLayout *mainLayout = new QGridLayout;
   //ctrButtonForm *form = new ctrButtonForm;





   this->setLayout(mainLayout);
   resize(800,480);

    setStyleSheet("background-color:blue;");

   QGroupBox *groupBox0 = new QGroupBox(tr("主机箱"));
   QGroupBox *groupBox1 = new QGroupBox(tr("分配机箱"));
   QHBoxLayout *hbox0 = new QHBoxLayout;
   QHBoxLayout *hbox1 = new QHBoxLayout;
  QString s(tr("切换B"));
    ctrButtonForm *but0 = new ctrButtonForm(s);
    QString but0sub0(tr("sub0"));
    QString but0sub1(tr("sub1"));
    QString but0sub2(tr("sub2"));
    QString but0sub3(tr("sub3"));
    but0->addSubTitle(but0sub0);
    but0->addSubTitle(but0sub1);
    but0->addSubTitle(but0sub2);
    but0->addSubTitle(but0sub3);
    ctrButtonForm *but1 = new ctrButtonForm(s);
    ctrButtonForm *but2 = new ctrButtonForm(s);
    ctrButtonForm *but3 = new ctrButtonForm(s);
    ctrButtonForm *but4 = new ctrButtonForm(s);
    ctrButtonForm *but5 = new ctrButtonForm(s);
    ctrButtonForm *but6 = new ctrButtonForm(s);
    ctrButtonForm *but7 = new ctrButtonForm(s);
    ctrButtonForm *but8 = new ctrButtonForm(s);
    ctrButtonForm *but9 = new ctrButtonForm(s);
    ctrButtonForm *but10 = new ctrButtonForm(s);
    ctrButtonForm *but11 = new ctrButtonForm(s);
    groupBox0->setMinimumSize(600,210);
    groupBox0->setStyleSheet("color:white;");


    hbox0->addWidget(but0);
    hbox0->addWidget(but1);
    hbox0->addWidget(but2);
    hbox0->addWidget(but3);
    hbox0->addWidget(but4);
    hbox0->addWidget(but5);
    hbox0->addWidget(but6);
    hbox0->addWidget(but7);
    hbox0->addWidget(but8);
    hbox0->addWidget(but9);
    hbox0->addWidget(but10);
    hbox0->addWidget(but11);


   // vbox->addStretch(1);
    groupBox0->setLayout(hbox0);
    ///////////////
    /// \brief groupBox1
    QString s1(tr("切换B"));
    ctrButtonForm *but00 = new ctrButtonForm(s);
    QString but1sub0(tr("sub0"));

    but00->addSubTitle(but0sub0);


   // ctrButtonForm *but10 = new ctrButtonForm(s);


    groupBox1->setMinimumSize(600,210);
    groupBox1->setStyleSheet("color:white;");





     // vbox->addStretch(1);
      groupBox1->setLayout(hbox1);
      ////////////////////////////////
      /// \brief groupBox1
      ///



    groupBox1->setStyleSheet("color:white;");
    QGroupBox *groupBox2 = new QGroupBox();
    groupBox2->setStyleSheet("color:white;");
    //groupBox2->resize(QSize(30,30));

    QVBoxLayout *vLayout0 = new QVBoxLayout;
    QVBoxLayout *vLayout1 = new QVBoxLayout;
    QGroupBox *groupBox3 = new QGroupBox(); //tr("报警")
    QGroupBox *groupBox4 = new QGroupBox(); //tr("精度")
    QGroupBox *groupBox5 = new QGroupBox(); //版本
    groupBox3->setMinimumSize(150,90);
    groupBox4->setMinimumSize(150,50);
    groupBox5->setMinimumSize(150,50);



  //vLayout0->addItem(verticalSpacer);

   //vLayout0->addWidget(groupBox2);

    vLayout1->addWidget(groupBox3,1, Qt::AlignBottom);
    vLayout1->addWidget(groupBox4,1,  Qt::AlignBottom);
    vLayout1->addWidget(groupBox5,1,  Qt::AlignBottom);

    mainLayout->addWidget(groupBox0, 0, 0);
    mainLayout->addWidget(groupBox1, 1, 0);
    mainLayout->addWidget(groupBox2, 0, 1,Qt::AlignBottom);
    mainLayout->addLayout(vLayout1, 1, 1);

    // groupBox2->setGeometry(QRect(10, 10, 100, 100));
    groupBox2->setMinimumSize(150,220);
    //groupBox2->setMaximumSize(150,190);
}
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{

   resize(800,480);
   setStyleSheet("background-color:blue;");
   QGridLayout *mainLayout = new QGridLayout;
   this->setLayout(mainLayout);


   //////
   QGroupBox *groupBox0 = new QGroupBox(tr("主机箱"));
   //groupBox0->setMaximumSize(200,210);
   groupBox0->setStyleSheet("color:white;");
   QHBoxLayout *hbox0 = new QHBoxLayout;
   groupBox0->setLayout(hbox0);

     ctrButtonForm *but00 = new ctrButtonForm(tr("电源A"));
     hbox0->addWidget(but00);
     ctrButtonForm *but01 = new ctrButtonForm(QString(tr("电源B")));
     hbox0->addWidget(but01);
     ctrButtonForm *but02 = new ctrButtonForm(QString(tr("输出")));
     hbox0->addWidget(but02);
     ctrButtonForm *but03 = new ctrButtonForm(QString(tr("输出")));
     hbox0->addWidget(but03);
     ctrButtonForm *but04 = new ctrButtonForm(QString(tr("输出")));
     hbox0->addWidget(but04);
     ctrButtonForm *but05 = new ctrButtonForm(QString(tr("输出")));
     hbox0->addWidget(but05);
     ctrButtonForm *but06 = new ctrButtonForm(QString(tr("输出")));
     hbox0->addWidget(but06);
     ctrButtonForm *but07 = new ctrButtonForm(QString(tr("GNSS")));
     but07->addSubTitle(QString(tr("status")));
     hbox0->addWidget(but07);
     ctrButtonForm *but08 = new ctrButtonForm(QString(tr("外监板")));
     but08->addSubTitle(QString(tr("status")));
     hbox0->addWidget(but08);
     ctrButtonForm *but09 = new ctrButtonForm(QString(tr("时频A")));
     but09->addSubTitle(QString(tr("10M")));
     but09->addSubTitle(QString(tr("1pps")));
     but09->addSubTitle(QString(tr("TOD")));
     but09->addSubTitle(QString(tr("B")));
     hbox0->addWidget(but09);
     ctrButtonForm *but10 = new ctrButtonForm(QString(tr("切换")));
     but10->addSubTitle(QString(tr("10M")));
     but10->addSubTitle(QString(tr("1pps")));
     hbox0->addWidget(but10);
     ctrButtonForm *but11 = new ctrButtonForm(QString(tr("时频B")));
     but11->addSubTitle(QString(tr("10M")));
     but11->addSubTitle(QString(tr("1pps")));
     but11->addSubTitle(QString(tr("TOD")));
     but11->addSubTitle(QString(tr("B")));
     hbox0->addWidget(but11);
     but00->addSubTitle(QString(tr("sub0")));
     groupBox0->setMinimumSize(600,210);



   ///
    QGroupBox *groupBox1 = new QGroupBox(tr("分配机箱"));
   //groupBox1->setMinimumSize(600,210);
   groupBox1->setStyleSheet("color:white;");
   QHBoxLayout *hbox1 = new QHBoxLayout;
   groupBox1->setLayout(hbox1);

   ctrButtonForm *but10d = new ctrButtonForm(QString(tr("电源A")));
   hbox1->addWidget(but10d);
   ctrButtonForm *but11d = new ctrButtonForm(QString(tr("电源B")));
   hbox1->addWidget(but11d);
   ctrButtonForm *but12 = new ctrButtonForm(QString(tr("输出")));
   hbox1->addWidget(but12);
   ctrButtonForm *but13 = new ctrButtonForm(QString(tr("输出")));
   hbox1->addWidget(but13);
   ctrButtonForm *but14 = new ctrButtonForm(QString(tr("输出")));
   hbox1->addWidget(but14);
   ctrButtonForm *but15 = new ctrButtonForm(QString(tr("输出")));
   hbox1->addWidget(but15);
   ctrButtonForm *but16 = new ctrButtonForm(QString(tr("输出")));
   hbox1->addWidget(but16);
   ctrButtonForm *but17 = new ctrButtonForm(QString(tr("输出")));
   hbox1->addWidget(but17);
   ctrButtonForm *but18 = new ctrButtonForm(QString(tr("输出")));
   hbox1->addWidget(but18);
   ctrButtonForm *but19 = new ctrButtonForm(QString(tr("输出")));
   hbox1->addWidget(but19);
   ctrButtonForm *but20 = new ctrButtonForm(QString(tr("输出")));
   hbox1->addWidget(but20);
   ctrButtonForm *but21 = new ctrButtonForm(QString(tr("分配板")));
   but21->addSubTitle(QString(tr("10M")));
   but21->addSubTitle(QString(tr("1pps")));
   but21->addSubTitle(QString(tr("TOD")));
   but21->addSubTitle(QString(tr("B")));
   hbox1->addWidget(but21);

   ///
   /// \brief groupBox2
   ///
   QVBoxLayout *vbox0 = new QVBoxLayout;
   QGroupBox *groupBox2 = new QGroupBox(tr("时间"));
   groupBox2->setMinimumHeight(150);
   groupBox2->setStyleSheet("color:white;");

   QVBoxLayout *vbox00 = new QVBoxLayout;
   groupBox2->setLayout(vbox00);
   QTimeEdit *timeEdit = new QTimeEdit();
   QDateTimeEdit  *dateEdit = new QDateTimeEdit ();

    vbox00->addWidget(timeEdit);
    vbox00->addWidget(dateEdit);
    timeEdit->setCalendarPopup(true);
    dateEdit->setCalendarPopup(true);



    QGroupBox *groupBox3 = new QGroupBox(tr("精度"));
    groupBox3->setMinimumHeight(60);
    groupBox3->setStyleSheet("color:white;");
    vbox0->addWidget(groupBox2);
    vbox0->addWidget(groupBox3);




    //QLabel *label20 = new QLabel(tr("12:10:11"));
    //vbox0->addWidget(label20);
    //QLabel *label21 = new QLabel(tr("1998/10/11"));
    //vbox0->addWidget(label21);

    //
    QVBoxLayout *vbox1 = new QVBoxLayout;
    QGroupBox *groupBox4 = new QGroupBox(tr("报警"));
    groupBox4->setMinimumHeight(130);
    groupBox4->setStyleSheet("color:white;");


    QGroupBox *groupBox5 = new QGroupBox();
    groupBox5->setStyleSheet("color:white;");

    vbox1->addWidget(groupBox4);
    vbox1->addWidget(groupBox5);

    //
    mainLayout->addWidget(groupBox0, 0, 0);
    mainLayout->addWidget(groupBox1, 1, 0);
    mainLayout->addLayout(vbox0, 0, 1);
    mainLayout->addLayout(vbox1, 1, 1);



}

Widget::~Widget()
{
    //delete ui;
}

void Widget::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    QPixmap pix(":/img/green.png");

   // painter.drawPixmap(0,0, pix.width(),pix.height() ,pix );
   // painter.drawText(30,30, tr("test111"));
}
