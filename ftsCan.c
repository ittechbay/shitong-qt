#include <sys/types.h>			/* See NOTES */
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#include <pthread.h>
#include <semaphore.h>
#include <linux/can.h>
#include "ftsSetDo.h"
#include "ftsCan.h"


int fts_slot_state[3];

void init_ftsCan(void)
{


}


#define SLOT_COUNT 24
#define BOARD_TYPE_COUNT 10
//board type电源-0、GNSS-1、外参考-2、时频-3、切换-4、分配-5、NTP-6、PTP-7、B-8、10M-9
static unsigned int canAddressArray[SLOT_COUNT][BOARD_TYPE_COUNT] = {
    //main box
    {0,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,2,3,4,5},//NTP
    {0,0,0,0,0,0,6,7,8,9},//PTP
    {0,0,0,0,0,0,10,11,12,13},//B
    {0,0,0,0,0,0,14,15,16,17},//10
    {0,18,0,0,0,0,0,0,0,0}, //GNSS
    {0,19,0,0,0,0,0,0,0,0},//GNSS
    {0,0,20,0,0,0,0,0,0,0},//outRef
    {0,0,0,21,0,0,0,0,0,0},//tf
    {0,0,0,0,22,0,0,0,0,0},//sw
    {0,0,0,23,0,0,0,0,0,0},//tf

    //alloc box
    {24,0,0,0,0,0,0,0,0,0},//pwr
    {25,0,0,0,0,0,0,0,0,0},//pwr
    {0,0,0,0,0,0,26,27,28,29},
    {0,0,0,0,0,0,30,31,32,33},
    {0,0,0,0,0,0,34,35,36,37},
    {0,0,0,0,0,0,38,39,40,41},
    {0,0,0,0,0,0,42,43,44,45},
    {0,0,0,0,0,0,46,47,48,49},
    {0,0,0,0,0,0,50,51,52,53},
    {0,0,0,0,0,0,54,55,56,57},
    {0,0,0,0,0,0,58,59,60,61},
    {0,0,0,0,0,62,0,0,0,0}// alloc
};
#define CAN_ID_COUNT 100
unsigned int canidToSlotAndBoardtype[CAN_ID_COUNT][2] = {
    {0,FTS_BOARD_TYPE_POWER},  {1,FTS_BOARD_TYPE_POWER},
    {2,FTS_BOARD_TYPE_NTP},  {2,FTS_BOARD_TYPE_PTP}, {2,FTS_BOARD_TYPE_B},   {2,FTS_BOARD_TYPE_10M},
    {3,FTS_BOARD_TYPE_NTP},  {3,FTS_BOARD_TYPE_PTP}, {3,FTS_BOARD_TYPE_B},   {3,FTS_BOARD_TYPE_10M},
    {4,FTS_BOARD_TYPE_NTP},  {4,FTS_BOARD_TYPE_PTP},  {4,FTS_BOARD_TYPE_B},  {4,FTS_BOARD_TYPE_10M},
    {5,FTS_BOARD_TYPE_NTP},  {5,FTS_BOARD_TYPE_PTP},  {5,FTS_BOARD_TYPE_B},  {5,FTS_BOARD_TYPE_10M},

    {6,FTS_BOARD_TYPE_GNSS},  {6,FTS_BOARD_TYPE_OUTER_REF},  {7,FTS_BOARD_TYPE_GNSS},  {7,FTS_BOARD_TYPE_OUTER_REF},  {8,FTS_BOARD_TYPE_GNSS},  {8,FTS_BOARD_TYPE_OUTER_REF},
    {9,FTS_BOARD_TYPE_TF},  {10,FTS_BOARD_TYPE_SW}, {11,FTS_BOARD_TYPE_TF},
    {12,FTS_BOARD_TYPE_POWER},  {13,FTS_BOARD_TYPE_POWER},

    {14,FTS_BOARD_TYPE_NTP},    {14,FTS_BOARD_TYPE_PTP},    {14,FTS_BOARD_TYPE_B},    {14,FTS_BOARD_TYPE_10M},
    {15,FTS_BOARD_TYPE_NTP},    {15,FTS_BOARD_TYPE_PTP},    {15,FTS_BOARD_TYPE_B},    {15,FTS_BOARD_TYPE_10M},
    {16,FTS_BOARD_TYPE_NTP},    {16,FTS_BOARD_TYPE_PTP},    {16,FTS_BOARD_TYPE_B},    {16,FTS_BOARD_TYPE_10M},
    {17,FTS_BOARD_TYPE_NTP},    {17,FTS_BOARD_TYPE_PTP},    {17,FTS_BOARD_TYPE_B},    {17,FTS_BOARD_TYPE_10M},
    {18,FTS_BOARD_TYPE_NTP},    {18,FTS_BOARD_TYPE_PTP},    {18,FTS_BOARD_TYPE_B},    {18,FTS_BOARD_TYPE_10M},
    {19,FTS_BOARD_TYPE_NTP},    {19,FTS_BOARD_TYPE_PTP},    {19,FTS_BOARD_TYPE_B},    {19,FTS_BOARD_TYPE_10M},
    {20,FTS_BOARD_TYPE_NTP},    {20,FTS_BOARD_TYPE_PTP},    {20,FTS_BOARD_TYPE_B},    {20,FTS_BOARD_TYPE_10M},
    {21,FTS_BOARD_TYPE_NTP},    {21,FTS_BOARD_TYPE_PTP},    {21,FTS_BOARD_TYPE_B},    {21,FTS_BOARD_TYPE_10M},
    {22,FTS_BOARD_TYPE_NTP},    {22,FTS_BOARD_TYPE_PTP},    {22,FTS_BOARD_TYPE_B},    {22,FTS_BOARD_TYPE_10M},

    {23,FTS_BOARD_TYPE_ALLOC}
};
#define FTS_CAN_FRAME_ID_BYTE 0x18          //CAN protocal type byte
#define FTS_CAN_FRAME_MON_ADDR_BYTE 0xFE    //CAN protocal type byte
//#define FTS_CAN_FRAME_BROARDCAST_ADDR ((FTS_CAN_FRAME_ID_BYTE<<24)|(0xFF<<16)|(FTS_CAN_FRAME_MON_ADDR_BYTE<<8)) //

unsigned int fts_can_mk_send_id(unsigned int slot, unsigned int board_type)
{
    unsigned int id, byte0, byte1, byte2, byte3;

    byte0 = 0;
    byte1 = FTS_CAN_FRAME_MON_ADDR_BYTE; //Monitor board CAN address is 0xFE
    byte2 = canAddressArray[slot][board_type];
    byte3 = FTS_CAN_FRAME_ID_BYTE;

    id = (byte3<<24)|(byte2<<16)|(byte1<<8)|byte0;
    id = id|CAN_EFF_FLAG;

    return id;
}

unsigned int fts_can_mk_broadcast_send_id()
{
    unsigned int id, byte0, byte1, byte2, byte3;

    byte0 = 0;
    byte1 = FTS_CAN_FRAME_MON_ADDR_BYTE;
    byte2 = 0xFF;
    byte3 = FTS_CAN_FRAME_ID_BYTE;
    id = (byte3<<24)|(byte2<<16)|(byte1<<8)|byte0;
    id = id|CAN_EFF_FLAG;
    return id;
}

int fts_can_id_to_slot(int canid)
{
    int tmp = canid&(~0xf0);
    return tmp>>4;
}

int fts_can_id_to_board_type(int canid)
{
    int tmp = canid&0xf;
    return tmp;
}

int fts_can_send(struct can_frame *send_frame)
{
    int sock;
    struct sockaddr_can addr;
    struct ifreq ifr;
    int ret;
    int recv_own_msgs = 0; //set loop back:  1 enable 0 disable

#if 0//zbl test
    return 1;
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
        close(sock);
        exit(1);
    }

    printf("%s can_ifindex = %x\n",ifr.ifr_name,ifr.ifr_ifindex);
    addr.can_ifindex = ifr.ifr_ifindex;

    //ioctl(sock,SIOCGIFNAME,&ifr);
    //printf("ret = %d can0 can_ifname = %s\n",ret,ifr.ifr_name);

    setsockopt(sock, SOL_CAN_BASE + CAN_RAW, 0x4, &recv_own_msgs, sizeof(recv_own_msgs));
    if (bind(sock,(struct sockaddr*)&addr,sizeof(addr))<0) {
        printf("bind error\n");
        close(sock);
        exit(1);
    }

    ret = write(sock, (void *)send_frame, sizeof(struct can_frame));

    close(sock);
    return 0;
}

int fts_can_send_and_recv(struct can_frame *send_frame, struct can_frame *recv_frame)
{
	int sock;
	struct sockaddr_can addr;
	struct ifreq ifr;
	int ret;
	int recv_own_msgs = 0; //set loop back:  1 enable 0 disable

#if 0//zbl test
    return 1;
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
		close(sock);
        exit(1);
	}

	printf("%s can_ifindex = %x\n",ifr.ifr_name,ifr.ifr_ifindex);
	addr.can_ifindex = ifr.ifr_ifindex;

	//ioctl(sock,SIOCGIFNAME,&ifr);
	//printf("ret = %d can0 can_ifname = %s\n",ret,ifr.ifr_name);	

    setsockopt(sock, SOL_CAN_BASE + CAN_RAW, 0x4, &recv_own_msgs, sizeof(recv_own_msgs));
	if (bind(sock,(struct sockaddr*)&addr,sizeof(addr))<0) {
		printf("bind error\n");
		close(sock);
        exit(1);
	}
    //todo: set receive filter, only receive dest can addr
	ret = write(sock, (void *)send_frame, sizeof(struct can_frame));
	///////////////////////
	
	struct timeval tv;
	fd_set readfds;
	
	tv.tv_sec = 2;
	tv.tv_usec = 500000;

	FD_ZERO(&readfds);
	FD_SET(sock, &readfds);
	// don't care about writefds and exceptfds:
	ret = select(sock+1, &readfds, NULL, NULL, &tv);
	if (ret <=0)
	{
		close(sock);
		return -1;
	}
	ret = read(sock, (void *)recv_frame, sizeof(struct can_frame));


	close(sock);
	return 0;
}

int fts_can_broardcast_poll()
{
    struct can_frame sendframe;
    //int test_size = sizeof (struct in_addr);  //test size
    int ret;

    sendframe.can_id = fts_can_mk_broadcast_send_id();
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_POLL;

    ret = fts_can_send(&sendframe);
    return ret;
}

int fts_can_poll(unsigned slot, unsigned boardtype, int *error)
{
    struct can_frame sendframe, recvframe;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(slot, boardtype);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_POLL;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

    *error = recvframe.data[3];
    return FTS_CAN_OK_RESPONSE;

}

int fts_can_pwr_get_current(unsigned slot, int *current)
{
    struct can_frame sendframe, recvframe;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_POWER);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_PWR_GET;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

    *current = recvframe.data[1];
     return FTS_CAN_OK_RESPONSE;

}

struct fts_ref_state { //[锁定|选中] [收星数高位][收星数低位]
int selected;
int locked;
int satCnt;
};
#define FTS_CAN_GNSS_SELECT_MASK 0x00000001
#define FTS_CAN_GNSS_LOCK_MASK 0x00000002
#define FTS_CAN_GNSS_JD_SIGN_MASK 0x00000001
#define FTS_CAN_GNSS_WD_SIGN_MASK 0x00000002


int fts_can_gnss_get_state(unsigned slot, struct fts_ref_state *gps_state, struct fts_ref_state *bd_state)
{
    struct can_frame sendframe, recvframe;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_GNSS);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_GNSS_GET_STATE;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

        int data_h, data_l;

        gps_state->selected = recvframe.data[1]&FTS_CAN_GNSS_SELECT_MASK;
        gps_state->locked = (recvframe.data[1]&FTS_CAN_GNSS_LOCK_MASK)>>1;
        data_h = recvframe.data[2];
        data_l = recvframe.data[3];
        gps_state->satCnt = (data_h<<8)|data_l;

        bd_state->selected = recvframe.data[4]&FTS_CAN_GNSS_SELECT_MASK;
        bd_state->locked = (recvframe.data[4]&FTS_CAN_GNSS_LOCK_MASK)>>1;
        data_h = recvframe.data[5];
        data_l = recvframe.data[6];
        bd_state->satCnt = (data_h<<8)|data_l;

        return FTS_CAN_OK_RESPONSE;

}

struct fts_jwd {
int jd; //
int jd_fen;
int jd_miao;
int wd;
int wd_fen;
int wd_miao;
};

int fts_can_gnss_get_gps_jwd(unsigned slot, struct fts_jwd *gps_jwd)
{
    struct can_frame sendframe, recvframe;
    int ret;
    int sign_jd, sign_wd; //jing
    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_GNSS);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_GNSS_GET_GPS_JWD;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }


    sign_jd = recvframe.data[1]&FTS_CAN_GNSS_JD_SIGN_MASK;
    gps_jwd->jd = recvframe.data[2];
    if (sign_jd != 0)
        gps_jwd->jd *= -1;
    gps_jwd->jd_fen = recvframe.data[3];
    gps_jwd->jd_miao = recvframe.data[4];

    gps_jwd->wd = recvframe.data[5];
    if (sign_wd != 0)
        gps_jwd->jd *= -1;
    gps_jwd->wd_fen = recvframe.data[6];
    gps_jwd->wd_miao = recvframe.data[7];
    return FTS_CAN_OK_RESPONSE;

}

int fts_can_gnss_get_bd_jwd(unsigned slot, struct fts_jwd *bd_jwd)
{
    struct can_frame sendframe, recvframe;
    int ret;
    int sign_jd, sign_wd; //jing
    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_GNSS);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_GNSS_GET_BD_JWD;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }


        sign_jd = recvframe.data[1]&FTS_CAN_GNSS_JD_SIGN_MASK;
        bd_jwd->jd = recvframe.data[2];
        if (sign_jd != 0)
            bd_jwd->jd *= -1;
        bd_jwd->jd_fen = recvframe.data[3];
        bd_jwd->jd_miao = recvframe.data[4];

        bd_jwd->wd = recvframe.data[5];
        if (sign_wd != 0)
            bd_jwd->jd *= -1;
        bd_jwd->wd_fen = recvframe.data[6];
        bd_jwd->wd_miao = recvframe.data[7];
        return FTS_CAN_OK_RESPONSE;

}

//1PPS 10M TOD
#define FTS_CAN_CODE_1PPS_SEL_MASK 0x00000001
#define FTS_CAN_CODE_10M_SEL_MASK 0x00000002
#define FTS_CAN_CODE_TOD_SEL_MASK 0x00000004
int fts_can_outfreq_get(unsigned slot, int *_1pps, int *_10M, int *tod)
{
    struct can_frame sendframe, recvframe;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_OUTER_REF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_OUTER_REF_GET;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

        *_1pps = (recvframe.data[1]&FTS_CAN_CODE_1PPS_SEL_MASK);
        *_10M = (recvframe.data[1]&FTS_CAN_CODE_10M_SEL_MASK)>>1;
        *tod = (recvframe.data[1]&FTS_CAN_CODE_TOD_SEL_MASK)>>2;

        return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_get_date(unsigned slot, int *year, int *month, int *day)
{
    struct can_frame sendframe, recvframe;
    int ret;
    int data_h, data_l;

    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 5;
    sendframe.data[0] = FTS_CAN_CODE_TF_GET_DATE;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }


    data_h = recvframe.data[1];
    data_l = recvframe.data[2];
    *year = (recvframe.data[1]<<8)|recvframe.data[2];
    *month = recvframe.data[3];
    *day = recvframe.data[4];

    return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_get_time(unsigned slot, int *hour, int *minute, int *second)
{
    struct can_frame sendframe, recvframe;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 4;
    sendframe.data[0] = FTS_CAN_CODE_TF_GET_TIME;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

        *hour = recvframe.data[1];
        *minute = recvframe.data[2];
        *second = recvframe.data[3];

        return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_get_time_zone(unsigned slot, int *tz_index)
{
    struct can_frame sendframe, recvframe;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_GET_TIME_ZONE;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

     *tz_index = recvframe.data[1];

     return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_set_date(unsigned slot, int year, int month, int day)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_SET_DATE;
    sendframe.data[1] = year>>8;
    sendframe.data[2] = year&0xFF;
    sendframe.data[3] = month;
    sendframe.data[4] = day;


    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

    return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_set_time(unsigned slot, int hour, int minute, int second)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_SET_TIME;
    sendframe.data[1] = hour;
    sendframe.data[2] = minute;
    sendframe.data[3] = second;



    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

    return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_set_time_zone(unsigned slot, int tz_index)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_SET_TIME_ZONE;
    sendframe.data[1] = tz_index;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

         return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_cmd_add_second(unsigned slot)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_CMD_ADD_SECOND;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

         return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_cmd_subtract_second(unsigned slot)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_CMD_SUBTRACT_SECOND;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

         return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_cmd_forword(unsigned slot)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_CMD_FORWORD;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

         return FTS_CAN_OK_RESPONSE;
}

int fts_can_tf_cmd_backword(unsigned slot)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_CMD_BACKWORD;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

     return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_cmd_syn(unsigned slot)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_CMD_SYN;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }
    return FTS_CAN_OK_RESPONSE;

}

int fts_can_tf_cmd_get_run_mode(unsigned slot, int *mode, int *sel)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_GET_RUN_MODE;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }
    *mode = recvframe.data[1];

    if (*mode == FTS_CAN_CODE_TF_RUN_MODE_MANUAL)
        *sel = recvframe.data[2];

    return FTS_CAN_OK_RESPONSE;
}


int fts_can_tf_cmd_set_run_mode(unsigned slot, int mode, int sel)
{
    struct can_frame sendframe, recvframe;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 2;
    sendframe.data[0] = FTS_CAN_CODE_TF_SET_RUN_MODE;
    sendframe.data[1] = mode;
    sendframe.data[2] = sel;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

    return FTS_CAN_OK_RESPONSE;
}

int fts_can_tf_cmd_get_time_diff(unsigned slot, int *time)
{
    struct can_frame sendframe, recvframe;
    int ret;



    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_GET_TIME_DIFF;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }

    int data_h, data_l;

    data_h = recvframe.data[1];
    data_l = recvframe.data[2];
    *time = (data_h<<8)|data_l;


    return FTS_CAN_OK_RESPONSE;

}


int fts_can_tf_cmd_get_acc(unsigned slot, int *acc)
{
    struct can_frame sendframe, recvframe;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(slot, FTS_BOARD_TYPE_TF);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_TF_GET_ACC;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_NO_RESPONSE;
    else if (recvframe.data[0] == FTS_CAN_CODE_RESPONSE)
    {
        if (recvframe.data[1] == FTS_CAN_CODE_RESPONSE_ERROR)
            return FTS_CAN_ERROR_RESPONSE;
    }
    int data_h, data_l;

    data_h = recvframe.data[1];
    data_l = recvframe.data[2];
    *acc = (data_h<<8)|data_l;


    return FTS_CAN_OK_RESPONSE;

}



