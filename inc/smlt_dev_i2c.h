#ifndef __SMLT_DEV_I2C_H
#define __SMLT_DEV_I2C_H


#ifdef __cplusplus
extern "C" {
#endif

#define SMLT_I2C_PORT_HIGH 
#define SMLT_I2C_PORT_LOW
#define SMLT_I2C_SDA
#define SMLT_I2C_SCL
#define SMLT_I2C_OUTPUT
#define SMLT_I2C_INPUT

typedef char (*smlt_i2cPortModeSet)(char, char);
typedef char (*smlt_i2cPortSet)(char, char);
typedef char (*smlt_i2cPortGet)(char);


typedef struct _smlt_sfI2c_eng
{
    smlt_i2cPortModeSet i2cPortModeSet;
    smlt_i2cPortSet     i2cPortSet;
    smlt_i2cPortGet     i2cPortGet;
}smlt_sfI2c_eng_t;

smlt_sfI2c_eng_t* smlt_softI2c_new(char* cfg, void *modeSetFunc, void *IoSetFunc);


void IIC_Init(void);                           
void IIC_Start(void);          
void IIC_Stop(void);            
void IIC_Send_Byte(uint8_t txd);      
uint8_t IIC_Read_Byte(unsigned char ack);
uint8_t IIC_Wait_Ack(void);         
void IIC_Ack(void);                
void IIC_NAck(void);            

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);   


#ifdef __cplusplus
};
#endif


#endif


