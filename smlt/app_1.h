
#ifndef __app
#define __app    

#include "stm32f1xx_hal.h"

#include "cmsis_os.h"


#define  Device_Okay       1
#define  Device_No_Okay       0

#define  Device_Type_ID    0xE4

#define  version    0x0105

#define  Device_Channel_Number    12

#define  Fore_Time    15//  调整可控硅前余量时间    Fore_Time + Last_Time+Effective_time =400；

#define  Last_Time    10   //  调整可控硅后余量时间


//#define Switch_On(n)   1// MODIFY_REG(GPIOC->ODR,(uint32_t)1<<n,(uint32_t)1<<n)

//#define Switch_Off(n)   1//MODIFY_REG(GPIOC->ODR,(uint32_t)1<<n,(uint32_t)0x00000000) 

#define Switch_Off(n)                                                                                  \
                                                              {                                                                      \
                                                                    if(n<7)                                                               \
                                                                 {                                                                      \
                                                                        MODIFY_REG(GPIOB->ODR,(uint32_t)(1<<(9-n)),(uint32_t)(1<<(9-n)));       \
                                                                 }                                                                      \
                                                                 else if(n<12)                                                          \
                                                                 {                                                                      \
                                                                        MODIFY_REG(GPIOB->ODR,(uint32_t)(1<<(n+3)),(uint32_t)(1<<(n+3)));       \
                                                                 }                                                                      \
                                                                }
                                                             
#define Switch_On(n)                                                                               \
                                                         {                                                                      \
                                                             if(n<7)                                                                \
                                                             {                                                                      \
                                                                    MODIFY_REG(GPIOB->ODR,(uint32_t)1<<(9-n),(uint32_t)0);              \
                                                             }                                                                      \
                                                             else if(n<12)                                                          \
                                                             {                                                                      \
                                                                    MODIFY_REG(GPIOB->ODR,(uint32_t)1<<(n+3),(uint32_t)0);              \
                                                             }                                                                      \
                                                       }                                                                      

                                                         
#define Key_OUT()  MODIFY_REG(GPIOA->CRL,(uint32_t)0x00000F00,(uint32_t)0x00000300)

#define Key_IN()  MODIFY_REG(GPIOA->CRL,(uint32_t)0x00000F00,(uint32_t)0x00000400)

#define Key_mode  ((GPIOA->CRL)&0x00000300)                                                         

                                                    
#define  Effective_time    300//有效时间

#define  Effective_use_time(a)    Effective_time*Device_Set_Pra.Memmory_9.Device_Max_Level[a]/255  //有效使用时间，即max中的时间

#define  Effective_no_use_time(a)  Effective_time -Effective_use_time(a)+2     //没有使用的有效时间

#define  Protect_time    10                                                                                                                                                                                                                                            1

#define  Total_time    Fore_Time +Effective_time

#define  Silicon_Control_Time   20

#define  L_To_T(n,a)      (uint32_t)((n*Effective_use_time(a))/255)
                                                         
//#define  L_To_T_ALL(n,a)      (uint32_t)((n*Effective_time (a))/255)                                                     

#define  T_To_L(n,a)       (uint32_t)(255*n/Effective_use_time(a))


typedef union _Device_Switch_Flag
{  
    uint16_t Device_Switch_Flag_HD;  
    struct  
    {  
            uint16_t bit0:1;  
            uint16_t bit1:1;  
            uint16_t bit2:1;
          uint16_t bit3:1; 
          uint16_t bit4:1;
          uint16_t bit5:1;
          uint16_t bit6:1;
           uint16_t bit7:1;  
      uint16_t bit8:1;     
      uint16_t bit9:1;     
      uint16_t bit10:1; 
      uint16_t bit11:1;     
          uint16_t bit12:1;
          uint16_t bit13:1;
          uint16_t bit14:1;
           uint16_t bit15:1;
    }bit;  
    
}Device_Switch_Flag_t;
 

#pragma  pack(1)
typedef struct _Memmory_1_Pra
{
    uint8_t  Device_Type;
    
    uint8_t  Device_Box;          
    
    uint8_t  Device_version[2];        //
    
    uint8_t   reserve_1[3];         //
    
    Device_Switch_Flag_t   Device_Switch_Flag;         
 
  //uint8_t   reserve_2;         //    
    
    uint8_t   Device_Duplic_Flag;         //
    
    uint8_t   reserve_3[6];
    
}Memmory_1_t;

#pragma  pack(1)
typedef struct _Memmory_2_Pra
{
    
    uint8_t   reserve_1[16];         //
    
}Memmory_2_t;

#pragma  pack(1)
typedef struct _Memmory_3_Pra
{
    
    uint8_t   reserve_1[16];         //
    
}Memmory_3_t;

#pragma  pack(1)
typedef struct _Memmory_4_Pra
{

    uint8_t   reserve_1[16];         //
    
}Memmory_4_t;

#pragma  pack(1)
typedef struct _Memmory_5_Pra
{

    
    uint8_t   reserve_1[16];         //
    
}Memmory_5_t;


#pragma  pack(1)
typedef struct _Memmory_6_Pra
{
    uint8_t   Aux_Push[8];         //
    uint8_t   Aux_Release[8];
    
}Memmory_6_t;



#pragma  pack(1)
typedef struct _Memmory_7_Pra
{
    uint8_t   Device_Area[12];         //
    
    uint8_t   Device_Jonn_1[4];         //
    
}Memmory_7_t; 

#pragma  pack(1)
typedef struct _Memmory_8_Pra
{
    uint8_t   Device_Jonn_2[8];         //
    
    uint8_t   Device_Set_Logic_Channel_1[8];
    
}Memmory_8_t;

#pragma  pack(1)
typedef struct _Memmory_9_Pra
{
    
    uint8_t   Device_Set_Logic_Channel_2[4];       //
    
    uint8_t   Device_Max_Level[12];         //
    
//uint8_t   reserve_2[4];         //    
    
}Memmory_9_t;


#pragma  pack(1)
typedef struct _Memmory_10_Pra
{
    uint8_t   reserve_1[12];         //
    
    uint8_t   Device_Switch_On_Delay_Time[4];         //
    
    
}Memmory_10_t;

#pragma  pack(1)
typedef struct _Memmory_11_Pra
{
    uint8_t   Device_Switch_On_Delay_Time[8];         //
    
    //uint8_t   reserve_1[4];         //
    
    uint8_t   Device_Switch_Off_Delay_Time[8];         //
    
}Memmory_11_t;


#pragma  pack(1)
typedef struct _Memmory_12_Pra
{
//    uint8_t    reserve_1[4];
    
    uint8_t   Device_Switch_Off_Delay_Time[4]; 
    
  uint8_t    Device_Switch_Level[12];         //
    
//    uint8_t    reserve_2[4];

    
}Memmory_12_t;


#pragma  pack(1)
typedef struct _Memmory_13_Pra
{
    
    uint8_t   reserve_1[16];         //
    
}Memmory_13_t;


#pragma  pack(1)
typedef struct _Memmory_14_Pra
{
    uint8_t   reserve_1[16];         //
    
}Memmory_14_t;


#pragma  pack(1)
typedef struct _Memmory_15_Pra
{
    uint8_t   reserve_1[16];         //
    
}Memmory_15_t;


#pragma  pack(1)
typedef struct _Memmory_16_Pra
{
    uint8_t   Device_Preset_1[12];         //
    
    uint8_t   Device_Preset_2[4];         //
    
}Memmory_16_t;


#pragma  pack(1)
typedef struct _Memmory_17_Pra
{
    uint8_t   Device_Preset_2[8];         //     
  
  uint8_t   Device_Preset_3[8];         //    
    
}Memmory_17_t;


#pragma  pack(1)
typedef struct _Memmory_18_Pra
{
    uint8_t   Device_Preset_3[4];         //
    
    uint8_t   Device_Preset_4[12];         //
    
}Memmory_18_t;


#pragma  pack(1)
typedef struct _Memmory_19_Pra
{
    uint8_t   Device_Preset_5[12];         //
    
    uint8_t   Device_Preset_6[4];         //
    
}Memmory_19_t;

#pragma  pack(1)
typedef struct _Memmory_20_Pra
{
    uint8_t   Device_Preset_6[8];         //
    
    uint8_t   Device_Preset_7[8];         //
    
}Memmory_20_t;

#pragma  pack(1)
typedef struct _Memmory_21_Pra
{
    uint8_t   Device_Preset_7[4];         //
    
    uint8_t   Device_Preset_8[12];         //
    
}Memmory_21_t;


#pragma  pack(1)
typedef struct _Memmory_22_Pra
{
    uint8_t   Device_Preset_9[12];         //
    
    uint8_t   Device_Preset_10[4];         //
    
}Memmory_22_t;


#pragma  pack(1)
typedef struct _Memmory_23_Pra
{
    uint8_t   Device_Preset_10[8];         //
    
    uint8_t   Device_Preset_11[8];         //
    
}Memmory_23_t;


#pragma  pack(1)
typedef struct _Memmory_24_Pra
{
    uint8_t   Device_Preset_11[4];         //
    
    uint8_t   Device_Preset_12[12];         //
    
}Memmory_24_t;

#pragma  pack(1)
typedef struct _Memmory_25_Pra
{
    uint8_t   Device_Preset_13[12];         //
    
    uint8_t   Device_Preset_14[4];         //
    
}Memmory_25_t;

#pragma  pack(1)
typedef struct _Memmory_26_Pra
{
    uint8_t   Device_Preset_14[8];         //
    
    uint8_t   Device_Preset_15[8];         //
    
}Memmory_26_t;


#pragma  pack(1)
typedef struct _Memmory_27_Pra
{
    uint8_t   Device_Preset_15[4];         //
    
    uint8_t   Device_Preset_16[12];         //
    
}Memmory_27_t;


#pragma  pack(1)
typedef struct _Memmory_28_Pra
{
    uint8_t   level_save[12]; 
    
    uint8_t   reserve_16[4];         //
    
    
}Memmory_28_t;


#pragma  pack(1)
typedef struct _Memmory_29_Pra
{ 
    
    uint8_t   reserve_16[16];         //
    
}Memmory_29_t;


#pragma  pack(1)
typedef struct _Memmory_30_Pra
{ 
    
    uint8_t   reserve_16[16];         //
    
}Memmory_30_t;

#pragma  pack(1)
typedef struct _Memmory_31_Pra
{ 
    
    uint8_t   reserve_16[16];         //
    
}Memmory_31_t;

#pragma  pack(1)
typedef struct _Memmory_32_Pra
{ 
    
    uint8_t   reserve_16[16];         //
    
}Memmory_32_t;

#pragma  pack(1)
typedef struct _Memmory_33_Pra
{ 
    
    uint8_t   reserve_16[16];         //
    
}Memmory_33_t;


#pragma  pack(1)
typedef struct _Memmory_34_Pra
{ 
    
    uint8_t   reserve_16[16];         //
    
}Memmory_34_t;

#pragma  pack(1)
typedef struct _Memmory_35_Pra
{ 
    
    uint8_t   set_save[16];         //
    
}Memmory_35_t;

#pragma  pack(1)
typedef struct _Memmory_36_Pra
{ 
    
    uint8_t   reserve_16[16];         //
    
}Memmory_36_t;

#pragma  pack(4)
typedef struct _Device_Pra
{

    Memmory_1_t  Memmory_1;
    Memmory_2_t  Memmory_2;
    Memmory_3_t  Memmory_3;
    Memmory_4_t  Memmory_4;
    Memmory_5_t  Memmory_5;
    Memmory_6_t  Memmory_6;
    Memmory_7_t  Memmory_7;
    Memmory_8_t  Memmory_8;
    Memmory_9_t  Memmory_9;
    Memmory_10_t  Memmory_10;
    Memmory_11_t  Memmory_11;
    Memmory_12_t  Memmory_12;
    Memmory_13_t  Memmory_13;
    Memmory_14_t  Memmory_14;
    Memmory_15_t  Memmory_15;
    Memmory_16_t  Memmory_16;
    Memmory_17_t  Memmory_17;
    Memmory_18_t  Memmory_18;
    Memmory_19_t  Memmory_19;
    Memmory_20_t  Memmory_20;
    Memmory_21_t  Memmory_21;
    Memmory_22_t  Memmory_22;
    Memmory_23_t  Memmory_23;
    Memmory_24_t  Memmory_24;
    Memmory_25_t  Memmory_25;
    Memmory_26_t  Memmory_26;
    Memmory_27_t  Memmory_27;
    Memmory_28_t  Memmory_28;
    Memmory_29_t  Memmory_29;
    Memmory_30_t  Memmory_30;
    Memmory_31_t  Memmory_31;
    Memmory_32_t  Memmory_32;
    Memmory_33_t  Memmory_33;
    Memmory_34_t  Memmory_34;
    Memmory_35_t  Memmory_35;
    Memmory_36_t  Memmory_36[90];
}Device_Set_Pra_t;                  // 存EE的参数


typedef enum _Switch_state
{
    Switch_Off=0,
    
    Switch_On=1,
    
    Switch_On_to_Off,
    
    Switch_Off_to_On,
    
}Switch_statet_t;

#pragma  pack(1)

typedef struct _Device_Obj_Mage
{
    uint32_t   Device_Pre_Level;         // 为了使变化平稳，每次进入零点时才修改真正的time值
    
    uint32_t   Device_Pre_Time;         //
    
    uint32_t   Device_Current_Level;         //
    
    uint32_t   Device_Current_Time;         //  
    
    uint32_t   Device_Change_Level;         // 

    uint32_t   Device_Dest_Level;         //
    
    uint32_t   Device_Fade_Time;         //
    
    uint32_t   Device_Fade_Step;         //
    
    uint16_t   Device_Switch_On_Delay_Ct;         // 延时开计数器
    
    uint16_t   Device_Switch_Off_Delay_Ct;         // 延时关计数器
    
    Switch_statet_t  Device_Switch_state;         //     开关量状态
    
}Device_Obj_Mage_t;   //设备对象管理器


typedef enum 
{
    LED_SYS=0,
    
    LED_LOADDATA=1,
    
}LED_statet_t;

typedef struct _Device_Current_Pra
{
    uint8_t   Device_Current_Level[8];         //
    
}Device_Current_Prat_t;


extern uint16_t g_Curretn_EE_Addr; 

extern Device_Set_Pra_t Device_Set_Pra;

extern Device_Current_Prat_t Device_Current_Pra;

extern volatile Device_Obj_Mage_t   Device_Obj_Mage[12];

extern uint16_t  g_Device_Zero_EXTI_Ct;

extern uint8_t g_device_state;

extern uint8_t run_ct;

extern uint8_t data_Y_ct;

extern uint16_t  g_Device_Zero_EXTI_make_Ct;


void Device_Intial(void);

void Device_Switch_Fuc_Process(uint8_t area_number, uint8_t logic_channel,uint8_t device_level,uint32_t fade_time,uint8_t stop_flag,uint8_t device_join);

void Device_Switch_Management(void);

void Device_Switch(uint8_t physic_channel, Switch_statet_t switch_statet);

void Device_Adjuts_Management(void);

//void Device_Adj_Level_Request(uint8_t* actual_level,uint8_t* target_level,uint8_t area_number, uint8_t logic_channel);
uint8_t Device_Adj_Level_Request(uint8_t* actual_level,uint8_t* target_level,uint8_t area_number, uint8_t logic_channel);
//void Device_Preset_Process(uint8_t area_number,uint8_t preset_number,uint32_t fade_time);
void Device_Preset_Process(uint8_t area_number,uint8_t preset_number,uint32_t fade_time,uint8_t device_join);

void Device_Switch_Channel(uint8_t channel_number,uint8_t channel_state);

void Normal_Work_Mode_Func(void);

void Device_AUX_Push_Fuc(void);

void Device_AUX_Release_Fuc(void);

void Light_Init(void);
void device_channel_set(uint8_t physic_channel,uint8_t device_level,uint32_t fade_time);

void LED_multi_func(LED_statet_t LED_state);

uint8_t Device_preset_Level_save(uint8_t area_number, uint8_t set_num, uint8_t join);

uint8_t Device_preset_search(uint8_t area_number,uint8_t join);

#endif 

