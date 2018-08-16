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

#define FTS_BOARD_TYPE_NTP 0
#define FTS_BOARD_TYPE_PTP 1
#define FTS_BOARD_TYPE_10M 2
#define FTS_BOARD_TYPE_1PPS 3
#define FTS_BOARD_TYPE_IRIG_B 4
#define FTS_BOARD_TYPE_NULL 5
#define FTS_BOARD_TYPE_GNSSA 6
#define FTS_BOARD_TYPE_GNSSB 7
#define FTS_BOARD_TYPE_PWRA0 8
#define FTS_BOARD_TYPE_PWRB0 9
#define FTS_BOARD_TYPE_PWRA1 10
#define FTS_BOARD_TYPE_PWRB1 11
#define FTS_BOARD_TYPE_FTA 12
#define FTS_BOARD_TYPE_FTB 13
#define FTS_BOARD_TYPE_SW 14
#define FTS_BOARD_TYPE_ALLOC 15






int fts_slot_state[3];

void init_ftsCan(void)
{


}
unsigned int fts_can_mk_send_id(unsigned int board_type)
{
    unsigned int byte0, byte1, byte2, byte3;

    byte0 = 0;
    byte1 = 0xF0;
    byte2 = board_type;
    byte3 = 0x00011000;

    return (byte3<<24)|(byte2<<16)|(byte1<<8)|byte0;
}

unsigned int fts_can_mk_send_id_output(unsigned int slot, unsigned int board_type)
{
	unsigned int byte0, byte1, byte2, byte3;

	byte0 = 0;
	byte1 = 0xF0;
	byte2 = (slot<<4)|board_type;
	byte3 = 0x00011000;

	return (byte3<<24)|(byte2<<16)|(byte1<<8)|byte0;
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

int fts_can_send_and_recv(struct can_frame *send_frame, struct can_frame *recv_frame)
{
	int sock;
	struct sockaddr_can addr;
	struct ifreq ifr;
	int ret;
	int recv_own_msgs = 0; //set loop back:  1 enable 0 disable

#if 1//zbl test
    return 0;
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

struct can_frame * fts_can_make_scalar_frame_ptp_poll(int canid)
{
	struct can_frame *frame;
	char *p1;
	char *p2;

	int test_size = sizeof (struct in_addr);  //test size
	
	frame = malloc(sizeof(struct can_frame));
	if (frame == NULL)
	{
        printf("ftsCan_makeScalarFrame");
		exit(1);
	}

	frame->can_id = canid;
	frame->can_dlc = 2;
	frame->data[0] = FTS_CAN_FRAME_CMD_CODE_PTP_SET_MODE;

	return frame;
}

void fts_can_parse_scalar_frame_ptp_poll_reply(struct can_frame *frame, int *flag)
{
	if (frame->data[0] != FTS_CAN_FRAME_CMD_CODE_PTP_SET_MODE)
        printf("fts_can_parse_scalar_frame_ptp_poll_reply");
	*flag = (int)frame->data[1];
}


struct can_frame * fts_can_make_scalar_frame_ptp_get_state(int canid)
{
	struct can_frame *frame;
	char *p1;
	char *p2;
	int test_size = sizeof (struct in_addr);  //test size
	
	frame = malloc(sizeof(struct can_frame));
	if (frame == NULL)
	{
        printf("ftsCan_makeScalarFrame");
		exit(1);
	}

	frame->can_id = canid;
	frame->can_dlc = 1;
	frame->data[0] = FTS_CAN_FRAME_CMD_CODE_PTP_GET_STATE;

	return frame;
}

void fts_can_parse_scalar_frame_ptp_get_state_reply(struct can_frame *frame, int *mode, int *synRate, int *DelayRate)
{
	if (frame->data[0] != FTS_CAN_FRAME_CMD_CODE_PTP_GET_STATE_REPLY)
        printf("fts_can_parse_scalar_frame_ptp_poll_reply");
	*mode = (int)frame->data[1];
	*synRate = (int)frame->data[2];
	*DelayRate = (int)frame->data[3];
}

struct can_frame * fts_can_make_scalar_frame_ptp_set_mode(int canid, int mode)
{
	struct can_frame *frame;
	char *p1;
	char *p2;

	int test_size = sizeof (struct in_addr);  //test size
	
	frame = malloc(sizeof(struct can_frame));
	if (frame == NULL)
	{
        printf("ftsCan_makeScalarFrame");
		exit(1);
	}

	frame->can_id = canid;
	frame->can_dlc = 2;
	frame->data[0] = FTS_CAN_FRAME_CMD_CODE_PTP_SET_MODE;
	frame->data[1] = (char)mode; 

	return frame;
}


struct can_frame * fts_can_make_scalar_frame_ptp_set_param(int canid, int syncRate, int delayRate)
{
	struct can_frame *frame;
	char *p1;
	char *p2;

	int test_size = sizeof (struct in_addr);  //test size
	
	frame = malloc(sizeof(struct can_frame));
	if (frame == NULL)
	{
        printf("ftsCan_makeScalarFrame");
		exit(1);
	}

	frame->can_id = canid;
	frame->can_dlc = 3;
	frame->data[0] = FTS_CAN_FRAME_CMD_CODE_PTP_SET_PARAM;
	frame->data[1] = (char)syncRate; 
	frame->data[2] = (char)delayRate; 

	return frame;
}



struct can_frame * fts_can_make_scalar_frame_ptp_set_ip_p2(int canid, struct in_addr mask, struct in_addr gateway)
{
	struct can_frame *frame;
	char *p1;
	char *p2;

	int test_size = sizeof (struct in_addr);  //test size
	
	frame = malloc(sizeof(struct can_frame));
	if (frame == NULL)
	{
        printf("ftsCan_makeScalarFrame");
		exit(1);
	}

	frame->can_id = canid;
	frame->can_dlc = 8;
	frame->data[0] = FTS_CAN_FRAME_CMD_CODE_PTP_SET_IP_P2;
	p1 = (char *)&mask;
	frame->data[1] = p1[3]; 

	p2 = (char *)&gateway;
	frame->data[2] = p2[0]; 
	frame->data[3] = p2[1]; 
	frame->data[4] = p2[2]; 
	frame->data[5] = p2[3]; 

	return frame;
}

struct can_frame * fts_can_make_scalar_frame_ptp_set_multicast_master(int canid, struct in_addr mask, struct in_addr gateway)
{
	struct can_frame *frame;
	char *p1;
	char *p2;

	int test_size = sizeof (struct in_addr);  //test size
	
	frame = malloc(sizeof(struct can_frame));
	if (frame == NULL)
	{
        printf("ftsCan_makeScalarFrame");
		exit(1);
	}

		frame->can_id = canid;
		frame->can_dlc = 8;
		frame->data[0] = FTS_CAN_FRAME_CMD_CODE_PTP_SET_IP_P2;
		p1 = (char *)&mask;
		frame->data[1] = p1[3]; 

		p2 = (char *)&gateway;
		frame->data[2] = p2[0]; 
		frame->data[3] = p2[1]; 
		frame->data[4] = p2[2]; 
		frame->data[5] = p2[2]; 
		
	return frame;
}

void fts_can_make_ref_table_frame()
{

}

void fts_can_make_ntp_table_frame()
{

}

void fts_can_make_ptp_table_frame()
{

}

void fts_can_get_scalar_int()
{
	
}

void fts_can_get_scalar_string()
{
	
}

void fts_can_get_table_ntp()
{
	
}

int fts_can_gnssA_poll(int *error)
{
    struct can_frame sendframe, recvframe;
    int test_size = sizeof (struct in_addr);  //test size
    int canid;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(FTS_BOARD_TYPE_GNSSA);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_GNSSA_POLL;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);
    if (ret != 0)
        return FTS_CAN_CODE_BOARD_NO_RESPONSE;
    else
    {
       *error = recvframe.data[0];
       return FTS_CAN_CODE_BOARD_OK_RESPONSE;
    }
}


int fts_can_gnssA_get_ref_state(struct ref_state *gps_state, struct ref_state *bd_state)
{
    struct can_frame sendframe, recvframe;
    int test_size = sizeof (struct in_addr);  //test size
    int canid;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(FTS_BOARD_TYPE_FTA);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_GNSSA_POLL;


    ret = fts_can_send_and_recv(&sendframe, &recvframe);
    if (ret != 0)
        return FTS_CAN_CODE_BOARD_NO_RESPONSE;
    else
    {
         gps_state->selected = recvframe.data[1];
         gps_state->locked = recvframe.data[2];
         gps_state->timediff = recvframe.data[3];
         bd_state->selected = recvframe.data[4];
         bd_state->locked = recvframe.data[5];
         bd_state->timediff = recvframe.data[6];
        return FTS_CAN_CODE_BOARD_OK_RESPONSE;
    }
}

int fts_can_pwrA0_poll(int *error)
{
    struct can_frame sendframe, recvframe;
    int canid;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(FTS_BOARD_TYPE_PWRA0);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_POLL;
    ret = fts_can_send_and_recv(&sendframe, &recvframe);
    if (ret != 0)
        return FTS_CAN_CODE_BOARD_NO_RESPONSE;
    else
    {
       *error = recvframe.data[0];
       return FTS_CAN_CODE_BOARD_OK_RESPONSE;
    }    
}

int fts_can_pwrA0_get_current(int *current)
{
    struct can_frame sendframe, recvframe;
    int canid;
    int ret;


    sendframe.can_id = fts_can_mk_send_id(FTS_BOARD_TYPE_PWRA0);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_PWRA0_GET;
    
    ret = fts_can_send_and_recv(&sendframe, &recvframe);

    if (ret != 0)
        return FTS_CAN_CODE_BOARD_NO_RESPONSE;
    else
    {
         *current = recvframe.data[1];

        return FTS_CAN_CODE_BOARD_OK_RESPONSE;
    }    
}

int fts_can_B_poll(int slot, int *error)
{
    struct can_frame sendframe, recvframe;
    int canid;
    int ret;

    sendframe.can_id = fts_can_mk_send_id(FTS_BOARD_TYPE_GNSSA);
    sendframe.can_dlc = 1;
    sendframe.data[0] = FTS_CAN_CODE_GNSSA_POLL;

    ret = fts_can_send_and_recv(&sendframe, &recvframe);
    if (ret != 0)
        return FTS_CAN_CODE_BOARD_NO_RESPONSE;
    else
    {
       *error = recvframe.data[0];
       return FTS_CAN_CODE_BOARD_OK_RESPONSE;
    }
}

int fts_can_get (int slot, int *MI, int *amp, int *delay)
{

}

int fts_can_set(int slot, int MI, int amp, int delay)
{

}

