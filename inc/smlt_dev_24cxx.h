#ifndef __24CXX_H
#define __24CXX_H

#include "smlt_soft_i2c.h"  

#ifdef __cplusplus
extern "C" {
#endif


typedef enum _smlt_AT24xx_types
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
}smlt_AT24xx_types_t;

#define SMLT_DEV_24CXX_NAME           SMLT_DEV_AT24C16 

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









