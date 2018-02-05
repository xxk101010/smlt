
#include "smlt_dev_24cxx.h" 

const unsigned long  smlt_AT24xx_max[SMLT_DEV_AT24SUM] = {127,255,511,1023,2047,4095,8191,16383,32767};

/*********************************************************************************************************
** Function name:       AT24CXX_Init
** Descriptions:        ��ʼ��IIC�ӿ�	
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
** Descriptions:        ��AT24CXXָ����ַ����һ������	
** input parameters:    ReadAddr:��ʼ�����ĵ�ַ
** output parameters:   
** Returned value:     	����������   
*********************************************************************************************************/
uint8_t AT24CXX_ReadOneByte(uint8_t sla,uint8_t suba_type, uint16_t ReadAddr)
{				  
	uint8_t temp=0;	
    
    IIC_Start();  
	if(suba_type == 2)
	{	
		IIC_Send_Byte(sla);	   //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ	 
	}
	else if(suba_type == 1)
	{
		IIC_Send_Byte(sla+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 
	}
	else
	{
		return 0;
	}
	
	IIC_Wait_Ack(); 
  IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(sla+1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
  temp=IIC_Read_Byte(0);		   
   IIC_Stop();										//����һ��ֹͣ����	    
	return temp;
}

/*********************************************************************************************************
** Function name:       AT24CXX_WriteOneByte
** Descriptions:        ��AT24CXXָ����ַд��һ������	
** input parameters:    WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ��DataToWrite:Ҫд������� 
** output parameters:   
** Returned value:      
*********************************************************************************************************/
void AT24CXX_WriteOneByte(uint8_t sla,uint8_t suba_type, uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																  
    IIC_Start();  
	if(suba_type == 2)
	{	
		IIC_Send_Byte(sla);	    //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ		 
	}
	else if(suba_type == 1)
	{
		IIC_Send_Byte(sla+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	else
	{;}
		
	IIC_Wait_Ack();	   
  IIC_Send_Byte(WriteAddr%256);   				//���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     					//�����ֽ�							   
	IIC_Wait_Ack();  		    	   
  IIC_Stop();															//����һ��ֹͣ���� 
		
//	delay_ms(10);

}

/*********************************************************************************************************
** Function name:       AT24CXX_WriteLenByte
** Descriptions:        ��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen�����ݣ��ú�������д��16bit����32bit������	
** input parameters:    WriteAddr  :��ʼд��ĵ�ַ��DataToWrite:���������׵�ַ
** output parameters:   Len        :Ҫд�����ݵĳ���2,4
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
** Descriptions:        ��AT24CXX�����ָ����ַ��ʼ��������ΪLen�����ݣ��ú������ڶ���16bit����32bit������.	
** input parameters:    ReadAddr   :��ʼ�����ĵ�ַ��Len        :Ҫ�������ݵĳ���2,4
** output parameters:   ����
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
** Descriptions:        ���AT24CXX�Ƿ���������������24XX�����һ����ַ(255)���洢��־��.	
** input parameters:   	
** output parameters:   
** Returned value:       ����1:���ʧ��	 ����0:���ɹ�
** note:				���������24Cϵ��,�����ַҪ�޸�
*********************************************************************************************************/
uint8_t AT24CXX_Check(uint8_t sla,uint8_t suba_type)
{
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(sla, suba_type, 255);	//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)
	{
		return 0;		   
	}
	else							//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(sla, suba_type, 255,0X55);
	    temp=AT24CXX_ReadOneByte(sla, suba_type, 255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

/*********************************************************************************************************
** Function name:       AT24CXX_Read
** Descriptions:        ��AT24CXX�����ָ����ַ��ʼ����ָ������������	
** input parameters:   	ReadAddr��ʼ�����ĵ�ַ ��24c02Ϊ0~255 ,pBuffer,���������׵�ַ,NumToRead:Ҫ�������ݵĸ���
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
** Descriptions:        ��AT24CXX�����ָ����ַ��ʼд��ָ������������
** input parameters:   	WriteAddr:��ʼд��ĵ�ַ ��24c02Ϊ0~255��pBuffer:���������׵�ַ��NumToWrite:Ҫд�����ݵĸ���
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
 








