
#include "protoal.h"

#include "app.h"
	
#include "string.h"	

#include "24cxx.h" 

#include "usart.h"	

#include "cmsis_os.h"

#include "delay.h"




extern osMessageQId Send_QueueHandle;

extern uint32_t d;





CMD_Send_obj_t  CMD_Send_obj[8]; //发送数据对象管理

CMD_FORMAT_t   CMD_FORMAT={0xFA,0xE0,0XFF,0,0,0,0,0};//协议数据格式

uint8_t CMD_Receive_Buffer[8]; //命令接收buffer：注意不是真的串口接收buffer



Protoal_Set_Mode_t  Protoal_Set_Mode;


static void CMD_handle_Fun(void);

static void SETTING_handle_Fun(void);

static void Block_WRITE_handle_Fun(void);

static void CMD_ACK(uint8_t* P_data);

static void SoftReset(void);


uint8_t CheckSum(uint8_t *buffer,uint16_t Num);

uint8_t format_check_func(uint8_t *pData, uint16_t Size)
{
	if((pData==NULL)||(Size<8))
	{
		return 1;
	}
	if(pData[0]==HEAD_SIGN_SETTING)
	{
		if(pData[1]!=Device_Type_ID)
		{
			return 1;
		}		
		if((pData[2]!=Device_Set_Pra.Memmory_1.Device_Box)&&(pData[2]!=0))
		{
				return 1;
		}		
  }	
	
	if(CheckSum(pData,7)!=pData[7])
	{
		return 1;
	}
	
	return 0;
}

void Buffer_Trans_Fun(uint8_t *pData, uint16_t Size)
{
	memcpy(CMD_Receive_Buffer,pData,8);
}


void Protoal_Process_Fun(void)
{
  switch((CMD_HEAD_SIGN_t)CMD_Receive_Buffer[0])
	{
		case  HEAD_SIGN_CMD:
		{
			CMD_handle_Fun();
			break;
		}
			
		case  HEAD_SIGN_SETTING:
		{
			SETTING_handle_Fun();
			break;
		}
			
	  case  HEAD_SIGN_Block_WRITE:	
		{
			if(Protoal_Set_Mode==Master_Listen_Mode)
			{
			Block_WRITE_handle_Fun();
			}
			break;
		}
			
		default:
		{
			break;
		}
	}
	
}



static void CMD_handle_Fun(void)
{
	uint16_t device_time;
	
	if(g_device_state==Device_No_Okay)
	{
		return;
	}
	switch((CMD_F5_FUNC_t)CMD_Receive_Buffer[3])
	{
		
		case F5_FUNC_NUM_D3:
		{
		 Device_Switch_Fuc_Process(CMD_Receive_Buffer[1],CMD_Receive_Buffer[5],CMD_Receive_Buffer[6],CMD_Receive_Buffer[4]*50,RESET,CMD_Receive_Buffer[2]);
		 break;
		}
		case F5_FUNC_NUM_FD:
		{
		 Device_Switch_Fuc_Process(CMD_Receive_Buffer[1],CMD_Receive_Buffer[5],0,CMD_Receive_Buffer[4]*50,RESET,CMD_Receive_Buffer[2]);	
		 break;
		}
		case F5_FUNC_NUM_DC:
		{
		 Device_Switch_Fuc_Process(CMD_Receive_Buffer[1],CMD_Receive_Buffer[5],0xFF,CMD_Receive_Buffer[4]*50,RESET,CMD_Receive_Buffer[2]);
     break;			
		}		
    case F5_FUNC_NUM_DB:
    {
		 Device_Switch_Fuc_Process(CMD_Receive_Buffer[1],CMD_Receive_Buffer[5],1,CMD_Receive_Buffer[4]*50,RESET,CMD_Receive_Buffer[2]); 
		 break;
		}			
		case F5_FUNC_NUM_DA:
		{
     Device_Switch_Fuc_Process(CMD_Receive_Buffer[1],CMD_Receive_Buffer[5],1,0,SET,CMD_Receive_Buffer[2]); 
		 break;
		}			
		case F5_FUNC_NUM_E3:
		{
		  memcpy((uint8_t*)&CMD_FORMAT.CmdHead,CMD_Receive_Buffer,7);
			
			if(Device_Adj_Level_Request(&CMD_FORMAT.payload[0],&CMD_FORMAT.payload[2],CMD_Receive_Buffer[1],CMD_Receive_Buffer[5]))
			{
				return;
			}
			
			CMD_FORMAT.FunctionNum= F5_FUNC_NUM_E4;
			
			CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);
			
      CMD_ACK(&CMD_FORMAT.CmdHead);
			
			break;
		}
		
		case F5_FUNC_NUM_E1:
		{
			uint8_t set_tmp;
			
			set_tmp = Device_preset_search(CMD_Receive_Buffer[1],CMD_Receive_Buffer[2]);
			
			if( set_tmp > 0x10)
			{
				return;
			}
				
		  memcpy((uint8_t*)&CMD_FORMAT.CmdHead,CMD_Receive_Buffer,7);
			
			CMD_FORMAT.FunctionNum= F5_FUNC_NUM_E2;
			
			CMD_FORMAT.payload[1] =  set_tmp;
			
			CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);
			
      CMD_ACK(&CMD_FORMAT.CmdHead);
			
			break;
		}
		case F5_FUNC_NUM_FE: //场景命令
		{	
      device_time=	 (uint16_t)(CMD_Receive_Buffer[5]|(CMD_Receive_Buffer[6]<<8));	
			Device_preset_Level_save(CMD_Receive_Buffer[1],CMD_Receive_Buffer[4],CMD_Receive_Buffer[2]);
			Device_Preset_Process(CMD_Receive_Buffer[1],CMD_Receive_Buffer[4],device_time,CMD_Receive_Buffer[2]);
			//AT24CXX_Write(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1,432,Device_Set_Pra.Memmory_28.level_save,12);
		
			break;
		}
		case F5_FUNC_NUM_D6:
		{
	 	  Device_Preset_Process(CMD_Receive_Buffer[1],0xA9,CMD_Receive_Buffer[4]*5,CMD_Receive_Buffer[2]);
			break;
		}
		case F5_FUNC_NUM_D5:
		{
			Device_Preset_Process(CMD_Receive_Buffer[1],0xBA,CMD_Receive_Buffer[4]*5,CMD_Receive_Buffer[2]);
			break;
		}
		default:
		{
		 	
		 break;
		}
	}	
}



static void SETTING_handle_Fun(void)
{
	uint16_t EE_Addr=0;
  uint8_t i;
	
	switch((CMD_FA_FUNCTION_t)CMD_Receive_Buffer[3])
	{
		case FUNC_NUM_ENTER_INTER_MODE:
		{
			if((CMD_Receive_Buffer[4]==1)&&(CMD_Receive_Buffer[5]==1))
			{
				Protoal_Set_Mode=Master_Listen_Mode;
			}
			else if((CMD_Receive_Buffer[4]==1)&&(CMD_Receive_Buffer[5]==0))
			{		
		//		Normal_Work_Mode_Func();  //防止配置的时候发生灯光抖动
			  Protoal_Set_Mode=Normal_Work_Mode;
			}
		
			break;
		}
		case FUNC_NUM_WRITE_DATA_ADDR:
		{	

      memcpy((uint8_t*)&CMD_FORMAT.CmdHead,CMD_Receive_Buffer,7);
			
	    g_Curretn_EE_Addr = (uint16_t)((CMD_Receive_Buffer[4]<<8)|CMD_Receive_Buffer[5]);
			
			CMD_FORMAT.payload[0] =(uint8_t) (g_Curretn_EE_Addr>>8);
			
			CMD_FORMAT.payload[1] =(uint8_t) g_Curretn_EE_Addr;
			
			CMD_FORMAT.FunctionNum=FUNC_NUM_ACK_WRITE_DATA_ADDR;
			
			CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);
			
      CMD_ACK(&CMD_FORMAT.CmdHead);
		
			break;
		}
		case FUNC_NUM_ACK_WRITE_DATA_ADDR:
		{
			 memcpy((uint8_t*)&CMD_FORMAT.CmdHead,CMD_Receive_Buffer,8);
			 
			 CMD_ACK(&CMD_FORMAT.CmdHead);
			 
			 break;
		}
		case FUNC_NUM_REQUEST_VERSION:
		{
      memcpy((uint8_t*)&CMD_FORMAT.CmdHead,CMD_Receive_Buffer,7);
			
			CMD_FORMAT.FunctionNum=FUNC_NUM_REBOOT_ACK;
			
	    CMD_FORMAT.payload[0]=Device_Set_Pra.Memmory_1.Device_version[0];
	
	    CMD_FORMAT.payload[1]=Device_Set_Pra.Memmory_1.Device_version[1];
			
			CMD_FORMAT.payload[2]=0;					
			
			CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);
			
      CMD_ACK(&CMD_FORMAT.CmdHead);
			
			break;
		}
		
		case FUNC_NUM_SEARCH_PARAMTER:
		{
			uint16_t addr_tmp = 0;
			
			memcpy((uint8_t*)&CMD_FORMAT.CmdHead,CMD_Receive_Buffer,7);
			
			addr_tmp = (uint16_t)((CMD_Receive_Buffer[4]<<8)|(CMD_Receive_Buffer[5]));
					
			CMD_FORMAT.payload[2]= AT24CXX_ReadOneByte(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1, addr_tmp);
			
			DelayXus(1000);
			
			CMD_FORMAT.FunctionNum=FUNC_NUM_SEARCH_PARAM_ACK;
					
			CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);
			
			CMD_ACK(&CMD_FORMAT.CmdHead);
      			
			break;
		}
		
		case FUNC_NUM_BLOCK_READ_ENABLE:
		{	
			memcpy((uint8_t*)&CMD_FORMAT.CmdHead,CMD_Receive_Buffer,7);		

      CMD_FORMAT.FunctionNum=FUNC_NUM_BLOCK_READ_ACK;	

			CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);
			
		  g_Curretn_EE_Addr = (uint16_t)((CMD_Receive_Buffer[4]<<8)|CMD_Receive_Buffer[5]);
			
			CMD_ACK(&CMD_FORMAT.CmdHead);	
			
			break;
		}
		
		case FUNC_NUM_BLOCK_READ_ACK:
		{

			g_Curretn_EE_Addr = (uint16_t)((CMD_Receive_Buffer[4]<<8)|CMD_Receive_Buffer[5]);
      		
     	AT24CXX_Read(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1,g_Curretn_EE_Addr,&CMD_FORMAT.DeviceType,6);
			
			CMD_FORMAT.CmdHead = HEAD_SIGN_Block_WRITE;

      CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);		

      CMD_ACK(&CMD_FORMAT.CmdHead);			
						
			break;
					
		}
		
		case  FUNC_NUM_REBOOT:
		{
			
      SoftReset();		
      break;			
			
		}
		case  FUNC_NUM_WRITE_ONE_BYTE:
		{
			uint8_t cmp_data_tmp;	
    		
			memcpy((uint8_t*)&CMD_FORMAT.CmdHead,CMD_Receive_Buffer,7);	
			
			EE_Addr= (uint16_t)((CMD_Receive_Buffer[4]<<8)|CMD_Receive_Buffer[5]);
			
			AT24CXX_WriteOneByte(AT24C64_ADDR, IIC_DEV_ADDR_TYPE_1,EE_Addr,CMD_Receive_Buffer[6]);
			
			DelayXus(1000);
			
			cmp_data_tmp= AT24CXX_ReadOneByte(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1, EE_Addr);
			
			if(cmp_data_tmp!=CMD_Receive_Buffer[6])
			{
				return;
			}
			
		  CMD_FORMAT.FunctionNum=FUNC_NUM_SEARCH_PARAM_ACK ;	

			CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);
		
	    CMD_ACK(&CMD_FORMAT.CmdHead);
			
      break;			
			
		}
		case  FUNC_NUM_SET_FADE :
		{			
			  if(g_device_state==Device_No_Okay)
	      {
		       return;
	      }	  
			  if(CMD_Receive_Buffer[4]>Device_Channel_Number)
				{
					break;
				}
				i=CMD_Receive_Buffer[4]-1;

				device_channel_set(i,0xFF-CMD_Receive_Buffer[5],CMD_Receive_Buffer[6]*50);

      break;			
			
		}
		
			
		default:
		{
			break;
		}
		
	}
	
}


static void Block_WRITE_handle_Fun(void)
{	
  uint8_t cmp_data[6];
		 
	 AT24CXX_Write(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1,g_Curretn_EE_Addr,(uint8_t *)&CMD_Receive_Buffer[1],6);
	
	 AT24CXX_Read(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1, g_Curretn_EE_Addr,cmp_data,6);
  	
	 if(memcmp(cmp_data,&CMD_Receive_Buffer[1],6)!=0)
	 {
		 return;
	 }
	
	 if(g_Curretn_EE_Addr<2000)
	 {
	   memcpy((uint8_t *)&Device_Set_Pra.Memmory_1.Device_Type+g_Curretn_EE_Addr,(uint8_t *)&CMD_Receive_Buffer[1],6);
		 if(Device_Set_Pra.Memmory_1.Device_Type==Device_Type_ID)
		 {
			 g_device_state=Device_Okay;
		 }
	 }
	 
	 CMD_FORMAT.CmdHead=HEAD_SIGN_SETTING ;
	
	 CMD_FORMAT.DeviceType=Device_Type_ID;
	
	 CMD_FORMAT.BoxNo=Device_Set_Pra.Memmory_1.Device_Box;
	
	 CMD_FORMAT.FunctionNum=FUNC_NUM_ACK_WRITE_DATA_ADDR;	
	
	 CMD_FORMAT.payload[0]=(uint8_t)(g_Curretn_EE_Addr>>8);
	
	 CMD_FORMAT.payload[1]=(uint8_t)g_Curretn_EE_Addr;
	
	 CMD_FORMAT.payload[2]=0;
	
	 CMD_FORMAT.Checksum=CheckSum((uint8_t*)&CMD_FORMAT.CmdHead,7);
			
   CMD_ACK(&CMD_FORMAT.CmdHead); 
	 
	 g_Curretn_EE_Addr = g_Curretn_EE_Addr+6; 
}


uint8_t CheckSum(uint8_t *buffer,uint16_t Num) //校验和
{
	uint8_t sum=0;
	uint16_t i;
	for(i=Num;i!=0;i--)
	{
		sum+=*buffer++;
		sum = sum%256;
	}
	sum = 256-sum;
	return sum;
}


static void CMD_ACK(uint8_t* P_data)
{
	 uint8_t i=0;
	 
	 for(i=0;i<8;i++)
	 {
		 if((CMD_Send_obj[i].CMD_Send_Occupy_Flag)==0x00)
		 {
			 break;
		 }
		 if(i==7)
		 {
			 return;
		 }
	 }
	 CMD_Send_obj[i].CMD_Send_Occupy_Flag=1;
	 memcpy(&CMD_Send_obj[i].CMD_Send_Buffer[0],P_data,8);
	 osMessagePut(Send_QueueHandle, (uint32_t)&CMD_Send_obj[i].CMD_Send_Buffer[0], 10);
}

void F5_CMD_send(uint8_t area,uint8_t join,uint8_t func,uint8_t payload_0,uint8_t payload_1,uint8_t payload_2)
{
	F5_CMD_FORMAT_t F5_CMD_FORMAT;
	
	F5_CMD_FORMAT.SOM=0xF5;
	
	F5_CMD_FORMAT.area = area;
	
	F5_CMD_FORMAT.FunctionNum=func;
	
	F5_CMD_FORMAT.join=join;
	
	F5_CMD_FORMAT.payload[0]=  payload_0;
	
	F5_CMD_FORMAT.payload[1]=  payload_1;
	
	F5_CMD_FORMAT.payload[2]=  payload_2;
	
	F5_CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&F5_CMD_FORMAT.SOM,7);	
	
	CMD_ACK(&F5_CMD_FORMAT.SOM);
	
}


void CMD_ACK_Reset(void)
{
	
	CMD_FORMAT.CmdHead=HEAD_SIGN_SETTING ;
	
	CMD_FORMAT.DeviceType=Device_Type_ID;
	
	CMD_FORMAT.BoxNo=Device_Set_Pra.Memmory_1.Device_Box;
	
	CMD_FORMAT.FunctionNum=FUNC_NUM_REBOOT_ACK;		
	
	CMD_FORMAT.payload[0]=Device_Set_Pra.Memmory_1.Device_version[0];
	
	CMD_FORMAT.payload[1]=Device_Set_Pra.Memmory_1.Device_version[1];
	
	CMD_FORMAT.payload[2]=0x80;
	
	CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);	

	CMD_ACK(&CMD_FORMAT.CmdHead);	

}


void CMD_Search_CMD(void)
{
	
	CMD_FORMAT.CmdHead=HEAD_SIGN_SETTING ;
	
	CMD_FORMAT.DeviceType=Device_Type_ID;
	
	CMD_FORMAT.BoxNo=Device_Set_Pra.Memmory_1.Device_Box;
	
	CMD_FORMAT.FunctionNum=FUNC_NUM_REBOOT_ACK;		
	
	CMD_FORMAT.payload[0]=Device_Set_Pra.Memmory_1.Device_version[0];
	
	CMD_FORMAT.payload[1]=Device_Set_Pra.Memmory_1.Device_version[1];
	
	CMD_FORMAT.payload[2]=0x00;
	
	CMD_FORMAT.Checksum=CheckSum( (uint8_t*)&CMD_FORMAT.CmdHead,7);	

	CMD_ACK(&CMD_FORMAT.CmdHead);	

}


static void SoftReset(void) 
{  
//	__set_FAULTMASK(1); 
	
 NVIC_SystemReset();
	
} 
