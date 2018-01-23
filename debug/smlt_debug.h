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
#ifndef  _SMLT_DEBUG_H_
#define  _SMLT_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "smlt_common.h"

#define smlt_err(...)           do    \
                                {     \
                                    smlt_printf("\n****************** FEND Error in %s() %d *********************\n", __FUNCTION__, __LINE__);    \
                                    smlt_printf(__VA_ARGS__); \
                                    smlt_printf("******************    FEND Error End     *********************\n"); \
                                } while (0)

#define smlt_info(...)          do    \
                                {    \
                                    smlt_printf("\n****************** FEND Info in %s() %d ***********************\n", __FUNCTION__, __LINE__);    \
                                    smlt_printf(__VA_ARGS__); \
                                    smlt_printf("******************    FEND Info End     ***********************\n"); \
                                } while (0)


#ifdef __cplusplus
};
#endif

#endif

