
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
#include "smlt_engine.h"

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
smlt_engine_t* smlt_engine_new(char *cfg)
{
    int8_t ret = 0;
    smlt_engine_t *pstSmltEngine = NULL;
    list_t *key_list = NULL;

    pstSmltEngine = (smlt_keyObj_mgmt_t *)smlt_calloc(sizeof(smlt_keyObj_mgmt_t), 1);
    if(pstSmltEngine == NULL)
    {
        return  NULL;
    }
    pstSmltEngine->dev_type = SMLT_MODULE;
    pstSmltEngine->chNum = SMLT_CHANNEL_NUM;

    pstSmltEngine->ltChCtr_list = list_new();
    if(pstSmltEngine->ltChCtr_list == NULL)
    {   
        ret = -1;
        goto FAIL;
    }
    
    return pstSmltEngine;
FAIL:
    if(pstSmltEngine)
    {
        if(pstSmltEngine->ltChCtr_list) 
        {
            
        }
    }
    return ret;
}

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
int8_t smlt_engine_run(smlt_engine_t* pstSmltEngine)
{
    return 0;
}

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
void smlt_engine_delete(smlt_engine_t* pstSmltEngine)
{
    if(pstSmltEngine)
    {
        SMLT_PTR_FREE(pstSmltEngine);
    }
}



