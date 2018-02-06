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
#include "smlt_soft_i2c.h"
#include "smlt_arch.h"

/************************************************************
  Function   : smlt_sfI2c_eng_t* smlt_softI2c_new(char* cfg, void *modeSetFunc, void *IoSetFunc, void *ioGetFunc)

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
smlt_sfI2c_eng_t* smlt_softI2c_new(char* cfg, void *modeSetFunc, void *IoSetFunc, void *IoGetFunc)
{           
    smlt_sfI2c_eng_t* pstSfI2c_eng;

    pstSfI2c_eng =  (smlt_sfI2c_eng_t *)smlt_calloc(sizeof(smlt_sfI2c_eng_t), 1);
    if(pstSfI2c_eng == NULL)
    {
        return NULL;
    }

    pstSfI2c_eng->i2cPortModeSet = modeSetFunc;
    pstSfI2c_eng->i2cPortSet     = IoSetFunc;
    pstSfI2c_eng->i2cPortGet     = ioGetFunc

    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_OUTPUT);
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SCL, SMLT_I2C_OUTPUT);
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_HIGH);
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
}

/************************************************************
  Function   : smlt_sfI2c_eng_t* smlt_softI2c_new(char* cfg, void *modeSetFunc, void *IoSetFunc, void *ioGetFunc)

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
void smlt_softI2c_delete(smlt_sfI2c_eng_t *pstSfI2c_eng)
{           
    if(pstSfI2c_eng)
    {
        smlt_free(pstSfI2c_eng);
    }
}


/************************************************************
  Function   : signed char smlt_sfI2c_start(smlt_sfI2c_eng_t *pstSfI2c_eng)

  Description: 
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
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
    //Clr_IIC_SDA;  //START:when CLK is high,DATA change form high to low 
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_LOW);
    //DelayXus(4);
    smlt_delayUs(2);
    //Clr_IIC_SCL; 
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
}      

/************************************************************
  Function   : signed char smlt_sfI2c_stop(smlt_sfI2c_eng_t *pstSfI2c_eng)

  Description: 
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
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

/************************************************************
  Function   : signed char smlt_sfI2c_ack_wait(smlt_sfI2c_eng_t *pstSfI2c_eng)

  Description: 
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
signed char smlt_sfI2c_ack_wait(smlt_sfI2c_eng_t *pstSfI2c_eng)
{
    uint8_t ucErrTime=0;

    //SDA_IN();  
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_INPUT);                        
    //Set_IIC_SDA;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_HIGH);
    //DelayXus(1);
    smlt_delayUs(1);
    //Set_IIC_SCL;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
    //DelayXus(1);
    smlt_delayUs(1);    //可以不延时
    if(pstSfI2c_eng->i2cPortGet(SMLT_I2C_SDA))
    {
        return -1;
    }
    /* while(READ_SDA) */
    /* { */
        /* ucErrTime++; */
        /* if(ucErrTime > 250) */
        /* { */
            /* IIC_Stop(); */
            /* return -11; */
        /* } */
    /* } */
    //Clr_IIC_SCL; 
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
    return 0;  
} 

/************************************************************
  Function   : signed char smlt_sfI2c_ack(smlt_sfI2c_eng_t *pstSfI2c_eng)

  Description: 
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
signed char smlt_sfI2c_ack(smlt_sfI2c_eng_t *pstSfI2c_eng)
{
    if(pstSfI2c_eng == NULL)
    {
        return -1;
    }
    //Clr_IIC_SCL;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
    //SDA_OUT();
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_OUTPUT);
    //Clr_IIC_SDA;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_LOW);
    //DelayXus(2);
    smlt_delayUs(1);
    //Set_IIC_SCL;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
    //DelayXus(2);
    smlt_delayUs(1);
    //Clr_IIC_SCL; 
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
}

/************************************************************
  Function   : signed char smlt_sfI2c_Nack(smlt_sfI2c_eng_t *pstSfI2c_eng)

  Description: 
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/       
signed char smlt_sfI2c_Nack(smlt_sfI2c_eng_t *pstSfI2c_eng)
{
    if(pstSfI2c_eng == NULL)
    {
        return -1;
    }
    //Clr_IIC_SCL;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
    //SDA_OUT();
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_OUTPUT);
    //Set_IIC_SDA;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_HIGH);
    //DelayXus(2);
    smlt_delayUs(1);
    //Set_IIC_SCL;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
    //DelayXus(2);
    smlt_delayUs(1);
    //Clr_IIC_SCL;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
}                                          

/************************************************************
  Function   : signed char smlt_sfI2c_TxdByte(smlt_sfI2c_eng_t *pstSfI2c_eng, char txd)

  Description: 
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/           
signed char smlt_sfI2c_TxdByte(smlt_sfI2c_eng_t *pstSfI2c_eng, char txd)
{                        
    char i; 

    if(pstSfI2c_eng == NULL)
    {
        return -1;
    }    
    //SDA_OUT();   
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_OUTPUT);
    //Clr_IIC_SCL;
    pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
    for(i = 0; i < 8; i++)
    {              
        if ((txd&0x80) >> 7)  
        {
            //Set_IIC_SDA;  
            pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_HIGH);
            
        }  
        else
        {
            //Clr_IIC_SDA;
            pstSfI2c_eng->i2cPortSet(SMLT_I2C_SDA, SMLT_I2C_PORT_LOW);
        } 
        txd <<= 1;       
        //DelayXus(2); 
        smlt_delayUs(1);
        //Set_IIC_SCL;
        pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
        //DelayXus(2);
        smlt_delayUs(1);
        //Clr_IIC_SCL;
        pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
        //DelayXus(2);
        smlt_delayUs(1);    
    }     
}        

/************************************************************
  Function   : signed char smlt_sfI2c_rcvByte(smlt_sfI2c_eng_t *pstSfI2c_eng, char ack)

  Description: 
  Calls      :
  Called By  :
  Input      : 
 
  Output     :
  Return     :  
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/  
signed char smlt_sfI2c_rcvByte(smlt_sfI2c_eng_t *pstSfI2c_eng, char ack)
{
    char i;
    char rcv = 0;
    
    if(pstSfI2c_eng == NULL)
    {
        return -1;
    }
    //SDA_IN();
    pstSfI2c_eng->i2cPortModeSet(SMLT_I2C_SDA, SMLT_I2C_OUTPUT);
    for(i=0; i < 8; i++)
    {
        //Clr_IIC_SCL; 
        pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_LOW);
        //DelayXus(2);
        smlt_delayUs(1); 
        //Set_IIC_SCL;
        pstSfI2c_eng->i2cPortSet(SMLT_I2C_SCL, SMLT_I2C_PORT_HIGH);
        rcv<<=1;
        if(pstSfI2c_eng->i2cPortGet(SMLT_I2C_SDA))
        {
            rcv++;
        }
        //DelayXus(1);
        smlt_delayUs(1);
    }                     
    if (!ack)
    {
        //IIC_NAck();
        smlt_sfI2c_Nack(pstSfI2c_eng);
    }
    else
    {
        //IIC_Ack();
        smlt_sfI2c_ack(pstSfI2c_eng)
    }
    return rcv;
}


