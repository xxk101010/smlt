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
** Descriptions:        IIC³õÊ¼»¯
** input parameters:    ÎÞ
** output parameters:   ÎÞ
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
** Descriptions:        ²úÉúIICÆðÊ¼ÐÅºÅ
** input parameters:    ÎÞ
** output parameters:   ÎÞ
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
    //Clr_IIC_SCL;//Ç¯×¡I2C×ÜÏß£¬×¼±¸·¢ËÍ»ò½ÓÊÕÊý¾Ý
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
}      


/*********************************************************************************************************
** Function name:       IIC_Stop
** Descriptions:        ²úÉúIICÍ£Ö¹ÐÅºÅ
** input parameters:    ÎÞ
** output parameters:   ÎÞ
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
** Descriptions:        µÈ´ýÓ¦´ðÐÅºÅµ½À´
** input parameters:    ÎÞ
** output parameters:   ÎÞ
** Returned value:         1£¬½ÓÊÕÓ¦´ðÊ§°Ü
                        0£¬½ÓÊÕÓ¦´ð³É¹¦
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
    smlt_delayUs(1);    // å¯ä»¥ä¸å»¶æ—¶
    /* while(READ_SDA) */
    /* { */
        /* ucErrTime++; */
        /* if(ucErrTime > 250) */
        /* { */
            /* IIC_Stop(); */
            /* return -11; */
        /* } */
    /* } */
    Clr_IIC_SCL;                    //Ê±ÖÓÊä³ö0        
    return 0;  
} 

/*********************************************************************************************************
** Function name:       IIC_Ack
** Descriptions:        ²úÉúACKÓ¦´ð
** input parameters:    ÎÞ
** output parameters:   ÎÞ
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
** Descriptions:        ²»²úÉúACKÓ¦´ð    
** input parameters:    ÎÞ
** output parameters:   ÎÞ
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
** Descriptions:        IIC·¢ËÍÒ»¸ö×Ö½Ú    
** input parameters:    ÎÞ
** output parameters:   
** Returned value:         ·µ»Ø´Ó»úÓÐÎÞÓ¦´ð  
                        //1£¬ÓÐÓ¦´ð
                        //0£¬ÎÞÓ¦´ð    
*********************************************************************************************************/          
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
      SDA_OUT();         
    Clr_IIC_SCL;//À­µÍÊ±ÖÓ¿ªÊ¼Êý¾Ý´«Êä
      //DelayXus(2);
    for(t=0; t<8; t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
        if ((txd&0x80)>>7)     Set_IIC_SDA;
        else Clr_IIC_SDA;
     txd <<= 1;       
        DelayXus(2);
//        delay_us(2);   //¶ÔTEA5767ÕâÈý¸öÑÓÊ±¶¼ÊÇ±ØÐëµÄ
        Set_IIC_SCL;
        DelayXus(2);
//        delay_us(2); 
        Clr_IIC_SCL;    
            DelayXus(2);
    }     
}         
/*********************************************************************************************************
** Function name:       IIC_Read_Byte
** Descriptions:        IIC·¢ËÍÒ»¸ö×Ö½Ú    
** input parameters:    ÎÞ
** output parameters:   
** Returned value:         ¶Á1¸ö×Ö½Ú£¬ack=1Ê±£¬·¢ËÍACK£¬ack=0£¬·¢ËÍnACK   
*********************************************************************************************************/
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDAÉèÖÃÎªÊäÈë
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
        IIC_NAck();//·¢ËÍnACK
    else
        IIC_Ack(); //·¢ËÍACK   
    return receive;
}
