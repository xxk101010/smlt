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
#include "smlt_key.h"

typedef struct _smlt_engine_t
{
	int 	 keyObj_is_enalbe;
	int 	 key_num;
	list_t	 *keyObj_list;
}smlt_engine_t;


#ifdef __cplusplus
};
#endif

#endif

