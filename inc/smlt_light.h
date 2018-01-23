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
#include "smlt_light.h"


#define SMLT_LEVER_MAX  0xFF


typedef struct _smlt_ltChCtr      // light phy channel ctr 
{
    /*   channel Number  */
    char ChNo;
    /*   is switch       */
    char is_switch;
    /*   ptr to cfg mem  */
    void *CfgPtr;  
    /*   current lever */
    uint16_t curLever;
    /*   dest lever    */
    uint16_t destLever;
        
}smlt_ltChCtr_t;



#ifdef __cplusplus
};
#endif

#endif

