#include "ftscmdthread.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ftsCan.h"
#include <linux/can.h>
#include <QDebug>

#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/can/raw.h>
#include <linux/can.h>


FtsCmdThread::FtsCmdThread(QObject *parent)
    : QThread(parent)
{

}

void FtsCmdThread::run()
{
    int sock;
    struct sockaddr_can addr;
    struct ifreq ifr;
    int ret;
    int recv_own_msgs = 0; //set loop back:  1 enable 0 disable
    struct can_frame recv_frame;

#if 0//zbl test
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

    /* struct can_filter rfilter[2];
    rfilter[0].can_id = 0x55;
    rfilter[0].can_mask = 0xff;
    rfilter[1].can_id = 0xaa;
    rfilter[1].can_mask = 0xff00;
    setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
    */

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
        case FTS_CAN_CODE_POLL:
            switch (boardtype) {
            case FTS_BOARD_TYPE_POWER:
             emit   pwrErr(slot, err);
                break;
            case FTS_BOARD_TYPE_GNSS:
            emit   gnssErr(slot, err);
                break;
            default:
                break;
            }
            break;

        }
    }
    ::close(sock);
}



//! [1]
FtsCmdThread::~FtsCmdThread()
{


}

