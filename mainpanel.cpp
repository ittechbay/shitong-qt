//主控界面
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "mainpanel.h"
#include "ui_mainpanel.h"
#include "settime.h"
#include "setptp.h"
#include "setntp.h"
#include <QTableWidgetSelectionRange>
#include "statetable.h"
#include "setalarm.h"
#include "ftsCan.h"
#include <linux/can.h>
#include <QDebug>

#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>



mainPanel::mainPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainPanel)
{
    ui->setupUi(this);
    ui->frame_0->setBoard();
    ui->frame_1->setBoard();
    ui->frame_2->setNullBoard();
    ui->frame_3->setNullBoard();
    ui->frame_4->setNullBoard();
    ui->frame_5->setNullBoard();
    ui->frame_6->setBoard();
    ui->frame_7->setBoard();
    ui->frame_8->setBoard();
    ui->frame_9->setBoard(QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0),
                           QApplication::translate("BoardButton", "TOD", 0),
                           QApplication::translate("BoardButton", "B", 0));
    ui->frame_10->setBoard(QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0));
    ui->frame_11->setBoard(QApplication::translate("BoardButton", "10M", 0),
                           QApplication::translate("BoardButton", "1pps", 0),
                           QApplication::translate("BoardButton", "TOD", 0),
                           QApplication::translate("BoardButton", "B", 0));

    ui->frame_12->setBoard();
    ui->frame_13->setBoard();
    ui->frame_14->setNullBoard();
    ui->frame_15->setNullBoard();
    ui->frame_16->setNullBoard();
    ui->frame_17->setNullBoard();
    ui->frame_18->setNullBoard();
    ui->frame_19->setNullBoard();
    ui->frame_20->setNullBoard();
    ui->frame_21->setNullBoard();
    ui->frame_22->setNullBoard();
    ui->frame_23->setBoard();

    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
    ui->tableWidget->setStyleSheet("QTableWidget {selection-background-color: red;font: 8pt \"Sans Serif\";selection-color: green;}");
    ui->tableWidget->setStyleSheet(QLatin1String("selection-background-color: red;selection-color: green;\n"
    "font: 8pt \"Sans Serif\";\n"
    ""));


    ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(1,0,1,4), true);
    //ui->tableWidget->setColumnWidth(0,50);
    //ui->tableWidget->setColumnWidth(1,90);
    //ui->tableWidget->setColumnWidth(2,50);
    //ui->tableWidget->setColumnWidth(3,50);

            //ui->tableWidget->set
            //setRangeSelected(const QTableWidgetSelectionRange &range, bool select)
    ui->tab_2->setEnabled(false);

    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOutMain()));
    //timer->start();
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut0()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut1()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut2()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut3()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut4()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut5()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut6()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut7()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut8()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut9()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut10()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut11()));
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
    SetAlarm w;
    w.exec();
    //ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(0,0,0,3), false);
    //ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(1,0,1,3), true);
}



void mainPanel::onTimerOutMain()
{
    ;
}

void mainPanel::onTimerOut0()
{
    static int a = 0;
    a++;
    unsigned int error;
    int ret;
    ret = fts_can_poll(0, FTS_BOARD_TYPE_POWER, &error);
    if (ret == FTS_CAN_NO_RESPONSE)
    {
        qDebug() << "onTimerOut0 fts_can_poll no response!"  << endl;
    }
    else
    {
        if (error == FTS_CAN_CODE_OK)
            ui->frame_0->setLedColor(Qt::green);
        else
            ui->frame_0->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut1()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(1, FTS_BOARD_TYPE_POWER, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        qDebug() << "onTimerOut0 fts_can_poll no response!"  << endl;
    }
    else
    {
        if (error == FTS_CAN_CODE_OK)
            ui->frame_1->setLedColor(Qt::green);
        else
            ui->frame_1->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut2()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;

    ret = fts_can_poll(2, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut0 fts_can_poll no response!"  << endl;
        ui->frame_2->setNullBoard();
        ui->label_2->setText(QApplication::translate("mainPanel", "输出", 0));
    }
    else
    {
        switch(board_type)
        {
        case FTS_BOARD_TYPE_B:
            ui->frame_2->setBoard(QApplication::translate("BoardButton", "10M", 0),
                              QApplication::translate("BoardButton", "1pps", 0),
                              QApplication::translate("BoardButton", "B-AC", 0),
                              QApplication::translate("BoardButton", "B-DC", 0));
            ui->label_2->setText(QApplication::translate("mainPanel", "B", 0));
            break;
        case FTS_BOARD_TYPE_10M:
            ui->frame_2->setBoard(QApplication::translate("BoardButton", "10M-1", 0),
                              QApplication::translate("BoardButton", "10M-2", 0),
                              QApplication::translate("BoardButton", "10M-3", 0));
            ui->label_2->setText(QApplication::translate("mainPanel", "10M", 0));
            break;
        case FTS_BOARD_TYPE_NTP:
            ui->frame_2->setBoard();
            ui->label_2->setText(QApplication::translate("mainPanel", "NTP", 0));
            break;
        case FTS_BOARD_TYPE_PTP:
            ui->frame_2->setBoard();
            ui->label_2->setText(QApplication::translate("mainPanel", "PTP", 0));
            break;
        default:
            break;
        }

        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_2->setLedColor(Qt::green);
        else
            ui->frame_2->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut3()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(3, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut0 fts_can_poll no response!"  << endl;
        ui->frame_3->setNullBoard();
        ui->label_3->setText(QApplication::translate("mainPanel", "输出", 0));
    }
    else
    {
        switch(board_type)
        {
        case FTS_BOARD_TYPE_B:
            ui->frame_3->setBoard(QApplication::translate("BoardButton", "10M", 0),
                              QApplication::translate("BoardButton", "1pps", 0),
                              QApplication::translate("BoardButton", "B-AC", 0),
                              QApplication::translate("BoardButton", "B-DC", 0));
            ui->label_3->setText(QApplication::translate("mainPanel", "B", 0));
            break;
        case FTS_BOARD_TYPE_10M:
            ui->frame_3->setBoard(QApplication::translate("BoardButton", "10M-1", 0),
                              QApplication::translate("BoardButton", "10M-2", 0),
                              QApplication::translate("BoardButton", "10M-3", 0));
            ui->label_3->setText(QApplication::translate("mainPanel", "10M", 0));
            break;
        case FTS_BOARD_TYPE_NTP:
            ui->frame_3->setBoard();
            ui->label_3->setText(QApplication::translate("mainPanel", "NTP", 0));
            break;
        case FTS_BOARD_TYPE_PTP:
            ui->frame_3->setBoard();
            ui->label_3->setText(QApplication::translate("mainPanel", "PTP", 0));
            break;
        default:
            break;
        }

        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_3->setLedColor(Qt::green);
        else
            ui->frame_3->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut4()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(4, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut0 fts_can_poll no response!"  << endl;
        ui->frame_4->setNullBoard();
        ui->label_4->setText(QApplication::translate("mainPanel", "输出", 0));
    }
    else
    {
        switch(board_type)
        {
        case FTS_BOARD_TYPE_B:
            ui->frame_4->setBoard(QApplication::translate("BoardButton", "10M", 0),
                              QApplication::translate("BoardButton", "1pps", 0),
                              QApplication::translate("BoardButton", "B-AC", 0),
                              QApplication::translate("BoardButton", "B-DC", 0));
            ui->label_4->setText(QApplication::translate("mainPanel", "B", 0));
            break;
        case FTS_BOARD_TYPE_10M:
            ui->frame_4->setBoard(QApplication::translate("BoardButton", "10M-1", 0),
                              QApplication::translate("BoardButton", "10M-2", 0),
                              QApplication::translate("BoardButton", "10M-3", 0));
            ui->label_4->setText(QApplication::translate("mainPanel", "10M", 0));
            break;
        case FTS_BOARD_TYPE_NTP:
            ui->frame_4->setBoard();
            ui->label_4->setText(QApplication::translate("mainPanel", "PTP", 0));
            break;
        case FTS_BOARD_TYPE_PTP:
            ui->frame_4->setBoard();
            ui->label_4->setText(QApplication::translate("mainPanel", "PTP", 0));
            break;
        default:
            break;
        }

        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_4->setLedColor(Qt::green);
        else
            ui->frame_4->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut5()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(5, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut0 fts_can_poll no response!"  << endl;
        ui->frame_5->setNullBoard();
        ui->label_5->setText(QApplication::translate("mainPanel", "输出", 0));
    }
    else
    {
        switch(board_type)
        {
        case FTS_BOARD_TYPE_B:
            ui->frame_5->setBoard(QApplication::translate("BoardButton", "10M", 0),
                              QApplication::translate("BoardButton", "1pps", 0),
                              QApplication::translate("BoardButton", "B-AC", 0),
                              QApplication::translate("BoardButton", "B-DC", 0));
            ui->label_5->setText(QApplication::translate("mainPanel", "B", 0));
            break;
        case FTS_BOARD_TYPE_10M:
            ui->frame_5->setBoard(QApplication::translate("BoardButton", "10M-1", 0),
                              QApplication::translate("BoardButton", "10M-2", 0),
                              QApplication::translate("BoardButton", "10M-3", 0));
            ui->label_5->setText(QApplication::translate("mainPanel", "10M", 0));
            break;
        case FTS_BOARD_TYPE_NTP:
            ui->frame_5->setBoard();
            ui->label_5->setText(QApplication::translate("mainPanel", "NTP", 0));
            break;
        case FTS_BOARD_TYPE_PTP:
            ui->frame_5->setBoard();
            ui->label_5->setText(QApplication::translate("mainPanel", "PTP", 0));
            break;
        default:
            break;
        }

        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_5->setLedColor(Qt::green);
        else
            ui->frame_5->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut6()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(6, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut0 fts_can_poll no response!"  << endl;
        ui->frame_6->setNullBoard();
        ui->label_6->setText(QApplication::translate("mainPanel", "参考源", 0));
    }
    else
    {
        switch(board_type)
        {
        case FTS_BOARD_TYPE_GNSS:
            ui->frame_6->setBoard();
            ui->label_6->setText(QApplication::translate("mainPanel", "GNSS", 0));
            break;
        case FTS_BOARD_TYPE_OUTER_REF:
            ui->frame_6->setBoard();
            ui->label_6->setText(QApplication::translate("mainPanel", "外参考", 0));
            break;
        default:
            break;
        }

        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_6->setLedColor(Qt::green);
        else
            ui->frame_6->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut7()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(7, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut0 fts_can_poll no response!"  << endl;
        ui->frame_7->setNullBoard();
        ui->label_7->setText(QApplication::translate("mainPanel", "参考源", 0));
    }
    else
    {
        switch(board_type)
        {
        case FTS_BOARD_TYPE_GNSS:
            ui->frame_7->setBoard();
            ui->label_7->setText(QApplication::translate("mainPanel", "GNSS", 0));

            break;
        case FTS_BOARD_TYPE_OUTER_REF:
            ui->frame_7->setBoard();
            ui->label_7->setText(QApplication::translate("mainPanel", "外参考", 0));
            break;
        default:
            break;
        }

        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_7->setLedColor(Qt::green);
        else
            ui->frame_7->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut8()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(8, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut0 fts_can_poll no response!"  << endl;
        ui->frame_8->setNullBoard();
        ui->label_8->setText(QApplication::translate("mainPanel", "参考源", 0));
    }
    else
    {
        switch(board_type)
        {
        case FTS_BOARD_TYPE_GNSS:
            ui->frame_8->setBoard();
            ui->label_8->setText(QApplication::translate("mainPanel", "GNSS", 0));
            break;
        case FTS_BOARD_TYPE_OUTER_REF:
            ui->frame_8->setBoard();
            ui->label_8->setText(QApplication::translate("mainPanel", "外参考", 0));
            break;
        default:
            break;
        }

        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_8->setLedColor(Qt::green);
        else
            ui->frame_8->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut9()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(9, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut9 fts_can_poll no response!"  << endl;
        ui->frame_9->setLedColor(Qt::red);
    }
    else
    {
        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_9->setLedColor(Qt::green);
        else
            ui->frame_9->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut10()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(10, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut9 fts_can_poll no response!"  << endl;
        ui->frame_10->setLedColor(Qt::red);
    }
    else
    {
        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_10->setLedColor(Qt::green);
        else
            ui->frame_10->setLedColor(Qt::red);
    }
}

void mainPanel::onTimerOut11()
{
    static int a = 0;
    a++;
    unsigned int error;
    unsigned int board_type;
    int ret;
    ret = fts_can_poll(11, &board_type, &error);
    if (ret == FTS_CAN_CODE_BOARD_NO_RESPONSE)
    {
        //qDebug() << "onTimerOut9 fts_can_poll no response!"  << endl;
        ui->frame_11->setLedColor(Qt::red);
    }
    else
    {
        if (error == FTS_CAN_CODE_BOARD_OK)
            ui->frame_11->setLedColor(Qt::green);
        else
            ui->frame_11->setLedColor(Qt::red);
    }
}

BoardButton * mainPanel::toButtonFrame(int slot)
{
    switch (slot)
    {
    case 0:
        return ui->frame_0;
    break;
    case 1:
        return ui->frame_1;
    break;
    case 2:
        return ui->frame_2;
    break;
    case 3:
        return ui->frame_3;
    break;
    case 4:
        return ui->frame_4;
    break;
    case 5:
        return ui->frame_5;
    break;
    case 6:
        return ui->frame_6;
    break;
    case 7:
        return ui->frame_7;
    break;
    case 8:
        return ui->frame_8;
    break;
    case 9:
        return ui->frame_9;
    break;
    case 10:
        return ui->frame_10;
    break;
    case 11:
        return ui->frame_11;
    break;
    case 12:
        return ui->frame_12;
    break;
    case 13:
        return ui->frame_13;
    break;
    case 14:
        return ui->frame_14;
    break;
    case 15:
        return ui->frame_15;
    break;
    case 16:
        return ui->frame_16;
    break;
    case 17:
        return ui->frame_17;
    break;
    case 18:
        return ui->frame_18;
    break;
    case 19:
        return ui->frame_19;
    break;
    case 20:
        return ui->frame_20;
    break;
    case 21:
        return ui->frame_21;
    break;
    case 22:
        return ui->frame_22;
    break;
    case 23:
        return ui->frame_23;
    break;


    }

}

QLabel * mainPanel::toButtonLabel(int slot)
{
    switch (slot)
    {
    case 0:
        return ui->label_0;
    break;
    case 1:
        return ui->label_1;
    break;
    case 2:
        return ui->label_2;
    break;
    case 3:
        return ui->label_3;
    break;
    case 4:
        return ui->label_4;
    break;
    case 5:
        return ui->label_5;
    break;
    case 6:
        return ui->label_6;
    break;
    case 7:
        return ui->label_7;
    break;
    case 8:
        return ui->label_8;
    break;
    case 9:
        return ui->label_9;
    break;
    case 10:
        return ui->label_10;
    break;
    case 11:
        return ui->label_11;
    break;
    case 12:
        return ui->label_12;
    break;
    case 13:
        return ui->label_13;
    break;
    case 14:
        return ui->label_14;
    break;
    case 15:
        return ui->label_15;
    break;
    case 16:
        return ui->label_16;
    break;
    case 17:
        return ui->label_17;
    break;
    case 18:
        return ui->label_18;
    break;
    case 19:
        return ui->label_19;
    break;
    case 20:
        return ui->label_20;
    break;
    case 21:
        return ui->label_21;
    break;
    case 22:
        return ui->label_22;
    break;
    case 23:
        return ui->label_23;
    break;
    }
    return NULL;
}

#if 1
void mainPanel::cmdProcessTask()
{
    int sock;
    struct sockaddr_can addr;
    struct ifreq ifr;
    int ret;
    int recv_own_msgs = 0; //set loop back:  1 enable 0 disable
    struct can_frame recv_frame;

#if 1//zbl test
    return;
#endif
    sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if(sock < 0) {
        printf("fts_can_send_and_recv socket error\n");
        exit(1);
    }

    addr.can_family = AF_CAN;
    strcpy(ifr.ifr_name, "can0"); //?? which can should i use


    ret = ioctl(sock, SIOCGIFINDEX, &ifr);  //get index
    if(ret && ifr.ifr_ifindex == 0)
    {
        printf("Can't get interface index for can0, code= %d, can0 ifr_ifindex value: %d, name: %s\n", ret, ifr.ifr_ifindex, ifr.ifr_name);
        ::close(sock);
        exit(1);
    }

    printf("%s can_ifindex = %x\n",ifr.ifr_name,ifr.ifr_ifindex);
    addr.can_ifindex = ifr.ifr_ifindex;

    //ioctl(sock,SIOCGIFNAME,&ifr);
    //printf("ret = %d can0 can_ifname = %s\n",ret,ifr.ifr_name);

    setsockopt(sock, SOL_CAN_BASE + CAN_RAW, 0x4, &recv_own_msgs, sizeof(recv_own_msgs)); //???????
    if (bind(sock,(struct sockaddr*)&addr,sizeof(addr))<0) {
        printf("bind error\n");
        ::close(sock);
        exit(1);
    }

    while(true)
    {
        ret = read(sock, (void *)&recv_frame, sizeof(struct can_frame));
        int cmd = recv_frame.data[0];
        int slot = (int)recv_frame.data[1];
        int boardtype = (int)recv_frame.data[2];
        int err = recv_frame.data[3];
        switch (cmd)
        {
        case FTS_CAN_CODE_POWERUP:
            switch (boardtype) {
            case FTS_BOARD_TYPE_NTP:
                toButtonFrame(slot)->setBoard(QApplication::translate("BoardButton", "10M", 0),
                                              QApplication::translate("BoardButton", "1pps", 0),
                                              QApplication::translate("BoardButton", "B-AC", 0),
                                              QApplication::translate("BoardButton", "B-DC", 0));

                toButtonLabel(slot)->setText(QApplication::translate("mainPanel", "NTP", 0));

                break;
            case FTS_BOARD_TYPE_PTP:
                toButtonFrame(slot)->setBoard(QApplication::translate("BoardButton", "10M", 0),
                                              QApplication::translate("BoardButton", "1pps", 0),
                                              QApplication::translate("BoardButton", "B-AC", 0),
                                              QApplication::translate("BoardButton", "B-DC", 0));

                toButtonLabel(slot)->setText(QApplication::translate("mainPanel", "PTP", 0));
                break;
            case FTS_BOARD_TYPE_B:
                toButtonFrame(slot)->setBoard(QApplication::translate("BoardButton", "10M", 0),
                                              QApplication::translate("BoardButton", "1pps", 0),
                                              QApplication::translate("BoardButton", "B-AC", 0),
                                              QApplication::translate("BoardButton", "B-DC", 0));

                toButtonLabel(slot)->setText(QApplication::translate("mainPanel", "B", 0));
                break;
            case FTS_BOARD_TYPE_10M:
                toButtonFrame(slot)->setBoard(QApplication::translate("BoardButton", "10M", 0),
                                              QApplication::translate("BoardButton", "1pps", 0),
                                              QApplication::translate("BoardButton", "B-AC", 0),
                                              QApplication::translate("BoardButton", "B-DC", 0));

                toButtonLabel(slot)->setText(QApplication::translate("mainPanel", "10M", 0));
                break;
            case FTS_BOARD_TYPE_GNSS:
                toButtonFrame(slot)->setBoard(QApplication::translate("BoardButton", "10M", 0),
                                              QApplication::translate("BoardButton", "1pps", 0),
                                              QApplication::translate("BoardButton", "B-AC", 0),
                                              QApplication::translate("BoardButton", "B-DC", 0));

                toButtonLabel(slot)->setText(QApplication::translate("mainPanel", "GNSS", 0));
                break;
            case FTS_BOARD_TYPE_OUTER_REF:
                toButtonFrame(slot)->setBoard(QApplication::translate("BoardButton", "10M", 0),
                                              QApplication::translate("BoardButton", "1pps", 0),
                                              QApplication::translate("BoardButton", "B-AC", 0),
                                              QApplication::translate("BoardButton", "B-DC", 0));

                toButtonLabel(slot)->setText(QApplication::translate("mainPanel", "外频", 0));

                break;
            default:
                break;
            }


            if (err == FTS_CAN_CODE_BOARD_OK)
                toButtonFrame(slot)->setLedColor(Qt::green);
            else

                toButtonFrame(slot)->setLedColor(Qt::red);

        }

        //boardInsterted(int slot, int boardType)
    }

    ::close(sock);
}
#endif
