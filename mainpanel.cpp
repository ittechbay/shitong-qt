#include "mainpanel.h"
#include "ui_mainpanel.h"
#include "settime.h"
#include "setptp.h"
#include "setntp.h"
#include <QTableWidgetSelectionRange>
#include "statetable.h"
#include "setalarm.h"

mainPanel::mainPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainPanel)
{
    ui->setupUi(this);
    ui->frame->setBoard();
    ui->frame_2->setBoard();
    ui->frame_3->setNullBoard();
    ui->frame_4->setNullBoard();
    ui->frame_5->setNullBoard();
    ui->frame_6->setNullBoard();
    ui->frame_7->setBoard();
    ui->frame_8->setBoard();
    ui->frame_9->setBoard();
    ui->frame_10->setBoard(QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0),
                           QApplication::translate("BoardButton", "TOD", 0),
                           QApplication::translate("BoardButton", "B", 0));
    ui->frame_11->setBoard(QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0));
    ui->frame_12->setBoard(QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0),
                           QApplication::translate("BoardButton", "TOD", 0),
                           QApplication::translate("BoardButton", "B", 0));

    ui->frame_13->setNullBoard();
    ui->frame_14->setNullBoard();
    ui->frame_15->setNullBoard();
    ui->frame_16->setNullBoard();
    ui->frame_17->setNullBoard();
    ui->frame_18->setNullBoard();
    ui->frame_19->setNullBoard();
    ui->frame_20->setNullBoard();
    ui->frame_21->setNullBoard();
    ui->frame_22->setNullBoard();
    ui->frame_23->setNullBoard();

    ui->frame_24->setNullBoard();




    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: green;}");
    QTableWidgetSelectionRange *ws = new QTableWidgetSelectionRange(1,1,2,2);
    ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(0,0,0,3), true);
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,90);
    ui->tableWidget->setColumnWidth(2,50);
    ui->tableWidget->setColumnWidth(3,50);

            //ui->tableWidget->set
            //setRangeSelected(const QTableWidgetSelectionRange &range, bool select)


}

mainPanel::~mainPanel()
{
    delete ui;
}

void mainPanel::on_pushButton_clicked()
{
    SetTime w;
    w.exec();

}



void mainPanel::on_frame_3_clicked()
{
    setPTP *w = new setPTP();
    w->show();
}

void mainPanel::on_frame_4_clicked()
{
    setNTP *w = new setNTP();
    w->show();
}



void mainPanel::on_pushButton_2_clicked()
{
ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(0,0,0,3), true);
ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(1,0,1,3), false);
}

void mainPanel::on_pushButton_4_clicked()
{
    //SetAlarm w;
    //w.exec();
    ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(0,0,0,3), false);
    ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(1,0,1,3), true);
}
