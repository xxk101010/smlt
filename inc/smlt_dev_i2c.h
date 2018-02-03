#ifndef __SMLT_DEV_I2C_H
#define __SMLT_DEV_I2C_H

//#include "stm32f0xx_hal.h"



#define SCL_OUT()  MODIFY_REG(GPIOC->MODER,(uint32_t)0x30000000,(uint32_t)0x10000000)

#define SDA_OUT()  MODIFY_REG(GPIOC->MODER,(uint32_t)0x0c000030,(uint32_t)0x04000000)

#define SDA_IN()   MODIFY_REG(GPIOC->MODER,(uint32_t)0x0c000030,(uint32_t)0x00000000)


//#define SCL_OUT()  MODIFY_REG(GPIOC->CRH,(uint32_t)0x000F0000,(uint32_t)0x00030000)

//#define SDA_OUT()  MODIFY_REG(GPIOC->CRH,(uint32_t)0x0000F000,(uint32_t)0x00003000)

//#define SDA_IN()   MODIFY_REG(GPIOC->CRH,(uint32_t)0x0000F000,(uint32_t)0x00004000)




//IO��������	 


#define Set_IIC_SCL   MODIFY_REG(GPIOC->ODR,GPIO_PIN_14,GPIO_PIN_14)
#define Clr_IIC_SCL   MODIFY_REG(GPIOC->ODR,GPIO_PIN_14,(uint32_t)0x00000000) 


#define Set_IIC_SDA   MODIFY_REG(GPIOC->ODR,GPIO_PIN_13,GPIO_PIN_13)
#define Clr_IIC_SDA   MODIFY_REG(GPIOC->ODR,GPIO_PIN_13,(uint32_t)0x00000000)


  //����SDA 
#define READ_SDA    (GPIOC->IDR & GPIO_PIN_13)


//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
















