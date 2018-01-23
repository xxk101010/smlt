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

#define SMLT_LEVER_MAX  0xFF

typedef struct _smlt_ltObj_mgmt
{
    char      light_num;
    uint16_t  fade_step;
    list_t    *ltObj_list;
}smlt_ltObj_mgmt_t;

typedef struct _smlt_ltChCtr      // light phy channel ctr 
{
    /*   channel Number  */
    char ChNo;
    /*   is switch       */
    char is_switch;
    /*   if switch mode, need threshold val */
    uint16_t thresh_val;
    /*   ptr to cfg mem  */
    void *CfgPtr;  
    /*   current lever   */
    uint16_t curLever;
    /*   dest lever      */
    uint16_t destLever;
    /*   dest lever      */
         
}smlt_ltChCtr_t;

smlt_ltObj_mgmt_t* smlt_lgObj_new(void);
void smlt_lgObj_delete(smlt_ltObj_mgmt_t* ltObj);

#ifdef __cplusplus
};
#endif

#endif

