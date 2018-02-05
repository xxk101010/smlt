/*-------------------------------------------------------------------------
    
-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
    
-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
    
-------------------------------------------------------------------------*/
/************************************************************
  Copyright (C), AISpeechTech. Co., Ltd.

  FileName   : smlt_key.c
  Project    :
  Module     :
  Version    :
  Date       : 2018/1/20
  Author     : kun.xu
  Document   :
  Description:

  Function List :

  History :
  <author>      <time>            <version >        <desc>
  kun.xu       2018/01/20            1.00            Create

************************************************************/

#include "smlt_dev_i2c.h"
#include "smlt_arch.h"


/*********************************************************************************************************
** Function name:       IIC_Init
** Descriptions:        IIC初始化
** input parameters:    无
** output parameters:   无
** Returned value:     
*********************************************************************************************************/
smlt_sfI2c_eng_t* smlt_softI2c_new(char* cfg, void *modeSetFunc, void *IoSetFunc)
{           
    smlt_sfI2c_eng_t* pstSfI2c_eng;

    pstSfI2c_eng =  (smlt_sfI2c_eng_t *)smlt_calloc(sizeof(smlt_sfI2c_eng_t), 1);
    if(pstSfI2c_eng == NULL)
    {
        return NULL;
    }

    pstSfI2c_eng->i2cPortModeSet = modeSetFunc;
    pstSfI2c_eng->i2cPortSet = IoSetFunc;

    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_OUTPUT);
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SCL, SMLT_I2C_OUTPUT);
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_HIGH);
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
}

/*********************************************************************************************************
** Function name:       IIC_Start
** Descriptions:        产生IIC起始信号
** input parameters:    无
** output parameters:   无
** Returned value:     
*********************************************************************************************************/
signed char smlt_sfI2c_start(smlt_sfI2c_eng_t *pstSfI2c_eng)
{
    if(pstSfI2c_eng == NULL)
    {
        return -1;
    }
    //SDA_OUT();
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_OUTPUT);
  
    //Set_IIC_SDA;            
    //Set_IIC_SCL;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_HIGH);
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);

    //DelayXus(4);
    smlt_delayUs(2);
    //Clr_IIC_SDA;//START:when CLK is high,DATA change form high to low 
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_LOW);
    //DelayXus(4);
    smlt_delayUs(4);
    //Clr_IIC_SCL;//钳住I2C总线，准备发送或接收数据
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
}      


/*********************************************************************************************************
** Function name:       IIC_Stop
** Descriptions:        产生IIC停止信号
** input parameters:    无
** output parameters:   无
** Returned value:     
*********************************************************************************************************/
signed char smlt_sfI2c_stop(smlt_sfI2c_eng_t *pstSfI2c_eng)
{
    if(pstSfI2c_eng == NULL)
    {
        return -1;
    }
    //SDA_OUT();
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_OUTPUT);
    //Clr_IIC_SCL;
    //Clr_IIC_SDA;//STOP:when CLK is high DATA change form low to high
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
    smlt_delayUs(1);
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_LOW);
    //DelayXus(4);
    smlt_delayUs(1);
    //Set_IIC_SCL; 
    //Set_IIC_SDA;
    //DelayXus(4);  
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
    smlt_delayUs(1);
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_HIGH);
    smlt_delayUs(1);                            
}

/*********************************************************************************************************
** Function name:       IIC_Wait_Ack
** Descriptions:        等待应答信号到来
** input parameters:    无
** output parameters:   无
** Returned value:         1，接收应答失败
                        0，接收应答成功
*********************************************************************************************************/
signed char smlt_sfI2c_ack_wait(smlt_sfI2c_eng_t *pstSfI2c_eng)
{
    uint8_t ucErrTime=0;

    //SDA_IN();  
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_INPUT);
                         
    //Set_IIC_SDA;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_HIGH);
    //DelayXus(1);
    //DelayXus(1);//delay_us(1);    //delay_us(1); 
    smlt_delayUs(1);
    //Set_IIC_SCL;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
   // DelayXus(1);
   //  DelayXus(1);//delay_us(1);    //delay_us(1); 
    smlt_delayUs(1);    // 鍙互涓嶅欢鏃�
    /* while(READ_SDA) */
    /* { */
        /* ucErrTime++; */
        /* if(ucErrTime > 250) */
        /* { */
            /* IIC_Stop(); */
            /* return -11; */
        /* } */
    /* } */
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
