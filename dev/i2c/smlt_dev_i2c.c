

#include "smlt_dev_i2c.h"
//#include "delay.h"

/*********************************************************************************************************
** Function name:       IIC_Init
** Descriptions:        IIC初始化
** input parameters:    无
** output parameters:   无
** Returned value:     
*********************************************************************************************************/
void IIC_Init(void)
{                         
    SCL_OUT();
    SDA_OUT();     //sda线输出
    Set_IIC_SCL;
    Set_IIC_SDA;
}


/*********************************************************************************************************
** Function name:       IIC_Start
** Descriptions:        产生IIC起始信号
** input parameters:    无
** output parameters:   无
** Returned value:     
*********************************************************************************************************/
void IIC_Start(void)
{
    SDA_OUT();     //sda线输出
    Set_IIC_SDA;            
    Set_IIC_SCL;
    DelayXus(4);
    //delay_us(1);
     Clr_IIC_SDA;//START:when CLK is high,DATA change form high to low 
    DelayXus(4);
    Clr_IIC_SCL;//钳住I2C总线，准备发送或接收数据
    //DelayXus(1);    
}      


/*********************************************************************************************************
** Function name:       IIC_Stop
** Descriptions:        产生IIC停止信号
** input parameters:    无
** output parameters:   无
** Returned value:     
*********************************************************************************************************/
void IIC_Stop(void)
{
    SDA_OUT();//sda线输出
    Clr_IIC_SCL;
    Clr_IIC_SDA;//STOP:when CLK is high DATA change form low to high
    DelayXus(4);
//     delay_us(1);
    Set_IIC_SCL; 
    Set_IIC_SDA;//发送I2C总线结束信号
    DelayXus(4);                                   
}

/*********************************************************************************************************
** Function name:       IIC_Wait_Ack
** Descriptions:        等待应答信号到来
** input parameters:    无
** output parameters:   无
** Returned value:         1，接收应答失败
                        0，接收应答成功
*********************************************************************************************************/
uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime=0;
    SDA_IN();                          //SDA设置为输入  
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
    Clr_IIC_SCL;                    //时钟输出0        
    return 0;  
} 

/*********************************************************************************************************
** Function name:       IIC_Ack
** Descriptions:        产生ACK应答
** input parameters:    无
** output parameters:   无
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
** Descriptions:        不产生ACK应答    
** input parameters:    无
** output parameters:   无
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
** Descriptions:        IIC发送一个字节    
** input parameters:    无
** output parameters:   
** Returned value:         返回从机有无应答  
                        //1，有应答
                        //0，无应答    
*********************************************************************************************************/          
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
      SDA_OUT();         
    Clr_IIC_SCL;//拉低时钟开始数据传输
      //DelayXus(2);
    for(t=0; t<8; t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
        if ((txd&0x80)>>7)     Set_IIC_SDA;
        else Clr_IIC_SDA;
     txd <<= 1;       
        DelayXus(2);
//        delay_us(2);   //对TEA5767这三个延时都是必须的
        Set_IIC_SCL;
        DelayXus(2);
//        delay_us(2); 
        Clr_IIC_SCL;    
            DelayXus(2);
    }     
}         
/*********************************************************************************************************
** Function name:       IIC_Read_Byte
** Descriptions:        IIC发送一个字节    
** input parameters:    无
** output parameters:   
** Returned value:         读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
*********************************************************************************************************/
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}
