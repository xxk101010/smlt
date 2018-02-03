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
#ifndef  _SMLT_H_
#define  _SMLT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef  void*   smlt_engHandle_t;

/*  smlt engine related api  */
void* smlt_engine_new(char *cfg);
int  smlt_engine_run(void* pstSmltEng_handle);
void smlt_engine_delete(void* pstSmltEng_handle);

/*  key related api   */

#ifdef __cplusplus
};
#endif

#endif

