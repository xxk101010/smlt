#ifndef __24CXX_H
#define __24CXX_H

#include "smlt_common.h"
#include "smlt_soft_i2c.h"  

//#define  SMLT_AT24CXX_HARDBUS_I2C
#ifdef __cplusplus
extern "C" {
#endif

typedef enum _smlt_AT24cxx_types
{
    SMLT_DEV_AT24C01 = 0,
    SMLT_DEV_AT24C02,
    SMLT_DEV_AT24C04,
    SMLT_DEV_AT24C08,
    SMLT_DEV_AT24C16,
    SMLT_DEV_AT24C32,
    SMLT_DEV_AT24C64,
    SMLT_DEV_AT24C128,
    SMLT_DEV_AT24C256,
    SMLT_DEV_AT24SUM;
}smlt_AT24cxx_types_t;

typedef struct _smlt_AT24cxx_eng
{
    smlt_AT24cxx_types_t dev_types;
    smlt_sfI2c_eng_t    i2c_eng;
    char                sla_type;
    char                Aval;
}smlt_AT24cxx_eng_t;


//#define SMLT_DEV_AT24C64_ADDR         0XA0
//#define IIC_DEV_TYPE_1                1
//#define IIC_DEV_TYPE_2                2
//#define IIC_DEV_10BITS                3
                       
unsigned char AT24CXX_ReadOneByte(unsigned char sla, unsigned char suba_type, unsigned short int ReadAddr);                    
void AT24CXX_WriteOneByte(unsigned char sla, unsigned char suba_type, unsigned short int WriteAddr, unsigned char DataToWrite);  
void AT24CXX_WriteLenByte(unsigned char sla, unsigned char suba_type, unsigned short int WriteAddr, unsigned int DataToWrite, unsigned char Len);
unsigned int AT24CXX_ReadLenByte(    unsigned char sla, unsigned char suba_type, unsigned short int ReadAddr, unsigned char Len); 
void AT24CXX_Write(unsigned char sla, unsigned char suba_type, unsigned short int WriteAddr, unsigned char *pBuffer,
                                        unsigned short int NumToWrite);    
void AT24CXX_Read(unsigned char sla,
                                    unsigned char suba_type,
                                    unsigned short int ReadAddr,
                                    unsigned char *pBuffer,
                                    unsigned short int NumToRead);     

unsigned char AT24CXX_Check(unsigned char sla,
                                                        unsigned char suba_type);
                                                        
void AT24CXX_Init(void); 


#endif

