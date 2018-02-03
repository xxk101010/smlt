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
  smlt_ltObj_mgmt_t* smlt_lgObj_new(void)

  Description: config init
  Calls      :
  Called By  :
  Input      : 
  Output     :
  Return     : handle of light obj mgmt 
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
smlt_ltObj_mgmt_t* smlt_lgObj_new(void)
{
    UINT8_t i;
    smlt_ltObj_mgmt_t *ltObj = NULL;

    ltObj = (smlt_ltObj_mgmt_t *)smlt_calloc(sizeof(smlt_ltObj_mgmt_t), 1);
    if(ltObj)
    {
        return  NULL;
    }
    ltObj->ltObj_list = list_new();
    if(ltObj->ltObj_list == NULL)
    {
        goto FAIL;   
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
        smlt_lgObj_delete(ltObj);
    }
    return NULL;
}

/************************************************************
  Function   : void smlt_lgObj_delete(smlt_ltObj_mgmt_t* ltObj)

  Description: config init
  Calls      :
  Called By  :
  Input      : ltObj:   : handle of  light obj mgmt 
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
  Function   : INT8_t smlt_light_set(smlt_ltObj_mgmt_t* ltObj, uint8_t ch, uint16_t level, uint32_t fade_time, uint32_t delay_time)

  Description: config init
  Calls      :
  Called By  :
  Input      : ltObj:   : handle of  light obj mgmt 
  Output     :
  Return     :
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
INT8_t smlt_light_set(smlt_ltObj_mgmt_t* ltObj, UINT8_t ch, UINT16_t level, UINT32_t fade_time, UINT32_t delay_time)
{
    UINT32_t time_change;
    smlt_ltChCtr_t *ltNode = NULL;
	list_node_t *list_node = NULL;
    
    if(ltObj == NULL)
    {
        return -1;
    }
    
    if(level == 0 || level == SMLT_LEVER_MAX)
    {
        return 0;
    }   

    list_node = list_at(ltObj->ltObj_list, ch);
		ltNode = (smlt_ltChCtr_t *)list_node->val;
    if(ltNode->curTime > LEVER_TO_TIME(level))
    {
        ltNode->fade_direction = SMLT_DIRE_DOWN;
    }
    else if(ltNode->curTime < LEVER_TO_TIME(level))
    {
        ltNode->fade_direction = SMLT_DIRE_UP;
    }
    else
    {
        ltNode->fade_direction = SMLT_DIRE_NONE;
        ltNode->fade_step_cnt = 0;
        ltNode->fade_time     = 0;
        ltNode->delay_time    = 0;
        return 0;  
    }

    if(fade_time == 0)
    {
        fade_time = 1;
    }
    ltNode->destTime   = LEVER_TO_TIME(level);
    if(ltNode->fade_direction == SMLT_DIRE_DOWN)
    {
        time_change = ltNode->curTime - ltNode->destTime;
    }
    else
    {
        time_change = ltNode->destTime - ltNode->curTime;
    }
    ltNode->fade_step = fade_time/time_change;
    if(ltNode->fade_step == 0)
    {
       ltNode->fade_step = 1; 
    }
    ltNode->fade_step_cnt = 0;
    ltNode->fade_time     = fade_time;
    ltNode->delay_time    = delay_time;
    return 0;
}

/************************************************************
  Function   : void smlt_light_process(smlt_ltObj_mgmt_t* ltObj)

  Description: config init
  Calls      :
  Called By  :
  Input      : ltObj        : handle of  light obj mgmt 
  Output     :
  Return     :
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
void smlt_light_process(smlt_ltObj_mgmt_t* ltObj)
{
    UINT16_t i = 0;
	  
    for ( i = 0; i < ltObj->light_num; i++ )
    {
       smlt_ltChCtr_t *ltNode = NULL;
			 list_node_t *list_node = NULL;
 
        list_node = list_at(ltObj->ltObj_list, i);
		  	ltNode = (smlt_ltChCtr_t *)list_node->val;
        if(ltNode->fade_time)
        {
            ltNode->fade_time--;
            ltNode->fade_step_cnt = (ltNode->fade_step_cnt + 1)%ltNode->fade_step;
            if(!ltNode->fade_step_cnt)
            {
                if(ltNode->curTime < ltNode->destTime)
                {
                    ltNode->curTime++;
                    if(ltNode->is_switch)
                    {
                        if(ltNode->curTime == ltNode->thresh_val)
                        {
                            ltNode->switch_status = SMLT_SWITCH_OFF2ON;
                        }
                    }
                }
                else if(ltNode->curTime > ltNode->destTime)
                {
                    ltNode->curTime--;
                    if(ltNode->is_switch)
                    {
                       if((ltNode->curTime + 1) == ltNode->thresh_val)
                       {
                           ltNode->switch_status = SMLT_SWITCH_ON2OFF;
                       }
                    }    
                } 
            }          
        }
		
        if(ltNode->switch_status == SMLT_SWITCH_OFF2ON || ltNode->switch_status == SMLT_SWITCH_ON2OFF)
        {
            if(ltNode->delay_time)
            {
                ltNode->delay_time--; 
				if(ltNode->switch_status == SMLT_SWITCH_OFF2ON)
				{
			        IO_SET_ON(i);
					ltNode->switch_status = SMLT_SWITCH_ON;
					
				}
				else if(ltNode->switch_status == SMLT_SWITCH_ON2OFF)
				{
				    IO_SET_OFF(i);
					ltNode->switch_status = SMLT_SWITCH_OFF;
				}
            }
        } 
		
    }
}
