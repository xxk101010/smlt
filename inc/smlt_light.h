/************************************************************
  Copyright (C), AISpeechTech. Co., Ltd.

  FileName   : aispeech_type.h
  Project    : 
  Module     : 
  Version    : 
  Date       : 2017/02/15
  Author     : Youhai.Jiang
  Document   : 
  Description: 

  Function List :

  History :
  <author>      <time>            <version >        <desc> 
  Youhai.Jiang  2017/02/15         1.00              Create

************************************************************/
#ifndef _SMLT_LIGHT_H_
#define  _SMLT_LIGHT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "smlt_common.h"

#if (SMLT_MODULE==SMLT_SWITCH_MODULE)
#define LEVER_TO_TIME(l)       (l)           
#define TIME_TO_LEVER(t)       (t)
#else

#endif

#define SMLT_DIRE_NONE             0
#define SMLT_DIRE_UP               1
#define SMLT_DIRE_DOWN             2

typedef struct _smlt_ltObj_mgmt
{
    char      light_num;
    //uint16_t  fade_step;
    list_t    *ltObj_list;
}smlt_ltObj_mgmt_t;

typedef struct _smlt_ltChCtr      // light phy channel ctr 
{
    /*   channel Number      */
    char ChNo;
    /*   is switch            */
    char is_switch;
    /*   if switch mode, need threshold val */
    uint16_t thresh_val;
    /*   ptr to cfg mem       */
    void *CfgPtr;  
    /*   current lever         */
   // uint16_t curLever;
    /*   current time         */
    uint16_t curTime;
    /*   update time for dim  */
    uint16_t updateTime;
    /*   dest time            */
    uint16_t destTime;
    /*   fade step (up to fade time)  */
    uint16_t fade_step;
    /*   fade direction  */
    uint8_t  fade_direction;
    /*   fade count  */
    uint16_t fade_step_cnt;
    /*   delay time  */
    uint32_t fade_time;
    /*   delay time  */
    uint16_t delay_time;  
}smlt_ltChCtr_t;

smlt_ltObj_mgmt_t* smlt_lgObj_new(void);
void smlt_lgObj_delete(smlt_ltObj_mgmt_t* ltObj);

#ifdef __cplusplus
};
#endif

#endif

