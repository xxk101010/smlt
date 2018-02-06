#ifndef __SMLT_SOFT_I2C_H
#define __SMLT_SOFT_I2C_H


#ifdef __cplusplus
extern "C" {
#endif

#define SMLT_I2C_PORT_HIGH 
#define SMLT_I2C_PORT_LOW
#define SMLT_I2C_SDA
#define SMLT_I2C_SCL
#define SMLT_I2C_OUTPUT
#define SMLT_I2C_INPUT
#define SMLT_I2C_NACK                      ((char)0)
#define SMLT_I2C_ACK                       ((char)1)

typedef char (*smlt_i2cPortModeSet)(char, char);
typedef char (*smlt_i2cPortSet)(char, char);
typedef char (*smlt_i2cPortGet)(char);

typedef struct _smlt_sfI2c_eng
{
    smlt_i2cPortModeSet i2cPortModeSet;
    smlt_i2cPortSet     i2cPortSet;
    smlt_i2cPortGet     i2cPortGet;
}smlt_sfI2c_eng_t;

smlt_sfI2c_eng_t* smlt_softI2c_new(char* cfg, void *modeSetFunc, void *IoSetFunc, void *ioGetFunc);
signed char smlt_sfI2c_start(smlt_sfI2c_eng_t *pstSfI2c_eng);
signed char smlt_sfI2c_stop(smlt_sfI2c_eng_t *pstSfI2c_eng);
signed char smlt_sfI2c_ack_wait(smlt_sfI2c_eng_t *pstSfI2c_eng);
signed char smlt_sfI2c_ack(smlt_sfI2c_eng_t *pstSfI2c_eng);
signed char smlt_sfI2c_Nack(smlt_sfI2c_eng_t *pstSfI2c_eng);
signed char smlt_sfI2c_TxdByte(smlt_sfI2c_eng_t *pstSfI2c_eng, char txd);
signed char smlt_sfI2c_rcvByte(smlt_sfI2c_eng_t *pstSfI2c_eng, char ack)
 
#ifdef __cplusplus
};
#endif

#endif

