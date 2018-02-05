
#ifndef __PROTOAL_H
#define __PROTOAL_H	 

#include "stm32f0xx_hal.h"


#define INVALID_WRITE_DATA_ADDR (0xFFFF)


#pragma  pack(1)
typedef struct _CMD_FORMAT 
{
	unsigned char CmdHead;      //命令头
	unsigned char DeviceType;   //设备代码
	unsigned char BoxNo;        //设备编号
	unsigned char FunctionNum;  //功能编码
 
//	union
//	{
//		unsigned short Addr;        //操作地址
		
		
//		struct 
//		{
//			unsigned char ChannelNum;  //通道号
//			unsigned char FadeValue;   //
//		};

//		struct  
//		{
//			unsigned char Preset;
//			unsigned char Time;
//		};

//		struct  
//		{
//			unsigned char FadeTime;
//			unsigned char  FadeChannelNum;
//		};
//	};
	
	unsigned char payload[3];     //参数

	unsigned char Checksum;     //校验和
	
} CMD_FORMAT_t;

#pragma  pack(1)
typedef struct _F5_CMD_FORMAT 
{
	unsigned char SOM;      //命令头
	unsigned char area;   //设备代码
	unsigned char join;        //设备编号
	unsigned char FunctionNum;  //功能编码
 
	unsigned char payload[3];     //参数

	unsigned char Checksum;     //校验和
	
} F5_CMD_FORMAT_t;


typedef enum  _CMD_HEAD_SIGN
{
	HEAD_SIGN_CMD           = 0xF5,
	HEAD_SIGN_SETTING       = 0xFA,
	HEAD_SIGN_Block_WRITE    = 0xFC,

}CMD_HEAD_SIGN_t;


typedef  enum _CMD_FA_FUNC
{
	FUNC_NUM_KEYBOARD_CMD        = 0xF5,  //键盘命令

	FUNC_NUM_REQUEST_VERSION     = 0xBA,  //应答0xFE
	FUNC_NUM_SEARCH_PARAM_ACK    = 0xF9,

	FUNC_NUM_WRITE_ONE_BYTE      = 0xFA,  //应答0xF9
	FUNC_NUM_SEARCH_PARAMTER     = 0xFB,  //应答0xF9
	FUNC_NUM_ENTER_INTER_MODE    = 0xFD,  //参数: 01 01 00 setup dc1000 box 214: Master Listen to me
	                                      //参数: 01 00 00 Setup dc1000 box 214: Master Go back to work
    
  FUNC_NUM_REBOOT              = 0xFC,  //Reboot DC1000 Box 214
  FUNC_NUM_REBOOT_ACK          = 0xFE,  //参数: 01 06 80 DC1000 V1.06 214 Reset


	FUNC_NUM_SET_FADE            = 0xB7,  //设置调光量,闪烁

	FUNC_NUM_WRITE_DATA_ADDR     = 0xDD,  //
	FUNC_NUM_ACK_WRITE_DATA_ADDR = 0xDC,  //

	FUNC_NUM_BLOCK_READ_ENABLE   = 0xDF,  //应答0xDE
	FUNC_NUM_BLOCK_READ_ACK      = 0xDE,
    
}CMD_FA_FUNCTION_t;

typedef enum _CMD_F5_FUNC
{
	
	F5_FUNC_NUM_D3 = 0xD3,   //调光

	F5_FUNC_NUM_D5 = 0xD5,
	
	F5_FUNC_NUM_D6 = 0xD6,   //Toggle Preset Fade

	F5_FUNC_NUM_DA = 0xDA,   //所有通道停止渐变
	
	//F5_FUNC_NUM_DB = 0xDB,   //修改所有通道渐变时间

	F5_FUNC_NUM_DC = 0xDC,   //Fade To Off Fade
	
	F5_FUNC_NUM_DB = 0xDB,   //Fade To On Fade
	

	F5_FUNC_NUM_FE = 0xFE,   //选择场景

	F5_FUNC_NUM_FD = 0xFD,   //渐暗至关闭
	
	F5_FUNC_NUM_E3 = 0xE3,   //Request Channel Level 
	
	F5_FUNC_NUM_E4 = 0xE4,   //Request Channel Level 
	
	F5_FUNC_NUM_E1 = 0xE1,   //Request Current Preset
	
	F5_FUNC_NUM_E2 = 0xE2,   //Request Current Preset
	
	



}CMD_F5_FUNC_t;



typedef enum _Protoal_Set_Mode
{
	Normal_Work_Mode = 0x00,   //正常工作模式

	Master_Listen_Mode    = 0x01,   //监听模式

}Protoal_Set_Mode_t;


typedef struct _CMD_Send_obj
{
  uint8_t CMD_Send_Buffer[8];
	
	uint32_t CMD_Send_Occupy_Flag;
	
}CMD_Send_obj_t;



extern Protoal_Set_Mode_t  Protoal_Set_Mode;

uint8_t format_check_func(uint8_t *pData, uint16_t Size);
void Buffer_Trans_Fun(uint8_t *pData, uint16_t Size);
void Protoal_Process_Fun(void);
void CMD_ACK_Reset(void);
void CMD_Search_CMD(void);
void F5_CMD_send(uint8_t area,uint8_t join,uint8_t func,uint8_t payload_0,uint8_t payload_1,uint8_t payload_2);


#endif
