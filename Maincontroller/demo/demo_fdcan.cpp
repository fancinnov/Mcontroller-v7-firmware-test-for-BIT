/*
 * demo_fdcan.cpp
 *
 *  Created on: 2022年8月21日
 *      Author: 25053
 */

#include "maincontroller.h"

void fdcan_init(void){//在系统初始化的时候运行一次
	//首先配置CAN接收过滤器
	fdcanFilterConfig->IdType = FDCAN_STANDARD_ID;
	fdcanFilterConfig->FilterIndex = 0;
	fdcanFilterConfig->FilterType = FDCAN_FILTER_MASK;
	fdcanFilterConfig->FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	fdcanFilterConfig->FilterID1 = 0x0000;
	fdcanFilterConfig->FilterID2 = 0x0000; /* For acceptance, MessageID and FilterID1 must match exactly */
	//配置can发送数据的header
	fdcanTxHeader->Identifier = 0x200;
	fdcanTxHeader->IdType = FDCAN_STANDARD_ID;
	fdcanTxHeader->TxFrameType = FDCAN_DATA_FRAME;
	fdcanTxHeader->DataLength = FDCAN_DLC_BYTES_8;
	fdcanTxHeader->ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	fdcanTxHeader->BitRateSwitch = FDCAN_BRS_OFF;
	fdcanTxHeader->FDFormat = FDCAN_CLASSIC_CAN;
	fdcanTxHeader->TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	fdcanTxHeader->MessageMarker = 0;
	set_comm3_as_fdcan();//把串口3重置为fdcan
}

static uint32_t notify=0;
void fdcan_update(void){//以自己需要的频率循环运行即可
	//CAN数据的接收
	if(get_fdcan_notification()!=notify){
		notify=get_fdcan_notification();
		//获取接收到的can header,本demo直接打印了header中的id.
		usb_printf("id:%x\n",fdcanRxHeader->Identifier);
		//获取接收到的can data,本demo直接打印了接收的8字节数据
		usb_printf("data:%d|%d|%d|%d|%d|%d|%d|%d\n",fdcanRxData[0],fdcanRxData[1],fdcanRxData[2],fdcanRxData[3],fdcanRxData[4],fdcanRxData[5],fdcanRxData[6],fdcanRxData[7]);
	}
	//CAN数据的发送
	fdcanTxHeader->Identifier = 0x200;//配置发送数据id
	fdcanTxData[0]=5000>>8;
	fdcanTxData[1]=5000&0xFF;
	fdcanTxData[2]=0;
	fdcanTxData[3]=0;
	fdcanTxData[4]=0;
	fdcanTxData[5]=0;
	fdcanTxData[6]=0;
	fdcanTxData[7]=0;
	fdcan_send_data();//demo演示了发送8字节数据
}
