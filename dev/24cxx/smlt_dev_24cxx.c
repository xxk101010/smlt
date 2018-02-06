#include "smlt_dev_24cxx.h" 

const unsigned long  smlt_AT24xx_max[SMLT_DEV_AT24SUM] = {127,255,511,1023,2047,4095,8191,16383,32767};
const unsigned long  smlt_AT24xx_id[SMLT_DEV_AT24SUM] = {0XA0, 0XA0, 0XA0, 1023, 0XA0, 0XA0, 0XA0, 0XA0, 0XA0};
/************************************************************
  Function   : smlt_AT24cxx_init()

  Description: config init
  Calls      :
  Called By  :
  Input      :  Aval : A0,A1,A2 val (if(up AT24C08) no need val)
 
  Output     :
  Return     :  the handle of key obj
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
smlt_AT24cxx_eng_t* smlt_AT24cxx_init(char dev_types, void *I2c_ModeSetFunc, void *I2c_IoSetFunc, void *I2c_IoGetFunc, char Aval)
{
    smlt_AT24xx_eng_t* pstAT24cxxEng;

    pstAT24cxxEng = (smlt_AT24cxx_eng_t*)smlt_calloc(1, sizeof(smlt_AT24cxx_eng_t));
    if(pstAT24cxxEng == NULL)
    {
        return NULL;
    }
    pstAT24cxxEng->dev_types = dev_types;
    if(pstAT24cxxEng->dev_types <= SMLT_DEV_AT24C16)
    {
        pstAT24cxxEng->sla_type = 1;
    }
    else
    {
        pstAT24cxxEng->sla_type = 2;
    }
    pstAT24cxxEng->i2c_eng = smlt_softI2c_new(NULL, I2c_ModeSetFunc, I2c_IoSetFunc, I2c_IoGetFunc);
    if(pstAT24cxxEng->i2c_eng == NULL)
    {
        goto FAILED;
    }
    return pstAT24cxxEng; 
FAILED:    
    if(pstAT24cxxEng)
    {
        smlt_AT24cxx_deinit(pstAT24cxxEng)   
    }
}

/************************************************************
  Function   : void smlt_AT24cxx_deinit(smlt_AT24cxx_eng_t* pstAT24cxxEng)

  Description: config init
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  the handle of key obj
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
void smlt_AT24cxx_deinit(smlt_AT24cxx_eng_t* pstAT24cxxEng)
{
    if(pstAT24cxxEng)
    {
        if(pstAT24cxxEng->i2c_eng)
        {
            smlt_softI2c_delete(pstAT24cxxEng->i2c_eng);
        }
        SMLT_PTR_FREE(pstAT24cxxEng);
    }
}

/************************************************************
  Function   : UINT16_t smlt_AT24cxx_ReadOneByte(smlt_AT24cxx_eng_t* pstAT24cxxEng, UINT32_t ReadAddr)

  Description: config init
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  the handle of key obj
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
UINT16_t smlt_AT24cxx_ReadOneByte(smlt_AT24cxx_eng_t* pstAT24cxxEng, UINT32_t ReadAddr)
{
    UINT8_t temp=0;  
    UINT8_t sla;
    
    if(pstAT24cxxEng == NULL)
    {
       return 0xFFFF; 
    }
    if(ReadAddr >= smlt_AT24xx_max[pstAT24cxxEng->dev_types])
    {
       return 0xFFFF;  
    }
#ifndef SMLT_AT24CXX_HARDBUS_I2C

    sla = smlt_AT24xx_id[pstAT24cxxEng->dev_types]|pstAT24cxxEng->Aval;
    smlt_sfI2c_start(pstAT24cxxEng->i2c_eng);  
    if(pstAT24cxxEng->sla_type == 2)
    {    
        smlt_sfI2c_TxdByte(pstAT24cxxEng->i2c_eng, sla); 
        smlt_sfI2c_ack_wait(pstAT24cxxEng->i2c_eng);
        smlt_sfI2c_TxdByte(pstAT24cxxEng->i2c_eng, ReadAddr>>8);   
    }
    else if(pstAT24cxxEng->sla_type == 1)
    {
        smlt_sfI2c_TxdByte(pstAT24cxxEng->i2c_eng, sla+((ReadAddr/256)<<1));
    }
    else
    {
        return 0xFFFF;
    }
    
    smlt_sfI2c_ack_wait(pstAT24cxxEng->i2c_eng);
    smlt_sfI2c_TxdByte(pstAT24cxxEng->i2c_eng, ReadAddr%256); 
    smlt_sfI2c_ack_wait(pstAT24cxxEng->i2c_eng);
    smlt_sfI2c_start(pstAT24cxxEng->i2c_eng);            
    smlt_sfI2c_TxdByte(pstAT24cxxEng->i2c_eng, sla+1); 
    smlt_sfI2c_ack_wait(pstAT24cxxEng->i2c_eng);    
    temp = smlt_sfI2c_rcvByte(pstAT24cxxEng->i2c_eng, 0); 
    smlt_sfI2c_stop(pstAT24cxxEng->i2c_eng);                                
    return (UINT16_t)temp;   
#else
#endif
}

/************************************************************
  Function   : UINT16_t smlt_AT24cxx_ReadOneByte(smlt_AT24cxx_eng_t* pstAT24cxxEng, UINT32_t ReadAddr)

  Description: config init
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  the handle of key obj
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
void AT24CXX_WriteOneByte(uint8_t sla,uint8_t suba_type, uint16_t WriteAddr,uint8_t DataToWrite)
{                                                                                                   
    IIC_Start();  
    if(suba_type == 2)
    {    
        IIC_Send_Byte(sla);        //����д����
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
    IIC_Send_Byte(WriteAddr%256);                   //���͵͵�ַ
    IIC_Wait_Ack();                                                           
    IIC_Send_Byte(DataToWrite);                         //�����ֽ�                               
    IIC_Wait_Ack();                     
    IIC_Stop();                                                            //����һ��ֹͣ���� 
        
    //delay_ms(10);
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
** Returned value:       ����1:���ʧ��     ����0:���ɹ�
** note:                ���������24Cϵ��,�����ַҪ�޸�
*********************************************************************************************************/
uint8_t AT24CXX_Check(uint8_t sla,uint8_t suba_type)
{
    uint8_t temp;
    temp=AT24CXX_ReadOneByte(sla, suba_type, 255);    //����ÿ�ο�����дAT24CXX               
    if(temp==0X55)
    {
        return 0;           
    }
    else                            //�ų���һ�γ�ʼ�������
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
** input parameters:       ReadAddr��ʼ�����ĵ�ַ ��24c02Ϊ0~255 ,pBuffer,���������׵�ַ,NumToRead:Ҫ�������ݵĸ���
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
** input parameters:       WriteAddr:��ʼд��ĵ�ַ ��24c02Ϊ0~255��pBuffer:���������׵�ַ��NumToWrite:Ҫд�����ݵĸ���
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
 








