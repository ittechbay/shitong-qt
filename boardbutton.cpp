#include "boardbutton.h"
#include "ui_boardbutton.h"
#include <QColor>

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

void BoardButton::setBoard()
{
    //ui->label->setText(boardName);
    ui->label_2->setText(QString());
    ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(QString());
    ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(QString());
    ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(QString());
    ui->widget_5->setStyleSheet(QString());
}

void BoardButton::setBoard(const QString &s1)
{
    //ui->label->setText(boardName);
    ui->label_2->setText(s1);
    //ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(QString());
    ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(QString());
    ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(QString());
    ui->widget_5->setStyleSheet(QString());


}

void BoardButton::setBoard(const QString &s1, const QString &s2)
{
    //ui->label->setText(boardName);
    ui->label_2->setText(s1);
    //ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(s2);
    //ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(QString());
    ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(QString());
    ui->widget_5->setStyleSheet(QString());
}

void BoardButton::setBoard(const QString &s1, const QString &s2, const QString &s3)
{
    //ui->label->setText(boardName);
    ui->label_2->setText(s1);
    //ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(s2);
    //ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(s3);
    //ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(QString());
    ui->widget_5->setStyleSheet(QString());
}

void BoardButton::setBoard(const QString &s1, const QString &s2, const QString &s3, const QString &s4)
{
    //ui->label->setText(boardName);
    ui->label_2->setText(s1);
    //ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(s2);
    //ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(s3);
    //ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(s4);
    //ui->widget_5->setStyleSheet(QString());
}

void BoardButton::setNullBoard()
{
    this->setStyleSheet(QStringLiteral("background-color: rgb(100, 120, 140);"));
    //ui->setSylesheet("background-color: rgb(100, 120, 140);");
    //ui::BoardButton->setStyleSheet(QStringLiteral("background-color: rgb(230, 230, 230);"));
    //ui->label->setText((QApplication::translate("BoardButton", "输出", 0)));
    ui->widget->setStyleSheet(QString());
    ui->label_2->setText(QString());
    ui->widget_2->setStyleSheet(QString());
    ui->label_3->setText(QString());
    ui->widget_3->setStyleSheet(QString());
    ui->label_4->setText(QString());
    ui->widget_4->setStyleSheet(QString());
    ui->label_5->setText(QString());
    ui->widget_5->setStyleSheet(QString());

    this->setEnabled(false);
}

void BoardButton::setLedColor(const Qt::GlobalColor &color)
{
    if (color == Qt::green)
        ui->widget->setStyleSheet(QString("image: url(:/new/prefix1/img/green_led_.bmp);"));
    else if (color == Qt::gray)
        ui->widget->setStyleSheet(QString("image: url(:/new/prefix1/img/gray_led_.bmp);"));
    else if (color == Qt::red)
        ui->widget->setStyleSheet(QString("image: url(:/new/prefix1/img/red_led_.bmp);"));

}

void BoardButton::setLedColor_sub1(const Qt::GlobalColor &color)
{
    if (color == Qt::green)
        ui->widget_2->setStyleSheet(QString("image: url(:/new/prefix1/img/green_led.bmp);"));
    else if (color == Qt::gray)
        ui->widget_2->setStyleSheet(QString("image: url(:/new/prefix1/img/gray_led.bmp);"));
    else if (color == Qt::red)
        ui->widget_2->setStyleSheet(QString("image: url(:/new/prefix1/img/red_led.bmp);"));
}

void BoardButton::setLedColor_sub2(const Qt::GlobalColor &color)
{
    if (color == Qt::green)
        ui->widget_3->setStyleSheet(QString("image: url(:/new/prefix1/img/green_led.bmp);"));
    else if (color == Qt::gray)
        ui->widget_3->setStyleSheet(QString("image: url(:/new/prefix1/img/gray_led.bmp);"));
    else if (color == Qt::red)
        ui->widget_3->setStyleSheet(QString("image: url(:/new/prefix1/img/red_led.bmp);"));
}

void BoardButton::setLedColor_sub3(const Qt::GlobalColor &color)
{
    if (color == Qt::green)
        ui->widget_4->setStyleSheet(QString("image: url(:/new/prefix1/img/green_led.bmp);"));
    else if (color == Qt::gray)
        ui->widget_4->setStyleSheet(QString("image: url(:/new/prefix1/img/gray_led.bmp);"));
    else if (color == Qt::red)
        ui->widget_4->setStyleSheet(QString("image: url(:/new/prefix1/img/red_led.bmp);"));
}

void BoardButton::setLedColor_sub4(const Qt::GlobalColor &color)
{
    if (color == Qt::green)
        ui->widget_5->setStyleSheet(QString("image: url(:/new/prefix1/img/green_led.bmp);"));
    else if (color == Qt::gray)
        ui->widget_5->setStyleSheet(QString("image: url(:/new/prefix1/img/gray_led.bmp);"));
    else if (color == Qt::red)
        ui->widget_5->setStyleSheet(QString("image: url(:/new/prefix1/img/red_led.bmp);"));
}

void BoardButton::mousePressEvent(QMouseEvent *event)
{
    this->setFrameShadow(QFrame::Sunken);

}

void BoardButton::mouseReleaseEvent(QMouseEvent *event)
{
    this->setFrameShadow(QFrame::Raised);
    emit clicked();
}







void BoardButton::on_BoardButton_clicked()
{

}
