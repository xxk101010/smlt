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
#ifndef _SMLT_ENGINE_H_
#define  _SMLT_ENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "smlt_common.h"
#include "smlt_light.h"


typedef struct _smlt_engine_t
{
    char dev_type;
    /*   channel Num  */
    char chNum;
    char *JsonCfg;
    char *MemCfg;
    /*   list for ligth channel control  */
    list_t *ltChCtr_list;   
}smlt_engine_t;

void*  smlt_engine_new(char *cfg);
int8_t smlt_engine_run(smlt_engine_t* pstSmltEngine);
void   smlt_engine_delete(smlt_engine_t* pstSmltEngine);

#ifdef __cplusplus
};
#endif

#endif

