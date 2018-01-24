

#include "app.h"

#include "protoal.h"

#include "string.h"

#include "delay.h"

#include "24cxx.h" 

#include "usart.h"


extern TIM_HandleTypeDef htim2;

uint8_t g_device_state;

uint8_t run_ct;

uint8_t data_Y_ct;

Device_Set_Pra_t Device_Set_Pra;

volatile Device_Obj_Mage_t   Device_Obj_Mage[12];

Device_Current_Prat_t Device_Current_Pra;

uint16_t  g_Device_Zero_EXTI_Ct=0;

uint16_t  g_Device_Zero_EXTI_make_Ct=0;


uint16_t g_Curretn_EE_Addr = 0;  //读写EE地址

void Device_Intial(void)
{

    AT24CXX_Init(); //初始化IIC
    
    Device_Set_Pra.Memmory_1.Device_version[0] = (uint8_t)(version>>8);
    
    Device_Set_Pra.Memmory_1.Device_version[1] = (uint8_t)version;
    
    AT24CXX_WriteOneByte(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1, 2,Device_Set_Pra.Memmory_1.Device_version[0]);
    
    DelayXus(1000);
    
    AT24CXX_WriteOneByte(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1, 3,Device_Set_Pra.Memmory_1.Device_version[1]);
    
    DelayXus(1000);

    DelayXus(1000);
    
    if(AT24CXX_ReadOneByte(AT24C64_ADDR, IIC_DEV_ADDR_TYPE_1, 2)!=Device_Set_Pra.Memmory_1.Device_version[0])  //读取设备号不对
    {
    while(1);
    }    
    
    if(AT24CXX_ReadOneByte(AT24C64_ADDR, IIC_DEV_ADDR_TYPE_1, 3)!=Device_Set_Pra.Memmory_1.Device_version[1])  //读取设备号不对
    {
    while(1);
    }
    
    if(AT24CXX_ReadOneByte(AT24C64_ADDR, IIC_DEV_ADDR_TYPE_1, 0)!=Device_Type_ID)  //读取设备号不对
    {
        g_device_state=Device_No_Okay;
    }    
    else
    {
        g_device_state= Device_Okay;
    AT24CXX_Read(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1,0,(uint8_t *)&Device_Set_Pra.Memmory_1.Device_Type,768); 
    }
    
}


     
//主控函数，当device_level为FF表示灭掉，0表示全开，fade_time为0 表示开关
void Device_Switch_Fuc_Process(uint8_t area_number, uint8_t logic_channel,uint8_t device_level,uint32_t fade_time,uint8_t stop_flag,uint8_t device_join)  
{
    uint8_t i;

    for(i=0;i<4;i++)
    {    
            if(((area_number==Device_Set_Pra.Memmory_7.Device_Area[i])||(area_number==0))&&((logic_channel==Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i])||(logic_channel==0XFF)))
            {  
                   if((device_join & Device_Set_Pra.Memmory_7.Device_Jonn_1[i])==0)
                    {
                        continue;
                    }        
                    if(device_level==0)
                    {
                        continue;
                    }                   
                    if(fade_time==0) //渐变时间为0，说明是设置亮度
                    {
                                 if(stop_flag==SET)
                                 {
                                     Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
                                     Device_Obj_Mage[i].Device_Fade_Time=0;
                                     Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level;
                                 }
                                 else
                                 {
                                      if((Device_Set_Pra.Memmory_1.Device_Switch_Flag.Device_Switch_Flag_HD>>i)&0x01)  //不是开关量状态
                                        {
                                             Device_Obj_Mage[i].Device_Dest_Level =device_level;
                                            
                                             Device_Obj_Mage[i].Device_Fade_Time = fade_time;
                                            
                                             Device_Obj_Mage[i].Device_Pre_Level=device_level;
                                             
                                             Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(device_level,i);
                                        }
                                        else 
                                        {   
                                                device_level = 0XFF-device_level;  
                                                if(device_level<=Device_Set_Pra.Memmory_12.Device_Switch_Level[i])  //&& (Device_Obj_Mage[i].Device_Switch_state==Switch_Off)
                                                {
                                                    Device_Obj_Mage[i].Device_Pre_Time=  Fore_Time+Effective_time;      
                                                }
                                                else if(device_level>=Device_Set_Pra.Memmory_12.Device_Switch_Level[i]) //&&(Device_Obj_Mage[i].Device_Switch_state==Switch_On)
                                                {
                                                    Device_Obj_Mage[i].Device_Pre_Time=Fore_Time;
                                                }    
                                         }                                            
                                 }
                            }
                            else
                            {
                                if(device_level>Device_Obj_Mage[i].Device_Current_Level)  
                                {
                                     
                                 Device_Obj_Mage[i].Device_Switch_state=Switch_On_to_Off;
                                    
                                 Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                                    
                                 Device_Obj_Mage[i].Device_Fade_Time = fade_time;
                                    
                                 Device_Obj_Mage[i].Device_Change_Level=device_level-Device_Obj_Mage[i].Device_Current_Level; 
                                                                                   
                                 Device_Obj_Mage[i].Device_Fade_Step=    Device_Obj_Mage[i].Device_Fade_Time/ Device_Obj_Mage[i].Device_Change_Level;
                                    
                                if(Device_Obj_Mage[i].Device_Fade_Step==0)
                                {
                                    Device_Obj_Mage[i].Device_Fade_Step=1;
                                }
                                    
                                 Device_Obj_Mage[i].Device_Dest_Level =device_level;
                                        
                                }
                                else if(device_level<Device_Obj_Mage[i].Device_Current_Level)   //渐亮
                                {
                                 Device_Obj_Mage[i].Device_Switch_state=Switch_Off_to_On;
                                    
                                 Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                                    
                                 Device_Obj_Mage[i].Device_Fade_Time= fade_time;//fade_time*10;
                                    
                                 Device_Obj_Mage[i].Device_Change_Level=Device_Obj_Mage[i].Device_Current_Level-device_level;                                   
                                    
                                 Device_Obj_Mage[i].Device_Fade_Step=   Device_Obj_Mage[i].Device_Fade_Time/ Device_Obj_Mage[i].Device_Change_Level;
                                    
                                if(Device_Obj_Mage[i].Device_Fade_Step==0)
                                {
                                    Device_Obj_Mage[i].Device_Fade_Step=1;
                                }
                                                                 
                                 Device_Obj_Mage[i].Device_Dest_Level =device_level;
                                }
                            }
        }
    }
    for(i=4;i<8;i++)
    {
            if(((area_number==Device_Set_Pra.Memmory_7.Device_Area[i])||(area_number==0))&&((logic_channel==Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i])||(logic_channel==0XFF)))
        {       
                
                 if((device_join & Device_Set_Pra.Memmory_8.Device_Jonn_2[i-4])==0)
                    {
           continue;
                    }        
                    if(device_level==0)
                    {
                        continue;
                    }
                              if(fade_time==0) //渐变时间为0，说明是设置亮度
                              {
                                 if(stop_flag==SET)
                                 {
                                     Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
                                     Device_Obj_Mage[i].Device_Fade_Time=0;
                                     Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level;
                                 }
                                 else
                                 {
                                      if((Device_Set_Pra.Memmory_1.Device_Switch_Flag.Device_Switch_Flag_HD>>i)&0x01)  //不是开关量状态
                                        {
                                              Device_Obj_Mage[i].Device_Dest_Level =device_level;
                                            
                                             Device_Obj_Mage[i].Device_Fade_Time = fade_time;
                                            
                                             Device_Obj_Mage[i].Device_Pre_Level=device_level;
                                             
                                             Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(device_level,i);
                                        }
                    else  //开关量状态
                                        {   
                                              device_level=0XFF-device_level;  
                                            if(device_level<=Device_Set_Pra.Memmory_12.Device_Switch_Level[i])  //&& (Device_Obj_Mage[i].Device_Switch_state==Switch_Off)
                                                {
                           //Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(0XFF,i);
                                                     Device_Obj_Mage[i].Device_Pre_Time= Fore_Time+Effective_time;
                                                    
                                                }
                                                else if(device_level>=Device_Set_Pra.Memmory_12.Device_Switch_Level[i]) //&&(Device_Obj_Mage[i].Device_Switch_state==Switch_On)
                                                {
                          //Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(0,i);
                                                     Device_Obj_Mage[i].Device_Pre_Time= Fore_Time;
                                                }    
                    }                                            
                                     
                                 //Device_Obj_Mage[i].Device_Pre_Time=(L_To_T(device_level)*(255-Device_Set_Pra.Memmory_9.Device_Max_Level[i]))/255;    
                                 }
                            }
                            else
                            {
                                if(device_level>Device_Obj_Mage[i].Device_Current_Level)       //渐暗
                                {
                                     
                                 Device_Obj_Mage[i].Device_Switch_state=Switch_On_to_Off;
                                    
                                 Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                                    
                                 Device_Obj_Mage[i].Device_Fade_Time = fade_time;
                                    
                                 Device_Obj_Mage[i].Device_Change_Level=device_level-Device_Obj_Mage[i].Device_Current_Level; 
                                                                                   
                                 Device_Obj_Mage[i].Device_Fade_Step=    Device_Obj_Mage[i].Device_Fade_Time/ Device_Obj_Mage[i].Device_Change_Level;
                                    
                                if(Device_Obj_Mage[i].Device_Fade_Step==0)
                                {
                                    Device_Obj_Mage[i].Device_Fade_Step=1;
                                }
                                    
                                 Device_Obj_Mage[i].Device_Dest_Level =device_level;
                                    
                                }
                                else if(device_level<Device_Obj_Mage[i].Device_Current_Level)   //渐亮
                                {
                                 Device_Obj_Mage[i].Device_Switch_state=Switch_Off_to_On;
                                    
                                 Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                                    
                                 Device_Obj_Mage[i].Device_Fade_Time= fade_time;//fade_time*10;
                                    
                                 Device_Obj_Mage[i].Device_Change_Level=Device_Obj_Mage[i].Device_Current_Level-device_level;                                   
                                    
                                 Device_Obj_Mage[i].Device_Fade_Step=    Device_Obj_Mage[i].Device_Fade_Time/ Device_Obj_Mage[i].Device_Change_Level;
                                    
                                if(Device_Obj_Mage[i].Device_Fade_Step==0)
                                {
                                    Device_Obj_Mage[i].Device_Fade_Step=1;
                                }
                                                                 
                                 Device_Obj_Mage[i].Device_Dest_Level =device_level;
                                }
                            }
                       
    }    
            
    }
    for(i=8;i<12;i++)
    {
        if(((area_number==Device_Set_Pra.Memmory_7.Device_Area[i])||(area_number==0))&&((logic_channel==Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8])||(logic_channel==0XFF)))
        {       
                
                 if((device_join & Device_Set_Pra.Memmory_8.Device_Jonn_2[i-4])==0)
                    {
           continue;
                    }        
                    if(device_level==0)
                    {
                        continue;
                    }
                              if(fade_time==0) //渐变时间为0，说明是设置亮度
                              {
                                 if(stop_flag==SET)
                                 {
                                     Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
                                     Device_Obj_Mage[i].Device_Fade_Time=0;
                                     Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level;
                                 }
                                 else
                                 {
                                      if((Device_Set_Pra.Memmory_1.Device_Switch_Flag.Device_Switch_Flag_HD>>i)&0x01)  //不是开关量状态
                                        {
                                              Device_Obj_Mage[i].Device_Dest_Level =device_level;
                                            
                                             Device_Obj_Mage[i].Device_Fade_Time = fade_time;
                                            
                                             Device_Obj_Mage[i].Device_Pre_Level=device_level;
                                             
                                             Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(device_level,i);
                                        }
                    else  //开关量状态
                                        {   
                                              device_level=0XFF-device_level;  
                                            if(device_level<=Device_Set_Pra.Memmory_12.Device_Switch_Level[i])  //&& (Device_Obj_Mage[i].Device_Switch_state==Switch_Off)
                                                {
                           //Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(0XFF,i);
                                                     Device_Obj_Mage[i].Device_Pre_Time= Fore_Time+Effective_time;
                                                    
                                                }
                                                else if(device_level>=Device_Set_Pra.Memmory_12.Device_Switch_Level[i]) //&&(Device_Obj_Mage[i].Device_Switch_state==Switch_On)
                                                {
                          //Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(0,i);
                                                     Device_Obj_Mage[i].Device_Pre_Time= Fore_Time;
                                                }    
                    }                                            
                                     
                                 //Device_Obj_Mage[i].Device_Pre_Time=(L_To_T(device_level)*(255-Device_Set_Pra.Memmory_9.Device_Max_Level[i]))/255;    
                                 }
                            }
                            else
                            {
                                if(device_level>Device_Obj_Mage[i].Device_Current_Level)       //渐暗
                                {
                                     
                                 Device_Obj_Mage[i].Device_Switch_state=Switch_On_to_Off;
                                    
                                 Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                                    
                                 Device_Obj_Mage[i].Device_Fade_Time = fade_time;
                                    
                                 Device_Obj_Mage[i].Device_Change_Level=device_level-Device_Obj_Mage[i].Device_Current_Level; 
                                                                                   
                                 Device_Obj_Mage[i].Device_Fade_Step=    Device_Obj_Mage[i].Device_Fade_Time/ Device_Obj_Mage[i].Device_Change_Level;
                                    
                                if(Device_Obj_Mage[i].Device_Fade_Step==0)
                                {
                                    Device_Obj_Mage[i].Device_Fade_Step=1;
                                }
                                    
                                 Device_Obj_Mage[i].Device_Dest_Level =device_level;
                                    
                                }
                                else if(device_level<Device_Obj_Mage[i].Device_Current_Level)   //渐亮
                                {
                                 Device_Obj_Mage[i].Device_Switch_state=Switch_Off_to_On;
                                    
                                 Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                                    
                                 Device_Obj_Mage[i].Device_Fade_Time= fade_time;//fade_time*10;
                                    
                                 Device_Obj_Mage[i].Device_Change_Level=Device_Obj_Mage[i].Device_Current_Level-device_level;                                   
                                    
                                 Device_Obj_Mage[i].Device_Fade_Step=    Device_Obj_Mage[i].Device_Fade_Time/ Device_Obj_Mage[i].Device_Change_Level;
                                    
                                if(Device_Obj_Mage[i].Device_Fade_Step==0)
                                {
                                    Device_Obj_Mage[i].Device_Fade_Step=1;
                                }
                                                                 
                                 Device_Obj_Mage[i].Device_Dest_Level =device_level;
                                }
                            }
                       
    }    
            
    }    
}


void device_channel_set(uint8_t physic_channel,uint8_t device_level,uint32_t fade_time)
{
        
                if(device_level==0)
                {
                    return;
                }
                 if(fade_time==0) //渐变时间为0，说明是设置亮度
                {
                    if((Device_Set_Pra.Memmory_1.Device_Switch_Flag.Device_Switch_Flag_HD>>physic_channel)&0x01)  //不是开关量状态
                    {
                         Device_Obj_Mage[physic_channel].Device_Dest_Level =device_level;
                        
                         Device_Obj_Mage[physic_channel].Device_Fade_Time = fade_time;
                        
                         Device_Obj_Mage[physic_channel].Device_Pre_Level=device_level;
                         
                         Device_Obj_Mage[physic_channel].Device_Pre_Time= Effective_no_use_time(physic_channel)+L_To_T(device_level,physic_channel);
                    }
                    else  //开关量状态
                    {   
                            device_level=0XFF-device_level;  
                            if(device_level<=Device_Set_Pra.Memmory_12.Device_Switch_Level[physic_channel])  //&& (Device_Obj_Mage[i].Device_Switch_state==Switch_Off)
                            {
                                Device_Obj_Mage[physic_channel].Device_Pre_Time=  Fore_Time+Effective_time;
                            }
                            else if(device_level>=Device_Set_Pra.Memmory_12.Device_Switch_Level[physic_channel]) //&&(Device_Obj_Mage[i].Device_Switch_state==Switch_On)
                            {                
                                Device_Obj_Mage[physic_channel].Device_Pre_Time=Fore_Time;
                            }    
                    }                                            
            }
            else
            {
                if(device_level>Device_Obj_Mage[physic_channel].Device_Current_Level)       //渐暗
                {
                     
                 Device_Obj_Mage[physic_channel].Device_Switch_state=Switch_On_to_Off;
                    
                 Device_Obj_Mage[physic_channel].Device_Pre_Level=Device_Obj_Mage[physic_channel].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                    
                 Device_Obj_Mage[physic_channel].Device_Fade_Time = fade_time;
                    
                 Device_Obj_Mage[physic_channel].Device_Change_Level=device_level-Device_Obj_Mage[physic_channel].Device_Current_Level; 
                                                                            
                 Device_Obj_Mage[physic_channel].Device_Fade_Step=    Device_Obj_Mage[physic_channel].Device_Fade_Time/ Device_Obj_Mage[physic_channel].Device_Change_Level;
                    
                if(Device_Obj_Mage[physic_channel].Device_Fade_Step==0)
                {
                    Device_Obj_Mage[physic_channel].Device_Fade_Step=1;
                }
                    
                 Device_Obj_Mage[physic_channel].Device_Dest_Level =device_level;
                    
                }
                else if(device_level<Device_Obj_Mage[physic_channel].Device_Current_Level)   //渐亮
                {
                 Device_Obj_Mage[physic_channel].Device_Switch_state=Switch_Off_to_On;
                    
                 Device_Obj_Mage[physic_channel].Device_Pre_Level=Device_Obj_Mage[physic_channel].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                    
                 Device_Obj_Mage[physic_channel].Device_Fade_Time= fade_time;//fade_time*10;
                    
                 Device_Obj_Mage[physic_channel].Device_Change_Level=Device_Obj_Mage[physic_channel].Device_Current_Level-device_level;                                   
                    
                 Device_Obj_Mage[physic_channel].Device_Fade_Step=    Device_Obj_Mage[physic_channel].Device_Fade_Time/ Device_Obj_Mage[physic_channel].Device_Change_Level;
                    
                if(Device_Obj_Mage[physic_channel].Device_Fade_Step==0)
                {
                    Device_Obj_Mage[physic_channel].Device_Fade_Step=1;
                }
                                                 
                 Device_Obj_Mage[physic_channel].Device_Dest_Level =device_level;
                }
            }
    
}  



void Device_Adjuts_Management(void)
{
     uint8_t i=0;
  uint32_t device_level_1=0;
    static uint8_t fade_step[8];
    
    for(i=0;i<12;i++)
    {
            if(Device_Obj_Mage[i].Device_Fade_Time)
          {
                Device_Obj_Mage[i].Device_Fade_Time--;
             if(Device_Obj_Mage[i].Device_Fade_Time==0&& Device_Obj_Mage[i].Device_Pre_Level!=Device_Obj_Mage[i].Device_Dest_Level)
             {
                 Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Dest_Level;
                 Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(Device_Obj_Mage[i].Device_Pre_Level,i);
                 
             }
                fade_step[i]++;
                if(fade_step[i]>=Device_Obj_Mage[i].Device_Fade_Step)
                {
                    fade_step[i]=0;
                    if(Device_Obj_Mage[i].Device_Switch_state==Switch_On_to_Off)
                    {
                      Device_Obj_Mage[i].Device_Pre_Level++;
                        
                        if((Device_Set_Pra.Memmory_1.Device_Switch_Flag.Device_Switch_Flag_HD>>i)&0x01)  //不是开关量状态
                        {
                            
                          Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(Device_Obj_Mage[i].Device_Pre_Level,i);
                        //Device_Obj_Mage[i].Device_Pre_Time=(L_To_T(Device_Obj_Mage[i].Device_Pre_Level)*(255-Device_Set_Pra.Memmory_9.Device_Max_Level[i]))/255;
                        }
                        else
                        {
                                device_level_1=(uint32_t)0Xff-Device_Obj_Mage[i].Device_Pre_Level;  
                                if(device_level_1<Device_Set_Pra.Memmory_12.Device_Switch_Level[i])  //&& (Device_Obj_Mage[i].Device_Switch_state==Switch_Off)
                                {
                                    // Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(0XFF,i);
                                     Device_Obj_Mage[i].Device_Pre_Time=  Effective_time;// +Fore_Time
                                }
                                else if(device_level_1>=Device_Set_Pra.Memmory_12.Device_Switch_Level[i]) //&&(Device_Obj_Mage[i].Device_Switch_state==Switch_On)
                                {
                                //     Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(0,i);
                                     Device_Obj_Mage[i].Device_Pre_Time= 2;
                                }    
                        }
                        if(Device_Obj_Mage[i].Device_Pre_Level>=Device_Obj_Mage[i].Device_Dest_Level)
                        {
                            Device_Obj_Mage[i].Device_Fade_Time=0;
                            Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Dest_Level;
                            Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
                            continue;
                        }
                        
                        if(Device_Obj_Mage[i].Device_Change_Level==0)
                        {
                            Device_Obj_Mage[i].Device_Fade_Step=1;
                        }
                        else
                        {    
                         Device_Obj_Mage[i].Device_Change_Level--;
                        }
                    }
                    else if(Device_Obj_Mage[i].Device_Switch_state==Switch_Off_to_On)
                    {
                        if(Device_Obj_Mage[i].Device_Pre_Level>0)
                        {
                      Device_Obj_Mage[i].Device_Pre_Level--;
                        }                
                        if((Device_Set_Pra.Memmory_1.Device_Switch_Flag.Device_Switch_Flag_HD>>i)&0x01)  //不是开关量状态
                        {                        
                        Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(Device_Obj_Mage[i].Device_Pre_Level,i);
                        }
                        else
                        {
                                device_level_1=(uint32_t)0Xff-Device_Obj_Mage[i].Device_Pre_Level;  
                                if(device_level_1<Device_Set_Pra.Memmory_12.Device_Switch_Level[i])  //&& (Device_Obj_Mage[i].Device_Switch_state==Switch_Off)
                                {
                                     Device_Obj_Mage[i].Device_Pre_Time= Effective_time;   //Fore_Time
                                    
                                     //Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(0XFF,i);
                                    
                                }
                                else if(device_level_1>=Device_Set_Pra.Memmory_12.Device_Switch_Level[i]) //&&(Device_Obj_Mage[i].Device_Switch_state==Switch_On)
                                {
                                    //Device_Obj_Mage[i].Device_Pre_Time= Effective_no_use_time(i)+L_To_T(0,i);
                                     Device_Obj_Mage[i].Device_Pre_Time= 2;
                                }
                        }
                //        Device_Obj_Mage[i].Device_Pre_Time=(L_To_T(Device_Obj_Mage[i].Device_Pre_Level)*(255-Device_Set_Pra.Memmory_9.Device_Max_Level[i]))/255;//Device_Obj_Mage[i].Device_Pre_Time=L_To_T(Device_Obj_Mage[i].Device_Pre_Level);
                        
                        if(Device_Obj_Mage[i].Device_Pre_Level<=Device_Obj_Mage[i].Device_Dest_Level)
                        {
                            Device_Obj_Mage[i].Device_Fade_Time=0;
                            Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Dest_Level;
                            Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
                            continue;
                        }
//                        if(Device_Obj_Mage[i].Device_Fade_Time==1&& Device_Obj_Mage[i].Device_Pre_Level!=Device_Obj_Mage[i].Device_Dest_Level)
//                        {
//                            Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Dest_Level;
//                        }    
                        if(Device_Obj_Mage[i].Device_Change_Level==0)
                        {
                            Device_Obj_Mage[i].Device_Fade_Step=1;
                        }
                        else
                        {    
                          Device_Obj_Mage[i].Device_Change_Level--;
                    
                        }
                    }
                    //Device_Obj_Mage[i].Device_Current_Time=L_To_T(Device_Obj_Mage[i].Device_Current_Level);
                }

         }
         else
         {
              Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
             if(Device_Obj_Mage[i].Device_Current_Time<Effective_no_use_time(i))
             {
                 Device_Obj_Mage[i].Device_Pre_Time=Effective_no_use_time(i);
                 Device_Obj_Mage[i].Device_Pre_Level=T_To_L(Device_Obj_Mage[i].Device_Pre_Time,i);
             }
        //     Device_Obj_Mage[i].Device_Current_Level=Device_Obj_Mage[i].Device_Dest_Level;
            // Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level; 
         }
         
    }
     

}    
 
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) //25us定时器中断回调函数
//{

//}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint8_t i=0;
    for(i=0;i<Device_Channel_Number;i++)
    {    
        if(g_device_state==Device_No_Okay)
        {
            Device_Obj_Mage[i].Device_Current_Level=0xFF;
            Device_Obj_Mage[i].Device_Pre_Level=0xFF;;
            Device_Obj_Mage[i].Device_Dest_Level=0xFF;
            Device_Obj_Mage[i].Device_Pre_Time= Total_time;
            Device_Obj_Mage[i].Device_Dest_Level=Total_time;
            
            Device_Obj_Mage[i].Device_Fade_Time=0;
        }
        else if(g_device_state==Device_Okay)
        {
            if(Protoal_Set_Mode!=Master_Listen_Mode)
            {
                Device_Obj_Mage[i].Device_Current_Level=Device_Obj_Mage[i].Device_Pre_Level;
                Device_Obj_Mage[i].Device_Current_Time=Device_Obj_Mage[i].Device_Pre_Time;
            }
      }
    }
//    ct=g_Device_Zero_EXTI_Ct;
//    
//    if(g_Device_Zero_EXTI_Ct<=Total_time)
//    {
//        ct=g_Device_Zero_EXTI_Ct;
//    }
    g_Device_Zero_EXTI_Ct=0;
}


void Normal_Work_Mode_Func(void)
{
    
    uint8_t i=0;
        for(i=0;i<Device_Channel_Number;i++)
    {
            Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;
            Device_Obj_Mage[i].Device_Pre_Time=Device_Obj_Mage[i].Device_Current_Time;
            Device_Obj_Mage[i].Device_Fade_Time=0;
    }
    
}



uint8_t Device_preset_Level_save(uint8_t area_number, uint8_t set_num, uint8_t join)
{
    uint8_t i = 0;
  uint8_t is_logic1_valid = 0;
    uint8_t result =1;
    
    
    for(i=0;i<4;i++)
    {
        if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
        {
            if((join & Device_Set_Pra.Memmory_7.Device_Jonn_1[i])==0)
            {
             continue;
            }    
            Device_Set_Pra.Memmory_35.set_save[i] =  set_num;
            result = 0;
        }                
    } 
    
    for(i=4;i<12;i++)
    {
        if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
        {
            if((join & Device_Set_Pra.Memmory_8.Device_Jonn_2[i-4])==0)
            {
             continue;
            }    
            Device_Set_Pra.Memmory_35.set_save[i] =  set_num;
            result = 0;
        }                
    } 

    if( result == 0)
    {
        AT24CXX_Write(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1,544,Device_Set_Pra.Memmory_35.set_save,16);  // 不在相关数据以内
    }

    return result;
    
} 


uint8_t Device_preset_search(uint8_t area_number,uint8_t join)
{
    uint8_t i = 0;
    uint8_t set_tmp = 0xFF;
  uint8_t is_logic1_valid = 0;
    //uint8_t result =1;
    
    
    for(i=0;i<8;i++)
    {    
          if((Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i] == 0)&&(area_number==Device_Set_Pra.Memmory_7.Device_Area[i]))
            {
                is_logic1_valid = 1;   // 确保包含逻辑号1
            }
    }
    
    for(i=8;i<12;i++)
    {
          if((Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8] == 0)&&(area_number==Device_Set_Pra.Memmory_7.Device_Area[i]))
            {
                is_logic1_valid = 1;
                
            }
    }
    
    
    if( is_logic1_valid == 1)
    {
             for(i=0;i<4;i++)
          {
                if( (Device_Set_Pra.Memmory_1.Device_Duplic_Flag&(0x01<<i)) ==  1 )     // 场景查询需不需要过滤重复位
                {
                     continue;
                }
                
                if((join & Device_Set_Pra.Memmory_7.Device_Jonn_1[i])==0)
              {
                continue;
              }    
                
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    set_tmp = Device_Set_Pra.Memmory_35.set_save[i];
                }            
            } 
             for(i=4;i<8;i++)
          {
                if( (Device_Set_Pra.Memmory_1.Device_Duplic_Flag&(0x01<<i)) ==  1 )     // 场景查询需不需要过滤重复位
                {
                     continue;
                }
                
                if((join & Device_Set_Pra.Memmory_8.Device_Jonn_2[i-4])==0)
              {
                continue;
              }
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    set_tmp = Device_Set_Pra.Memmory_35.set_save[i];
                }            
            } 
    }
    
//    if( result == 0)
//    {
//        AT24CXX_Write(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1,544,Device_Set_Pra.Memmory_35.set_save,16);  // 不在相关数据以内
//    }
    
//    if(is_logic1_valid == 1)
//    {
//        result = 1;
//        
//    }
    
    return set_tmp;
    
} 


uint8_t Device_Adj_Level_Request(uint8_t* actual_level,uint8_t* target_level,uint8_t area_number, uint8_t logic_channel)
{
    uint8_t i = 0;
  uint8_t is_logic1_valid = 0;
    uint8_t result =1;
    
    
    for(i=0;i<4;i++)
    {    
//          if(Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i] == 0)
//            {
//                is_logic1_valid = 1;
//            }
        
          if( (Device_Set_Pra.Memmory_1.Device_Duplic_Flag&(0x01<<i)) ==  1 )
            {
                continue;
            }
            
            if((area_number==Device_Set_Pra.Memmory_7.Device_Area[i])&&(logic_channel==Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i]))
          {
                *actual_level=Device_Obj_Mage[i].Device_Current_Level;
                *target_level=Device_Obj_Mage[i].Device_Dest_Level;
                result =  0;
            }
    }
    
    for(i=4;i<12;i++)
    {
//          if(Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i] == 0)
//            {
//                is_logic1_valid = 1;
//            }
            
          if( (Device_Set_Pra.Memmory_1.Device_Duplic_Flag&(0x01<<i)) ==  1 )
            {
                continue;
            }
            if((area_number==Device_Set_Pra.Memmory_7.Device_Area[i])&&(logic_channel==Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i]))
            { 
                *actual_level=Device_Obj_Mage[i].Device_Current_Level;
                *target_level=Device_Obj_Mage[i].Device_Dest_Level;            
                result =  0;
            }
  }        

//    if(is_logic1_valid == 1)
//    {
//        result = 1;
//    }
    
    return result;
    
} 

//void Device_Adj_Level_Request(uint8_t* actual_level,uint8_t* target_level,uint8_t area_number, uint8_t logic_channel)
//{
//     uint8_t i=0;
//  
//        for(i=0;i<4;i++)
//    {    
//            if((area_number==Device_Set_Pra.Memmory_7.Device_Area[i])&&(logic_channel==Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i]))
//          {
//                *actual_level=Device_Obj_Mage[i].Device_Current_Level;
//                *target_level=Device_Obj_Mage[i].Device_Dest_Level;
//            }
//    }
//    for(i=4;i<8;i++)
//    {
//            if((area_number==Device_Set_Pra.Memmory_7.Device_Area[i])&&(logic_channel==Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i]))
//        { 
//            *actual_level=Device_Obj_Mage[i].Device_Current_Level;
//            *target_level=Device_Obj_Mage[i].Device_Dest_Level;            
//    }
//  }        
//    
//}  

void Device_Preset_Process(uint8_t area_number,uint8_t preset_number,uint32_t fade_time,uint8_t device_join)
{
    uint8_t i=0;
    preset_number=preset_number+1;
    
    switch(preset_number)
    {
        case 1:
        {
             for(i=0;i<12;i++)
            {                
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_16.Device_Preset_1[i],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_16.Device_Preset_1[i],fade_time*10,RESET,device_join);    
                    }
                    
                  Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_16.Device_Preset_1[i];
                }
                else
                {
                     Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
                            
            }        
            break;
        }
        case 2:
        {
                for(i=0;i<4;i++)
             {    
                    if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                    {
                        Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_16.Device_Preset_2[i],fade_time*10,RESET,device_join);  
                        Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_16.Device_Preset_2[i];
                    }
                    else
                    {
                         Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                    }
             }    
             for(i=4;i<12;i++)
             {
                     if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                    {
                        if(i<8)
                        {
                        Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_17.Device_Preset_2[i-4],fade_time*10,RESET,device_join);    
                        }
                        else
                        {
                         Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_17.Device_Preset_2[i-4],fade_time*10,RESET,device_join);    
                        }
                        //Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_17.Device_Preset_2[i-4],fade_time*10,RESET,device_join);
            Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_16.Device_Preset_2[i-4];                        
                    }
                    else
                    {
                        Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                    }
                    
             }
            break;
        }

        case 3:
        {
                for(i=0;i<8;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_17.Device_Preset_3[i],fade_time*10,RESET,device_join);
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_17.Device_Preset_3[i];                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }            
            for(i=8;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_18.Device_Preset_3[i-8],fade_time*10,RESET,device_join);  
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_18.Device_Preset_3[i-8];
                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }
            break;
        }
        
        case 4:
        {
                for(i=0;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_18.Device_Preset_4[i],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_18.Device_Preset_4[i],fade_time*10,RESET,device_join);    
                    }
            //    Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_18.Device_Preset_4[i],fade_time*10,RESET,device_join);
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_18.Device_Preset_4[i];                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
            break;
        }
        case 5:
        {
                for(i=0;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_19.Device_Preset_5[i],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_19.Device_Preset_5[i],fade_time*10,RESET,device_join);    
                    }
                    //Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_19.Device_Preset_5[i],fade_time*10,RESET,device_join);  
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_19.Device_Preset_5[i];    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
            
            
            break;
        }
        case 6:
        {
                for(i=0;i<4;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_19.Device_Preset_6[i],fade_time*10,RESET,device_join); 
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_19.Device_Preset_6[i];                        
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
                for(i=4;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_20.Device_Preset_6[i-4],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_20.Device_Preset_6[i-4],fade_time*10,RESET,device_join);    
                    }
                //    Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_20.Device_Preset_6[i-4],fade_time*10,RESET,device_join);
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_20.Device_Preset_6[i-4];                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
            
            break;
        }

        case 7:
        {
                for(i=0;i<8;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_20.Device_Preset_7[i],fade_time*10,RESET,device_join); 
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_20.Device_Preset_7[i];                        
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
                
            }
                for(i=8;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_21.Device_Preset_7[i-8],fade_time*10,RESET,device_join);  
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_21.Device_Preset_7[i-8];
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
            break;
        }
        case 8:
        {
             for(i=0;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                     if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_21.Device_Preset_8[i],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_21.Device_Preset_8[i],fade_time*10,RESET,device_join);    
                    }
                //    Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_21.Device_Preset_8[i],fade_time*10,RESET,device_join); 
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_21.Device_Preset_8[i];                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
            break;
        }
        case 9:
        {
              for(i=0;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_22.Device_Preset_9[i],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_22.Device_Preset_9[i],fade_time*10,RESET,device_join);    
                    }
                //    Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_22.Device_Preset_9[i],fade_time*10,RESET,device_join);  
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_22.Device_Preset_9[i];    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
            break;
        }
        case 10:
        {
              for(i=0;i<4;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_22.Device_Preset_10[i],fade_time*10,RESET,device_join);
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_22.Device_Preset_10[i];                        
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
             for(i=4;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_23.Device_Preset_10[i-4],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_23.Device_Preset_10[i-4],fade_time*10,RESET,device_join);    
                    }
                //    Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_23.Device_Preset_10[i-4],fade_time*10,RESET,device_join);  
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_23.Device_Preset_10[i-4];
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
            break;
        }
        case 11:
        {
             for(i=0;i<8;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_23.Device_Preset_11[i],fade_time*10,RESET,device_join);
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_23.Device_Preset_11[i];                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }
             for(i=8;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_24.Device_Preset_11[i-8],fade_time*10,RESET,device_join);
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_23.Device_Preset_11[i-8];                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }
            break;
        }        
        case 12:
        {
                for(i=0;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_24.Device_Preset_12[i],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_24.Device_Preset_12[i],fade_time*10,RESET,device_join);    
                    }
            //        Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_24.Device_Preset_12[i],fade_time*10,RESET,device_join); 
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_24.Device_Preset_12[i];                        
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }
            break;
        }
        case 13:
        {
                for(i=0;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_25.Device_Preset_13[i],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_25.Device_Preset_13[i],fade_time*10,RESET,device_join);    
                    }
                //    Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_25.Device_Preset_13[i],fade_time*10,RESET,device_join); 
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_25.Device_Preset_13[i];                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }            
            break;
        }
        case 14:
        {
                for(i=0;i<4;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_25.Device_Preset_14[i],fade_time*10,RESET,device_join); 
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_25.Device_Preset_14[i];                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }        
                for(i=4;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_26.Device_Preset_14[i-4],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_26.Device_Preset_14[i-4],fade_time*10,RESET,device_join);    
                    }
            //        Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_26.Device_Preset_14[i-4],fade_time*10,RESET,device_join);
           Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_25.Device_Preset_14[i-4];                    
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }                    
            break;
        }
        case 15:
        {
                for(i=0;i<8;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_26.Device_Preset_15[i],fade_time*10,RESET,device_join); 
           Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_26.Device_Preset_15[i];                        
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }    
            for(i=8;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_27.Device_Preset_15[i-8],fade_time*10,RESET,device_join);  
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_27.Device_Preset_15[i-8];
                }
                else
                {
                    Device_Set_Pra.Memmory_28.level_save[i]=Device_Obj_Mage[i].Device_Current_Level;
                }
            }                
            break;
        }
        case 16:
        {
                for(i=0;i<12;i++)
             {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                    Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_27.Device_Preset_16[i],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_27.Device_Preset_16[i],fade_time*10,RESET,device_join);    
                    }
            //        Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_27.Device_Preset_16[i],fade_time*10,RESET,device_join); 
          Device_Set_Pra.Memmory_28.level_save[i]=Device_Set_Pra.Memmory_27.Device_Preset_16[i];                 
                }
            }                
            break;
        }
        case 17:
        {
            break;
        }
        case 18:
        {
            break;
        }        
        case 0xAA: // tooggle
        {
            for(i=0;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],0x01,fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],0x01,fade_time*10,RESET,device_join);    
                    }
            //        Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_27.Device_Preset_16[i],fade_time*10,RESET,device_join);              
                }
            }    
        
            break;
        }
        case 0xBB:
        {
            for(i=0;i<12;i++)
            {    
                if(area_number==Device_Set_Pra.Memmory_7.Device_Area[i])
                {
                    if(i<8)
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i],Device_Set_Pra.Memmory_28.level_save[i],fade_time*10,RESET,device_join);    
                    }
                    else
                    {
                     Device_Switch_Fuc_Process(area_number,Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8],Device_Set_Pra.Memmory_28.level_save[i],fade_time*10,RESET,device_join);    
                    }
            //        Device_Switch_Fuc_Process(area_number,i,Device_Set_Pra.Memmory_27.Device_Preset_16[i],fade_time*10,RESET,device_join);              
                }
            }    
            break;
        }
        default:
        {
            break;
        }
    }

}


void Device_Switch_Channel(uint8_t channel_number,uint8_t channel_state)
{
    if(channel_state==SET)
    {
         Device_Obj_Mage[channel_number].Device_Pre_Time=Fore_Time;
     //Device_Obj_Mage[channel_number].Device_Pre_Time= Effective_no_use_time(channel_number)+L_To_T(0,channel_number);
    }
    else if(channel_state==RESET)
    {
        Device_Obj_Mage[channel_number].Device_Pre_Time=Fore_Time+Effective_time;
        //Device_Obj_Mage[channel_number].Device_Pre_Time= Effective_no_use_time(channel_number)+L_To_T(0xFF,channel_number);
    }
}


void Device_AUX_Push_Fuc(void)
{ 
     uint32_t time_temp=0;
    
     if((Device_Set_Pra.Memmory_6.Aux_Push[0]&0x0F)==5)
     {    
         if(Device_Set_Pra.Memmory_6.Aux_Push[4]==0xD3)  //设置通道亮度
     {
            Device_Switch_Fuc_Process(Device_Set_Pra.Memmory_6.Aux_Push[2],Device_Set_Pra.Memmory_6.Aux_Push[6],Device_Set_Pra.Memmory_6.Aux_Push[7],Device_Set_Pra.Memmory_6.Aux_Push[5]*50,RESET,Device_Set_Pra.Memmory_6.Aux_Push[3]);       
            F5_CMD_send(Device_Set_Pra.Memmory_6.Aux_Push[2],Device_Set_Pra.Memmory_6.Aux_Push[3],Device_Set_Pra.Memmory_6.Aux_Push[4],Device_Set_Pra.Memmory_6.Aux_Push[5],Device_Set_Pra.Memmory_6.Aux_Push[6],Device_Set_Pra.Memmory_6.Aux_Push[7]);
         }
         else if(Device_Set_Pra.Memmory_6.Aux_Push[4]==0xFE) //设置场景
         {
            time_temp=(Device_Set_Pra.Memmory_6.Aux_Push[7]<<8)|Device_Set_Pra.Memmory_6.Aux_Push[6];
            Device_Preset_Process(Device_Set_Pra.Memmory_6.Aux_Push[2],Device_Set_Pra.Memmory_6.Aux_Push[5],time_temp,Device_Set_Pra.Memmory_6.Aux_Push[3]);
            F5_CMD_send(Device_Set_Pra.Memmory_6.Aux_Push[2],Device_Set_Pra.Memmory_6.Aux_Push[3],Device_Set_Pra.Memmory_6.Aux_Push[4],Device_Set_Pra.Memmory_6.Aux_Push[5],Device_Set_Pra.Memmory_6.Aux_Push[6],Device_Set_Pra.Memmory_6.Aux_Push[7]);
            
         }
     }
     
         if((Device_Set_Pra.Memmory_6.Aux_Release[0]&0x0F)==5)
     {    
         if(Device_Set_Pra.Memmory_6.Aux_Release[4]==0xD3)
     {
            Device_Switch_Fuc_Process(Device_Set_Pra.Memmory_6.Aux_Release[2],Device_Set_Pra.Memmory_6.Aux_Release[6],Device_Set_Pra.Memmory_6.Aux_Release[7],Device_Set_Pra.Memmory_6.Aux_Release[5]*50,RESET,Device_Set_Pra.Memmory_6.Aux_Release[3]); 
             F5_CMD_send(Device_Set_Pra.Memmory_6.Aux_Release[2],Device_Set_Pra.Memmory_6.Aux_Release[3],Device_Set_Pra.Memmory_6.Aux_Release[4],Device_Set_Pra.Memmory_6.Aux_Release[5],Device_Set_Pra.Memmory_6.Aux_Release[6],Device_Set_Pra.Memmory_6.Aux_Release[7]);
         }
         else if(Device_Set_Pra.Memmory_6.Aux_Release[4]==0xFE)
         {
            time_temp=(Device_Set_Pra.Memmory_6.Aux_Release[7]<<8)|Device_Set_Pra.Memmory_6.Aux_Release[6];
            Device_Preset_Process(Device_Set_Pra.Memmory_6.Aux_Release[2],Device_Set_Pra.Memmory_6.Aux_Release[5],time_temp,Device_Set_Pra.Memmory_6.Aux_Release[3]);        
      F5_CMD_send(Device_Set_Pra.Memmory_6.Aux_Release[2],Device_Set_Pra.Memmory_6.Aux_Release[3],Device_Set_Pra.Memmory_6.Aux_Release[4],Device_Set_Pra.Memmory_6.Aux_Release[5],Device_Set_Pra.Memmory_6.Aux_Release[6],Device_Set_Pra.Memmory_6.Aux_Release[7]);
         }
     }

    
}

void Device_AUX_Release_Fuc(void)
{
  uint32_t time_temp=0;
// if(Device_Set_Pra.Memmory_6.Aux_Release[4]==0xD3)
// {
//     if((Device_Set_Pra.Memmory_6.Aux_Push[0]&0x0F)==1)
//     {
//      Device_Switch_Fuc_Process(Device_Set_Pra.Memmory_6.Aux_Release[2],Device_Set_Pra.Memmory_6.Aux_Release[6],Device_Set_Pra.Memmory_6.Aux_Push[7],Device_Set_Pra.Memmory_6.Aux_Release[5]*50,RESET); 
//     }
// }
//  if(Device_Set_Pra.Memmory_6.Aux_Push[4]==0xD3)
// {
//     if((Device_Set_Pra.Memmory_6.Aux_Push[0]&0x0F)==5)
//     {
//      Device_Switch_Fuc_Process(Device_Set_Pra.Memmory_6.Aux_Push[2],Device_Set_Pra.Memmory_6.Aux_Push[6],Device_Set_Pra.Memmory_6.Aux_Push[7],Device_Set_Pra.Memmory_6.Aux_Push[5]*50,RESET); 
//     }
// }
 
      if((Device_Set_Pra.Memmory_6.Aux_Push[0]&0x0F)==1)
     {    
         if(Device_Set_Pra.Memmory_6.Aux_Push[4]==0xD3)
     {
            Device_Switch_Fuc_Process(Device_Set_Pra.Memmory_6.Aux_Push[2],Device_Set_Pra.Memmory_6.Aux_Push[6],Device_Set_Pra.Memmory_6.Aux_Push[7],Device_Set_Pra.Memmory_6.Aux_Push[5]*50,RESET,Device_Set_Pra.Memmory_6.Aux_Push[3]); 
      F5_CMD_send(Device_Set_Pra.Memmory_6.Aux_Push[2],Device_Set_Pra.Memmory_6.Aux_Push[3],Device_Set_Pra.Memmory_6.Aux_Push[4],Device_Set_Pra.Memmory_6.Aux_Push[5],Device_Set_Pra.Memmory_6.Aux_Push[6],Device_Set_Pra.Memmory_6.Aux_Push[7]);             
         }
         else if(Device_Set_Pra.Memmory_6.Aux_Push[4]==0xFE)
         {
             time_temp=(Device_Set_Pra.Memmory_6.Aux_Push[7]<<8)|Device_Set_Pra.Memmory_6.Aux_Push[6];
             Device_Preset_Process(Device_Set_Pra.Memmory_6.Aux_Push[2],Device_Set_Pra.Memmory_6.Aux_Push[5],time_temp,Device_Set_Pra.Memmory_6.Aux_Push[3]);
             F5_CMD_send(Device_Set_Pra.Memmory_6.Aux_Push[2],Device_Set_Pra.Memmory_6.Aux_Push[3],Device_Set_Pra.Memmory_6.Aux_Push[4],Device_Set_Pra.Memmory_6.Aux_Push[5],Device_Set_Pra.Memmory_6.Aux_Push[6],Device_Set_Pra.Memmory_6.Aux_Push[7]);
         }
     }
     
         if((Device_Set_Pra.Memmory_6.Aux_Release[0]&0x0F)==1)
     {    
         if(Device_Set_Pra.Memmory_6.Aux_Release[4]==0xD3)
     {
            Device_Switch_Fuc_Process(Device_Set_Pra.Memmory_6.Aux_Release[2],Device_Set_Pra.Memmory_6.Aux_Release[6],Device_Set_Pra.Memmory_6.Aux_Release[7],Device_Set_Pra.Memmory_6.Aux_Release[5]*50,RESET,Device_Set_Pra.Memmory_6.Aux_Release[3]); 
            F5_CMD_send(Device_Set_Pra.Memmory_6.Aux_Release[2],Device_Set_Pra.Memmory_6.Aux_Release[3],Device_Set_Pra.Memmory_6.Aux_Release[4],Device_Set_Pra.Memmory_6.Aux_Release[5],Device_Set_Pra.Memmory_6.Aux_Release[6],Device_Set_Pra.Memmory_6.Aux_Release[7]);
         }
         else if(Device_Set_Pra.Memmory_6.Aux_Release[4]==0xFE)
         {
            time_temp=(Device_Set_Pra.Memmory_6.Aux_Release[7]<<8)|Device_Set_Pra.Memmory_6.Aux_Release[6];
            Device_Preset_Process(Device_Set_Pra.Memmory_6.Aux_Release[2],Device_Set_Pra.Memmory_6.Aux_Release[5],time_temp,Device_Set_Pra.Memmory_6.Aux_Release[3]);        
            F5_CMD_send(Device_Set_Pra.Memmory_6.Aux_Release[2],Device_Set_Pra.Memmory_6.Aux_Release[3],Device_Set_Pra.Memmory_6.Aux_Release[4],Device_Set_Pra.Memmory_6.Aux_Release[5],Device_Set_Pra.Memmory_6.Aux_Release[6],Device_Set_Pra.Memmory_6.Aux_Release[7]);
         }
     }
}

void Light_Init(void)
{
     uint8_t i;

    for(i=0;i<12;i++)
    {
        Device_Obj_Mage[i].Device_Current_Level=0xFF;
        Device_Obj_Mage[i].Device_Pre_Time= Effective_time;
        Device_Obj_Mage[i].Device_Current_Time=Effective_time;
        Switch_Off(i);
    }
    
    for(i=0;i<Device_Channel_Number;i++)
    { 
        Device_Preset_Process(Device_Set_Pra.Memmory_7.Device_Area[i],Device_Set_Pra.Memmory_35.set_save[i],250,0xFF);
        //Device_Switch_Fuc_Process(0,i,Device_Set_Pra.Memmory_28.level_save[i],500,RESET,0xFF);    
    //    device_channel_set(i,Device_Set_Pra.Memmory_28.level_save[i],500);
    }
}


void LED_multi_func(LED_statet_t LED_state)
{
    static uint32_t Key_ct=0;;
    static uint32_t Key_uart_ct=0;
    
    Key_ct++;
    switch(LED_state)
    {
        case LED_SYS:
        {
                if(g_device_state!=Device_No_Okay)
                {
                    if(Key_ct%35==0)
                    {
                     Key_IN();
                    }
                    if(Key_ct%70==0)
                    {    
                         HAL_GPIO_WritePin(Service_GPIO_Port,Service_Pin,GPIO_PIN_RESET);
                         Key_OUT(); 
                    }
                }
            break;
        }
        
        case LED_LOADDATA:
        {
             Key_uart_ct++;
             if(Key_uart_ct%5==0)
             {
                Key_OUT();
                HAL_GPIO_TogglePin(Service_GPIO_Port,Service_Pin);
             }
             break;
        }
    }
        

    
}



