

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
  Function   : smlt_keyObj_mgmt_t* smlt_engine_new(char *cfg)

  Description: config init
  Calls      :
  Called By  :
  Input      :    cfg          : config json
  Output     :
  Return     :
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
smlt_keyObj_mgmt_t* smlt_engine_new(char *cfg)
{
    smlt_keyObj_mgmt_t *pstSmltEngine = NULL;

    pstSmltEngine = (smlt_keyObj_mgmt_t *)smlt_calloc(sizeof(smlt_keyObj_mgmt_t), 1);
    if(pstSmltEngine == NULL)
    {
        return  NULL;
    }
    return pstSmltEngine;
}

