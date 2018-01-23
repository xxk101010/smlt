

#include "app.h"

#include "protoal.h"

#include "string.h"

#include "delay.h"

#include "24cxx.h" 

#include "usart.h"


extern TIM_HandleTypeDef htim2;



uint8_t g_device_state;



Device_Set_Pra_t Device_Set_Pra;

Device_Obj_Mage_t   Device_Obj_Mage[12];

preset_save_t*   preset_save_ptr;

Device_Current_Prat_t Device_Current_Pra;

uint16_t  Switch_Mgmt=0;

uint16_t  g_Device_Zero_EXTI_Ct=0;




uint16_t g_Curretn_EE_Addr = 0;  //读写EE地址


void Device_Intial(void)
{
    AT24CXX_Init(); //初始化IIC
    
    Device_Set_Pra.Memmory_1.Device_version[0] = (uint8_t)(version>>8);
    
    Device_Set_Pra.Memmory_1.Device_version[1] = (uint8_t)version;
    
    AT24CXX_WriteOneByte(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1, 2,Device_Set_Pra.Memmory_1.Device_version[0]);
    
    DelayXus(2000);
    
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
        Device_Set_Pra.Memmory_1.Device_Box=0xFF;
    }    
    else
    {
        g_device_state= Device_Okay;
    AT24CXX_Read(AT24C64_ADDR,IIC_DEV_ADDR_TYPE_1,0,(uint8_t *)&Device_Set_Pra.Memmory_1.Device_Type,768); 
    }
      
}





void Device_Switch(uint8_t physic_channel, Switch_statet_t switch_statet)
{     
    if(switch_statet==Switch_On)
    {
        switch(physic_channel)
        {
            case 1:
            {
                 
                HAL_GPIO_WritePin(T1a_GPIO_Port,  T1a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T1a_GPIO_Port,  T1a_Pin, GPIO_PIN_RESET);
                break;
            }
                    
            case 2:
            {
                HAL_GPIO_WritePin(T2a_GPIO_Port,  T2a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T2a_GPIO_Port,  T2a_Pin, GPIO_PIN_RESET);
                break;
            }                
            
                
            case 3:
            {
                HAL_GPIO_WritePin(T3a_GPIO_Port,  T3a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T3a_GPIO_Port,  T3a_Pin, GPIO_PIN_RESET);
                break;
            }
                
            case 4:
            {
                HAL_GPIO_WritePin(T4a_GPIO_Port,  T4a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T4a_GPIO_Port,  T4a_Pin, GPIO_PIN_RESET);
                break;
                
            }
                
            case 5:
            {
                HAL_GPIO_WritePin(T5a_GPIO_Port,  T5a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T5a_GPIO_Port,  T5a_Pin, GPIO_PIN_RESET);
                break;
            }
                
            case 6:
            {
        HAL_GPIO_WritePin(T6a_GPIO_Port,  T6a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T6a_GPIO_Port,  T6a_Pin, GPIO_PIN_RESET);
                break;
            }
                
            case 7:
            {
        HAL_GPIO_WritePin(T7a_GPIO_Port,  T7a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T7a_GPIO_Port,  T7a_Pin, GPIO_PIN_RESET);
                break;
            }
                
            case 8:
            {
        HAL_GPIO_WritePin(T8a_GPIO_Port,  T8a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T8a_GPIO_Port,  T8a_Pin, GPIO_PIN_RESET);
                break;
            }
            case 9:
            {
             HAL_GPIO_WritePin(T9a_GPIO_Port,  T9a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T9a_GPIO_Port,  T9a_Pin, GPIO_PIN_RESET);
                break;
            }
            case 10:
            {
                HAL_GPIO_WritePin(T10a_GPIO_Port,  T10a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T10a_GPIO_Port,  T10a_Pin, GPIO_PIN_RESET);
                break;
            }
            case 11:
            {
                HAL_GPIO_WritePin(T11a_GPIO_Port,  T11a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T11a_GPIO_Port,  T11a_Pin, GPIO_PIN_RESET);
                break;
            }
            case 12:
            {
                HAL_GPIO_WritePin(T12a_GPIO_Port,  T12a_Pin, GPIO_PIN_SET);
                osDelay(delay_on_time);
              HAL_GPIO_WritePin(T12a_GPIO_Port,  T12a_Pin, GPIO_PIN_RESET);
                break;
            }
            default:
            {
                break;
            }
            
            
        }
    }
    else if(switch_statet==Switch_Off)
    {
         //Device_Obj_Mage[physic_channel].Switch_drive_state=Switch_drive_Off_set;
            switch(physic_channel)
         {
            case 1:
            {
        HAL_GPIO_WritePin(T1b_GPIO_Port,  T1b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T1b_GPIO_Port,  T1b_Pin, GPIO_PIN_RESET);
                break;
            }
                    
            case 2:
            {
        HAL_GPIO_WritePin(T2b_GPIO_Port,  T2b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T2b_GPIO_Port,  T2b_Pin, GPIO_PIN_RESET);
                break;
            }                
            
                
            case 3:
            {
        HAL_GPIO_WritePin(T3b_GPIO_Port,  T3b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T3b_GPIO_Port,  T3b_Pin, GPIO_PIN_RESET);
                break;
            }
                
            case 4:
            {
        HAL_GPIO_WritePin(T4b_GPIO_Port,  T4b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T4b_GPIO_Port,  T4b_Pin, GPIO_PIN_RESET);
                break;
                
            }
                
            case 5:
            {
        HAL_GPIO_WritePin(T5b_GPIO_Port,  T5b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T5b_GPIO_Port,  T5b_Pin, GPIO_PIN_RESET);
                break;
            }
                
            case 6:
            {
        HAL_GPIO_WritePin(T6b_GPIO_Port,  T6b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T6b_GPIO_Port,  T6b_Pin, GPIO_PIN_RESET);
                break;
            }
                
            case 7:
            {
        HAL_GPIO_WritePin(T7b_GPIO_Port,  T7b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T7b_GPIO_Port,  T7b_Pin, GPIO_PIN_RESET);
                break;
            }
                
            case 8:
            {    
        HAL_GPIO_WritePin(T8b_GPIO_Port,  T8b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T8b_GPIO_Port,  T8b_Pin, GPIO_PIN_RESET);
                break;
            }
            case 9:
            {       
                HAL_GPIO_WritePin(T9b_GPIO_Port,  T9b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T9b_GPIO_Port,  T9b_Pin, GPIO_PIN_RESET);
                break;
                
            }
            case 10:
            {
                HAL_GPIO_WritePin(T10b_GPIO_Port,  T10b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T10b_GPIO_Port,  T10b_Pin, GPIO_PIN_RESET);
                break;
            }
            case 11:
            {
                HAL_GPIO_WritePin(T11b_GPIO_Port,  T11b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T11b_GPIO_Port,  T11b_Pin, GPIO_PIN_RESET);
                break;
            }
            case 12:
            {
                HAL_GPIO_WritePin(T12b_GPIO_Port,  T12b_Pin, GPIO_PIN_SET);
        
            osDelay(delay_on_time);

            HAL_GPIO_WritePin(T12b_GPIO_Port,  T12b_Pin, GPIO_PIN_RESET);
                break;
            }
            default:
            {    
                break;
            }            
        }        
    }
        
}



void device_channel_set(uint8_t physic_channel,uint8_t device_level,uint32_t fade_time)
{
        
     fade_time= fade_time+1;

        if(device_level>Device_Obj_Mage[physic_channel].Device_Current_Level)       //渐暗
        {
             
                 Device_Obj_Mage[physic_channel].switch_direction_statet=Switch_On_to_Off;
                                                
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
                 Device_Obj_Mage[physic_channel].switch_direction_statet=Switch_Off_to_On;
                                                            
                 Device_Obj_Mage[physic_channel].Device_Fade_Time= fade_time;
                    
                 Device_Obj_Mage[physic_channel].Device_Change_Level=Device_Obj_Mage[physic_channel].Device_Current_Level-device_level;                                   
                    
                 Device_Obj_Mage[physic_channel].Device_Fade_Step=    Device_Obj_Mage[physic_channel].Device_Fade_Time/ Device_Obj_Mage[physic_channel].Device_Change_Level;
                    
                if(Device_Obj_Mage[physic_channel].Device_Fade_Step==0)
                {
                    Device_Obj_Mage[physic_channel].Device_Fade_Step=1;
                }
                                                 
                 Device_Obj_Mage[physic_channel].Device_Dest_Level =device_level;
        }
    
}  


     
//主控函数，当device_level为FF表示灭掉，0表示全开，fade_time为0 表示开关
void Device_Switch_Fuc_Process(uint8_t area_number, uint8_t logic_channel,uint8_t device_level,uint32_t fade_time,uint8_t stop_flag,uint8_t device_join)  
{
    uint8_t i;
    //uint32_t Device_Time=0;
    //device_level=0XFF-device_level;
    fade_time =  fade_time+1;
    for(i=0;i<4;i++)
    {    
            if(((area_number==Device_Set_Pra.Memmory_7.Device_Area[i])||(area_number==0))&&((logic_channel==Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i])||(logic_channel==0XFF)))
          {
                // if(((device_join & Device_Set_Pra.Memmory_7.Device_Jonn_1[i])==0)&&(((Device_Set_Pra.Memmory_7.Device_Jonn_1[i]|device_join)&0x80)==0))
                  if((device_join & Device_Set_Pra.Memmory_7.Device_Jonn_1[i])==0)
                    {
           continue;
                    }                
                    if(device_level==0)
                    {
                        continue;
                    }
                    
                    if(stop_flag==SET)
                    {
                        Device_Obj_Mage[i].Device_Fade_Time=0;
                        Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level;
                        continue;
                    }
                    if(device_level>Device_Obj_Mage[i].Device_Current_Level)       //渐暗
                    {
                         
                     Device_Obj_Mage[i].switch_direction_statet=Switch_On_to_Off;
                                                    
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
                     Device_Obj_Mage[i].switch_direction_statet=Switch_Off_to_On;
                                                                
                     Device_Obj_Mage[i].Device_Fade_Time= fade_time;
                        
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

                    if(stop_flag==SET)
                    {
                      Device_Obj_Mage[i].Device_Fade_Time=0;
                        Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level;
                        continue;
                    }
//                              if(fade_time==0) //渐变时间为0，说明是设置亮度
//                              {
//                                 if(stop_flag==SET)
//                                 {
//                                // Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
//                                     Device_Obj_Mage[i].Device_Fade_Time=0;
//                                     Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level;
//                                 }
//                                 else
//                                 {                                        
//                                     Device_Obj_Mage[i].Device_Fade_Time=1;                            
//                                 }
//                              }
                            if(device_level>Device_Obj_Mage[i].Device_Current_Level)       //渐暗
                            {
                                     
                                            Device_Obj_Mage[i].switch_direction_statet=Switch_On_to_Off;
                                            
                                        // Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                                            
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
                                         Device_Obj_Mage[i].switch_direction_statet=Switch_Off_to_On;
                                            
        //                             Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                                            
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

                     if(stop_flag==SET)
                    {
                      Device_Obj_Mage[i].Device_Fade_Time=0;
                        Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level;
                        continue;
                    }
//                              if(fade_time==0) //渐变时间为0，说明是设置亮度
//                              {
//                                 if(stop_flag==SET)
//                                 {
//                                     Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
//                                     Device_Obj_Mage[i].Device_Fade_Time=0;
//                                     Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level;
//                                 }
//                                 else
//                                 {                                        
//                                     Device_Obj_Mage[i].Device_Fade_Time=1;                            
//                                 }
//                              }

                            if(device_level>Device_Obj_Mage[i].Device_Current_Level)       //渐暗
                            {
                                     
                                            Device_Obj_Mage[i].switch_direction_statet=Switch_On_to_Off;
                                            
                                        // Device_Obj_Mage[i].Device_Pre_Level=Device_Obj_Mage[i].Device_Current_Level;//Device_Obj_Mage[i].Device_Current_Time;
                                            
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
                                         Device_Obj_Mage[i].switch_direction_statet=Switch_Off_to_On;
                                                                                       
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


void Device_Switch_Management(void)
{
    uint8_t i=0;

    for(i=0;i<12;i++)
    {

        if(Device_Obj_Mage[i].Device_Switch_state==Switch_On_to_Off_delay)
        {
            if((Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct!=0)&&(Device_Obj_Mage[i].Switch_no_delay_flag==0)) 
            {
                Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct--;
                continue;
            }
            Device_Obj_Mage[i].Switch_no_delay_flag=0;
            Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=0;
            Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
            
        //Device_Obj_Mage[i].switch_direction_statet=Switch_no_direction;
            
            Device_Switch(i+1, Switch_Off);
            
        }
        else if(Device_Obj_Mage[i].Device_Switch_state==Switch_Off_to_On_delay)
        {
            if((Device_Obj_Mage[i].Device_Switch_On_Delay_Ct!=0)&&(Device_Obj_Mage[i].Switch_no_delay_flag==0)) 
            {
                Device_Obj_Mage[i].Device_Switch_On_Delay_Ct--;
                continue;
            }
          Device_Obj_Mage[i].Switch_no_delay_flag=0;
            Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=0;
            Device_Obj_Mage[i].Device_Switch_state=Switch_On;
            
        //    Device_Obj_Mage[i].switch_direction_statet=Switch_no_direction;
            
            Device_Switch(i+1, Switch_On);                    
        }    
    }
    
}


void Device_Adjuts_Management(void)
{
     uint8_t i=0;
    uint8_t device_level;
    static uint8_t fade_step[8];
    for(i=0;i<12;i++)
    {
            if(Device_Obj_Mage[i].Device_Fade_Time)
          {
                Device_Obj_Mage[i].Device_Fade_Time--;

                fade_step[i]++;
                if((Device_Obj_Mage[i].Device_Fade_Time==0)&&(Device_Obj_Mage[i].Device_Current_Level!=Device_Obj_Mage[i].Device_Dest_Level))
                {
                     Device_Obj_Mage[i].Device_Current_Level=Device_Obj_Mage[i].Device_Dest_Level;  //这个地方还是需要判断是否是实际值，需要打补丁
                     Device_Obj_Mage[i].Device_Fade_Step=0;
                }
                if(fade_step[i]>=Device_Obj_Mage[i].Device_Fade_Step)
                {
                    fade_step[i]=0;
                    if(Device_Obj_Mage[i].switch_direction_statet==Switch_On_to_Off)
                    {
                      Device_Obj_Mage[i].Device_Current_Level++;
                        
                        if(Device_Obj_Mage[i].Device_Current_Level>=Device_Obj_Mage[i].Device_Dest_Level)
                        {
                            Device_Obj_Mage[i].Device_Current_Level=Device_Obj_Mage[i].Device_Dest_Level;
                            Device_Obj_Mage[i].Device_Fade_Time=0;
                        }
                            
                        device_level=0XFF-(uint8_t)Device_Obj_Mage[i].Device_Current_Level;  
                        if(device_level<Device_Set_Pra.Memmory_12.Device_Switch_Level[i]&&((Device_Obj_Mage[i].Device_Switch_state==Switch_On)||(Device_Obj_Mage[i].Device_Switch_state==Switch_Off_to_On_delay)))  //&& (Device_Obj_Mage[i].Device_Switch_state==Switch_Off)
                        {
                            if(i<8)
                            {
                                
                             Device_Obj_Mage[i].Device_Switch_state=Switch_On_to_Off_delay;
                            
                         Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=Device_Set_Pra.Memmory_11.Device_Switch_Off_Delay_Time[i]*200;//Device_Set_Pra.Memmory_10.Device_Switch_On_Delay_Time[i]*2000;
                    
                         Device_Obj_Mage[i].Device_Switch_On_Delay_Ct=0;
                            }
                            else
                            {
                                
                           Device_Obj_Mage[i].Device_Switch_state=Switch_On_to_Off_delay;
                            
                         Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=Device_Set_Pra.Memmory_12.Device_Switch_Off_Delay_Time[i-8]*200;//Device_Set_Pra.Memmory_10.Device_Switch_On_Delay_Time[i]*2000;
                    
                         Device_Obj_Mage[i].Device_Switch_On_Delay_Ct=0;        
                            }
                        }

                    }
                    else if(Device_Obj_Mage[i].switch_direction_statet==Switch_Off_to_On)
                    {
                        if(Device_Obj_Mage[i].Device_Current_Level>0)
                        {
                        Device_Obj_Mage[i].Device_Current_Level--;
                        }                
            if(Device_Obj_Mage[i].Device_Current_Level<=Device_Obj_Mage[i].Device_Dest_Level)
                        {
                            Device_Obj_Mage[i].Device_Fade_Time=0;
                            Device_Obj_Mage[i].Device_Current_Level=Device_Obj_Mage[i].Device_Dest_Level;
                        }
                        device_level=0XFF-(uint8_t)Device_Obj_Mage[i].Device_Current_Level;  

                        if((device_level>=Device_Set_Pra.Memmory_12.Device_Switch_Level[i])&&((Device_Obj_Mage[i].Device_Switch_state==Switch_Off)||(Device_Obj_Mage[i].Device_Switch_state==Switch_On_to_Off_delay))) 
                        {                                
                            if(i<4)
                            {
                             //Device_Obj_Mage[i].Device_Switch_state=Switch_On_to_Off_delay;
                             Device_Obj_Mage[i].Device_Switch_state=Switch_Off_to_On_delay;
                                                     
                             Device_Obj_Mage[i].Device_Switch_On_Delay_Ct=Device_Set_Pra.Memmory_10.Device_Switch_On_Delay_Time[i]*200;//Device_Set_Pra.Memmory_10.Device_Switch_On_Delay_Time[i]*2000;
                    
                             Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=0;
                            }
                            else
                            {
                             //Device_Obj_Mage[i].Device_Switch_state=Switch_On_to_Off_delay;
                             Device_Obj_Mage[i].Device_Switch_state=Switch_Off_to_On_delay;    
                            
                             Device_Obj_Mage[i].Device_Switch_On_Delay_Ct=Device_Set_Pra.Memmory_11.Device_Switch_On_Delay_Time[i-4]*200;//Device_Set_Pra.Memmory_10.Device_Switch_On_Delay_Time[i]*2000;
                    
                             Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=0;        
                                
                            }
                        }
                    }

                }

         }
         else
         {
             //Device_Obj_Mage[i].Device_Switch_state=Switch_Off;
             
        //     Device_Obj_Mage[i].Device_Current_Level=Device_Obj_Mage[i].Device_Dest_Level;
            // Device_Obj_Mage[i].Device_Dest_Level= Device_Obj_Mage[i].Device_Current_Level; 
         }
         
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
             for(i=4;i<12;i++)
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
    
    for(i=4;i<8;i++)
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
    
  for(i=8;i<12;i++)
    {
//          if(Device_Set_Pra.Memmory_8.Device_Set_Logic_Channel_1[i] == 0)
//            {
//                is_logic1_valid = 1;
//            }
            
          if( (Device_Set_Pra.Memmory_1.Device_Duplic_Flag_2&(0x01<<(i-8))) ==  1 )
            {
                continue;
            }
            if((area_number==Device_Set_Pra.Memmory_7.Device_Area[i])&&(logic_channel==Device_Set_Pra.Memmory_9.Device_Set_Logic_Channel_2[i-8]))
          {  
                *actual_level=Device_Obj_Mage[i].Device_Current_Level;
                *target_level=Device_Obj_Mage[i].Device_Dest_Level;    
                result = 0;
            }
    }
    
//    if(is_logic1_valid == 1)
//    {
//        result = 1;
//    }
    
    return result;
    
}  





void Device_Preset_Process(uint8_t area_number, uint8_t preset_number, uint32_t fade_time, uint8_t device_join)
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
    }
    

} 

void Device_Switch_Channel(uint8_t channel_number,uint8_t channel_state)
{
    if(channel_state==SET)
    {
        // Device_Obj_Mage[channel_number].Device_Pre_Time=Fore_Time;
     //Device_Obj_Mage[channel_number].Device_Pre_Time= Effective_no_use_time(channel_number)+L_To_T(0,channel_number);
    }
    else if(channel_state==RESET)
    {
        //Device_Obj_Mage[channel_number].Device_Pre_Time=Fore_Time+Effective_time;
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
     uint8_t device_level;
     for(i=0;i<12;i++)
    {
        Device_Switch(i+1, Switch_Off);    
        Device_Obj_Mage[i].Device_Current_Level=0xFF;
    }
    //Device_Switch_Fuc_Process(0xFF,0xFF,0xFF,0,RESET,0xFF);
     for(i=0;i<12;i++)
     {
             Device_Preset_Process(Device_Set_Pra.Memmory_7.Device_Area[i],Device_Set_Pra.Memmory_35.set_save[i],50,0xFF);
//Device_Obj_Mage[i].Device_Current_Level = 0xFF;
           
//            device_level=0XFF-(uint8_t)Device_Obj_Mage[i].Device_Current_Level; 
//         
//         
//                if(device_level<Device_Set_Pra.Memmory_12.Device_Switch_Level[i])  //&& (Device_Obj_Mage[i].Device_Switch_state==Switch_Off)
//                {
//           
//                     Device_Obj_Mage[i].Device_Switch_state=Switch_On_to_Off_delay;
//                    
//                     Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=0;//Device_Set_Pra.Memmory_10.Device_Switch_On_Delay_Time[i]*2000;

//                     Device_Obj_Mage[i].Device_Switch_On_Delay_Ct=0;
//              }
//                 else if(device_level>=Device_Set_Pra.Memmory_12.Device_Switch_Level[i]) //&&(Device_Obj_Mage[i].Device_Switch_state==Switch_On)
//                {                                
//                         Device_Obj_Mage[i].Device_Switch_state=Switch_Off_to_On_delay;
//                        
//                         Device_Obj_Mage[i].Device_Switch_On_Delay_Ct=0;//Device_Set_Pra.Memmory_10.Device_Switch_On_Delay_Time[i]*2000;
//                
//                         Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=0;
//                }
                
                
                
//                Device_Obj_Mage[i].Device_Current_Level = Device_Set_Pra.Memmory_28.level_save[i];
//            device_level=0XFF-(uint8_t)Device_Obj_Mage[i].Device_Current_Level;
//                    if(device_level<Device_Set_Pra.Memmory_12.Device_Switch_Level[i])  //&& (Device_Obj_Mage[i].Device_Switch_state==Switch_Off)
//                {
//           
//                     Device_Obj_Mage[i].Device_Switch_state=Switch_On_to_Off_delay;
//                    
//                     Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=0;//Device_Set_Pra.Memmory_10.Device_Switch_On_Delay_Time[i]*2000;

//                     Device_Obj_Mage[i].Device_Switch_On_Delay_Ct=0;
//              }
//                 else if(device_level>=Device_Set_Pra.Memmory_12.Device_Switch_Level[i]) //&&(Device_Obj_Mage[i].Device_Switch_state==Switch_On)
//                {                                
//                         Device_Obj_Mage[i].Device_Switch_state=Switch_Off_to_On_delay;
//                        
//                         Device_Obj_Mage[i].Device_Switch_On_Delay_Ct=0;//Device_Set_Pra.Memmory_10.Device_Switch_On_Delay_Time[i]*2000;
//                
//                         Device_Obj_Mage[i].Device_Switch_Off_Delay_Ct=0;
//                }
                

    
   }
 }     

void led_func(void)
{
        
     if(g_device_state==Device_No_Okay)
    {
        return;
    }
    
    //HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
    
}

