#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->frame->setBoard(QApplication::translate("BoardButton", "电源A", 0));
    ui->frame_2->setBoard(QApplication::translate("BoardButton", "电源B", 0));
    ui->frame_3->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_4->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_5->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_6->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_7->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_8->setBoard(QApplication::translate("BoardButton", "GNSS", 0));
    ui->frame_9->setBoard(QApplication::translate("BoardButton", "外监", 0));
    ui->frame_10->setBoard(QApplication::translate("BoardButton", "时频A", 0),
                           QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0),
                           QApplication::translate("BoardButton", "TOD", 0),
                           QApplication::translate("BoardButton", "B", 0));
    ui->frame_11->setBoard(QApplication::translate("BoardButton", "切换", 0),
                           QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0));
    ui->frame_12->setBoard(QApplication::translate("BoardButton", "时频A", 0),
                           QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0),
                           QApplication::translate("BoardButton", "TOD", 0),
                           QApplication::translate("BoardButton", "B", 0));

    ui->frame_13->setBoard(QApplication::translate("BoardButton", "电源A", 0));
    ui->frame_14->setBoard(QApplication::translate("BoardButton", "电源B", 0));
    ui->frame_15->setNullBoard();
    ui->frame_16->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_17->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_18->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_19->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_20->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_21->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_22->setBoard(QApplication::translate("BoardButton", "输出", 0));
    ui->frame_23->setBoard(QApplication::translate("BoardButton", "输出", 0));

    ui->frame_24->setBoard(QApplication::translate("BoardButton", "分配", 0),
                           QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0),
                           QApplication::translate("BoardButton", "TOD", 0),
                           QApplication::translate("BoardButton", "B", 0));




}

Widget::~Widget()
{
    delete ui;
}




