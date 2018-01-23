

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
#include "smlt_light.h"

/************************************************************
  Function   : smlt_key_init()

  Description: config init
  Calls      :
  Called By  :
  Input      : pstFendCfg   : config structure
               cfg          : config bin file
  Output     :
  Return     :
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
smlt_ltObj_mgmt_t* smlt_lgObj_new(void)
{
    uint8_t i;
    smlt_ltObj_mgmt_t *ltObj = NULL;
    list_t *key_list = NULL;

    ltObj = (smlt_ltObj_mgmt_t *)smlt_calloc(sizeof(smlt_ltObj_mgmt_t), 1);
    if(ltObj)
    {
        return  NULL;
    }
    ltObj->ltObj_list = list_new();
    if(ltObj->ltObj_list == NULL)
    {
        goto FAIL;   
        return NULL;
    }
    ltObj->light_num = SMLT_CHANNEL_NUM;
    for (i = 0; i < ltObj->light_num ; i++)
    {
        list_node_t *listNode = NULL;
        smlt_ltChCtr_t *ltNode = NULL;

        ltNode =  (smlt_ltChCtr_t *)smlt_calloc(1, sizeof(smlt_ltChCtr_t));
        ltNode->ChNo = i;
#if  (SMLT_MODULE==SMLT_SWITCH_MODULE)
        ltNode->is_switch = TRUE;
#endif
        listNode = list_node_new(ltNode);
        if(ltNode ==NULL || listNode == NULL)
        {
            goto FAIL;
        }
        list_rpush(ltObj->ltObj_list, listNode);        
    }
    return ltObj;

FAIL:
    if(ltObj)
    {
        smlt_lgObj_delete(ltObj)
    }
    return NULL;

}

/************************************************************
  Function   : void* smlt_key_add(smlt_keyObj_mgmt_t *keyObj, void *IoGetReg, void *KeyEventCb)

  Description: config init
  Calls      :
  Called By  :
  Input      : pstFendCfg   : config structure
               cfg          : config bin file
  Output     :
  Return     :
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
void smlt_lgObj_delete(smlt_ltObj_mgmt_t* ltObj)
{
    if(ltObj)
    {
        /* need modified */
        SMLT_PTR_FREE(ltObj);
    }
}

/************************************************************
  Function   : void smlt_key_remove(smlt_keyObj_mgmt_t *keyObj, void *keyHandle)

  Description: config init
  Calls      :
  Called By  :
  Input      : pstFendCfg   : config structure
               cfg          : config bin file
  Output     :
  Return     :
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
int8_t smlt_light_set(smlt_ltObj_mgmt_t* ltObj, uint8_t ch, uint16_t level, uint32_t fade_time)
{
    uint16_t i = 0;
    smlt_ltChCtr_t *ltNode = NULL;
    

    ltNode = list_at(ltObj->ltObj_list, ch);
    
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

}


/************************************************************
  Function   : void smlt_key_remove(smlt_keyObj_mgmt_t *keyObj, void *keyHandle)

  Description: config init
  Calls      :
  Called By  :
  Input      : pstFendCfg   : config structure
               cfg          : config bin file
  Output     :
  Return     :
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
void smlt_light_process(smlt_ltChCtr_t *ltNode)
{
    uint16_t i = 0;

    for (i = 0; i < keyObj->key_num; i++)
    {
        listNode = list_at(keyObj->keyObj_list, i);
        keyNode = listNode->val;
        if(keyNode->IoCallBack_fnPtr())
        {
            keyNode->keyVal = KEY_DOWN;
            keyNode->keyDownCnt++;
            keyNode->keyUpCnt = 0;
        }    
        else
        {
            keyNode->keyVal = KEY_UP;
            keyNode->keyUpCnt++;
            keyNode->keyDownCnt = 0;
        }
        smlt_key_process(keyNode);    
    }
}

