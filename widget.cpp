#include "widget.h"
#include "qpainter.h"
#include "ui_widget.h"
#include "ctrbuttonform.h"


#include <QLayout>
#include <QLabel>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //ui->setupUi(this);

  //  ctrButtonForm
   //  ui->taskLayout->addWidget(task);
    QHBoxLayout *layout = new QHBoxLayout;
    //QLabel *label = new QLabel(this);
    //QLabel *label1 = new QLabel(this);
    //label->setText("ookk");
    //label1->setText("kkoo");

    ctrButtonForm *form = new ctrButtonForm;

    QString *s = new QString("sub");
    form->addSubTitle(*s);

    //layout->addWidget(label);
    //layout->addWidget(label1);
   layout->addWidget(new ctrButtonForm());
   layout->addWidget(new ctrButtonForm());
   layout->addWidget(new ctrButtonForm());
   layout->addWidget(new ctrButtonForm());
   this->setLayout(layout);
   resize(800,480);
   setStyleSheet("background-color:blue;");

    //
   QGroupBox *groupBox = new QGroupBox(tr("Exclusive Radio Buttons"));

   QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
   QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
   QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));

   radio1->setChecked(true);

   mainLayout = new QGridLayout;
    mainLayout->addWidget(rotableGroupBox, 0, 0);
    mainLayout->addWidget(optionsGroupBox, 1, 0);
    mainLayout->addWidget(buttonBox, 2, 0);
    setLayout(mainLayout);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    QPixmap pix(":/img/green.png");

   // painter.drawPixmap(0,0, pix.width(),pix.height() ,pix );
   // painter.drawText(30,30, tr("test111"));
}
