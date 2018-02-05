
#include "smlt_dev_24cxx.h" 

const unsigned long  smlt_AT24xx_max[SMLT_DEV_AT24SUM] = {127,255,511,1023,2047,4095,8191,16383,32767};

/*********************************************************************************************************
** Function name:       AT24CXX_Init
** Descriptions:        初始化IIC接口	
** input parameters:  
** output parameters:   
** Returned value:     	   
*********************************************************************************************************/
void AT24CXX_Init(void)
{
	IIC_Init();
}

/*********************************************************************************************************
** Function name:       AT24CXX_ReadOneByte
** Descriptions:        在AT24CXX指定地址读出一个数据	
** input parameters:    ReadAddr:开始读数的地址
** output parameters:   
** Returned value:     	读到的数据   
*********************************************************************************************************/
uint8_t AT24CXX_ReadOneByte(uint8_t sla,uint8_t suba_type, uint16_t ReadAddr)
{				  
	uint8_t temp=0;	
    
    IIC_Start();  
	if(suba_type == 2)
	{	
		IIC_Send_Byte(sla);	   //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//发送高地址	 
	}
	else if(suba_type == 1)
	{
		IIC_Send_Byte(sla+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 
	}
	else
	{
		return 0;
	}
	
	IIC_Wait_Ack(); 
  IIC_Send_Byte(ReadAddr%256);   //发送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(sla+1);           //进入接收模式			   
	IIC_Wait_Ack();	 
  temp=IIC_Read_Byte(0);		   
   IIC_Stop();										//产生一个停止条件	    
	return temp;
}

/*********************************************************************************************************
** Function name:       AT24CXX_WriteOneByte
** Descriptions:        在AT24CXX指定地址写入一个数据	
** input parameters:    WriteAddr  :写入数据的目的地址，DataToWrite:要写入的数据 
** output parameters:   
** Returned value:      
*********************************************************************************************************/
void AT24CXX_WriteOneByte(uint8_t sla,uint8_t suba_type, uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																  
    IIC_Start();  
	if(suba_type == 2)
	{	
		IIC_Send_Byte(sla);	    //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//发送高地址		 
	}
	else if(suba_type == 1)
	{
		IIC_Send_Byte(sla+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	else
	{;}
		
	IIC_Wait_Ack();	   
  IIC_Send_Byte(WriteAddr%256);   				//发送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     					//发送字节							   
	IIC_Wait_Ack();  		    	   
  IIC_Stop();															//产生一个停止条件 
		
//	delay_ms(10);

}

/*********************************************************************************************************
** Function name:       AT24CXX_WriteLenByte
** Descriptions:        在AT24CXX里面的指定地址开始写入长度为Len的数据，该函数用于写入16bit或者32bit的数据	
** input parameters:    WriteAddr  :开始写入的地址，DataToWrite:数据数组首地址
** output parameters:   Len        :要写入数据的长度2,4
** Returned value:      
*********************************************************************************************************/
void AT24CXX_WriteLenByte(uint8_t sla,uint8_t suba_type, uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  	
	uint8_t t;
	for(t=0;t<Len;t++)
	{
	
     AT24CXX_WriteOneByte(sla, suba_type, WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

/*********************************************************************************************************
** Function name:       AT24CXX_WriteLenByte
** Descriptions:        在AT24CXX里面的指定地址开始读出长度为Len的数据，该函数用于读出16bit或者32bit的数据.	
** input parameters:    ReadAddr   :开始读出的地址，Len        :要读出数据的长度2,4
** output parameters:   数据
** Returned value:      
*********************************************************************************************************/
uint32_t AT24CXX_ReadLenByte(uint8_t sla,uint8_t suba_type, uint16_t ReadAddr,uint8_t Len)
{  	
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<Len;t++)
	{

        temp<<=8;
		temp+=AT24CXX_ReadOneByte(sla, suba_type, ReadAddr+Len-t-1); 
               
	}
	return temp;												    
}

/*********************************************************************************************************
** Function name:       AT24CXX_WriteLenByte
** Descriptions:        检查AT24CXX是否正常，这里用了24XX的最后一个地址(255)来存储标志字.	
** input parameters:   	
** output parameters:   
** Returned value:       返回1:检测失败	 返回0:检测成功
** note:				如果用其他24C系列,这个地址要修改
*********************************************************************************************************/
uint8_t AT24CXX_Check(uint8_t sla,uint8_t suba_type)
{
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(sla, suba_type, 255);	//避免每次开机都写AT24CXX			   
	if(temp==0X55)
	{
		return 0;		   
	}
	else							//排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(sla, suba_type, 255,0X55);
	    temp=AT24CXX_ReadOneByte(sla, suba_type, 255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

/*********************************************************************************************************
** Function name:       AT24CXX_Read
** Descriptions:        在AT24CXX里面的指定地址开始读出指定个数的数据	
** input parameters:   	ReadAddr开始读出的地址 对24c02为0~255 ,pBuffer,数据数组首地址,NumToRead:要读出数据的个数
** output parameters:   
** Returned value:       
*********************************************************************************************************/
void AT24CXX_Read(uint8_t sla,uint8_t suba_type, uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		
    *pBuffer++=AT24CXX_ReadOneByte(sla, suba_type, ReadAddr++);	
		NumToRead--;
	}
}  

/*********************************************************************************************************
** Function name:       AT24CXX_Write
** Descriptions:        在AT24CXX里面的指定地址开始写入指定个数的数据
** input parameters:   	WriteAddr:开始写入的地址 对24c02为0~255，pBuffer:数据数组首地址，NumToWrite:要写入数据的个数
** output parameters:   
** Returned value:       
*********************************************************************************************************/
void AT24CXX_Write(uint8_t sla,uint8_t suba_type, uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
    AT24CXX_WriteOneByte(sla, suba_type, WriteAddr,*pBuffer);
		
		WriteAddr++;
		
		pBuffer++;
		
		osDelay(10);
		
	}
}
 








