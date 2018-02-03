

#include "smlt_dev_i2c.h"
//#include "delay.h"

/*********************************************************************************************************
** Function name:       IIC_Init
** Descriptions:        IIC��ʼ��
** input parameters:    ��
** output parameters:   ��
** Returned value:     
*********************************************************************************************************/
void IIC_Init(void)
{                         
    SCL_OUT();
    SDA_OUT();     //sda�����
    Set_IIC_SCL;
    Set_IIC_SDA;
}


/*********************************************************************************************************
** Function name:       IIC_Start
** Descriptions:        ����IIC��ʼ�ź�
** input parameters:    ��
** output parameters:   ��
** Returned value:     
*********************************************************************************************************/
void IIC_Start(void)
{
    SDA_OUT();     //sda�����
    Set_IIC_SDA;            
    Set_IIC_SCL;
    DelayXus(4);
    //delay_us(1);
     Clr_IIC_SDA;//START:when CLK is high,DATA change form high to low 
    DelayXus(4);
    Clr_IIC_SCL;//ǯסI2C���ߣ�׼�����ͻ��������
    //DelayXus(1);    
}      


/*********************************************************************************************************
** Function name:       IIC_Stop
** Descriptions:        ����IICֹͣ�ź�
** input parameters:    ��
** output parameters:   ��
** Returned value:     
*********************************************************************************************************/
void IIC_Stop(void)
{
    SDA_OUT();//sda�����
    Clr_IIC_SCL;
    Clr_IIC_SDA;//STOP:when CLK is high DATA change form low to high
    DelayXus(4);
//     delay_us(1);
    Set_IIC_SCL; 
    Set_IIC_SDA;//����I2C���߽����ź�
    DelayXus(4);                                   
}

/*********************************************************************************************************
** Function name:       IIC_Wait_Ack
** Descriptions:        �ȴ�Ӧ���źŵ���
** input parameters:    ��
** output parameters:   ��
** Returned value:         1������Ӧ��ʧ��
                        0������Ӧ��ɹ�
*********************************************************************************************************/
uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime=0;
    SDA_IN();                          //SDA����Ϊ����  
    Set_IIC_SDA;
    DelayXus(1);
    //DelayXus(1);//delay_us(1);    //delay_us(1);       
    Set_IIC_SCL;
    DelayXus(1);
  //    DelayXus(1);//delay_us(1);    //delay_us(1); 
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    Clr_IIC_SCL;                    //ʱ�����0        
    return 0;  
} 

/*********************************************************************************************************
** Function name:       IIC_Ack
** Descriptions:        ����ACKӦ��
** input parameters:    ��
** output parameters:   ��
** Returned value:         
*********************************************************************************************************/
void IIC_Ack(void)
{
    Clr_IIC_SCL;
    SDA_OUT();
    Clr_IIC_SDA;
    DelayXus(2);
//    delay_us(1);
    Set_IIC_SCL;
    DelayXus(2);
//    delay_us(1);
    Clr_IIC_SCL;
}
    
/*********************************************************************************************************
** Function name:       IIC_NAck
** Descriptions:        ������ACKӦ��    
** input parameters:    ��
** output parameters:   ��
** Returned value:         
*********************************************************************************************************/        
void IIC_NAck(void)
{
    Clr_IIC_SCL;
    SDA_OUT();
    Set_IIC_SDA;
    DelayXus(2);
//    delay_us(1);
    Set_IIC_SCL;
    DelayXus(2);
//    delay_us(1);
    Clr_IIC_SCL;
}                                          


/*********************************************************************************************************
** Function name:       IIC_Send_Byte
** Descriptions:        IIC����һ���ֽ�    
** input parameters:    ��
** output parameters:   
** Returned value:         ���شӻ�����Ӧ��  
                        //1����Ӧ��
                        //0����Ӧ��    
*********************************************************************************************************/          
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
      SDA_OUT();         
    Clr_IIC_SCL;//����ʱ�ӿ�ʼ���ݴ���
      //DelayXus(2);
    for(t=0; t<8; t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
        if ((txd&0x80)>>7)     Set_IIC_SDA;
        else Clr_IIC_SDA;
     txd <<= 1;       
        DelayXus(2);
//        delay_us(2);   //��TEA5767��������ʱ���Ǳ����
        Set_IIC_SCL;
        DelayXus(2);
//        delay_us(2); 
        Clr_IIC_SCL;    
            DelayXus(2);
    }     
}         
/*********************************************************************************************************
** Function name:       IIC_Read_Byte
** Descriptions:        IIC����һ���ֽ�    
** input parameters:    ��
** output parameters:   
** Returned value:         ��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
*********************************************************************************************************/
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
    {
        Clr_IIC_SCL; 
            DelayXus(2);
            Set_IIC_SCL;
        receive<<=1;
        if(READ_SDA)receive++;
        DelayXus(1);        
        //        delay_us(1);
    }                     
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
