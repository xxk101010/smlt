
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
void* smlt_engine_new(char *cfg)
{
    smlt_engine_t *pstSmltEngine = NULL;
	
    pstSmltEngine = (smlt_engine_t *)smlt_calloc(sizeof(smlt_engine_t), 1);
    if(pstSmltEngine == NULL)
    {
        return  NULL;
    }
    pstSmltEngine->dev_type = SMLT_MODULE;
    pstSmltEngine->chNum = SMLT_CHANNEL_NUM;

    //pstSmltEngine->ltChCtr_list = list_new();
    //if(pstSmltEngine->ltChCtr_list == NULL)
    //{   
    //    goto FAIL;
    //}
	/*  key related */
	pstSmltEngine->keyObj =  smlt_key_init();
	if(pstSmltEngine->keyObj == NULL)
	{
	    goto FAIL;
	}
	/* add serv key */
	smlt_key_add(pstSmltEngine->keyObj, smlt_keyServ_get, smlt_servCallback, KEY_SERV_NAME);
	return pstSmltEngine;
	
FAIL:
    if(pstSmltEngine)
    {
        if(pstSmltEngine->ltChCtr_list) 
        {
            SMLT_PTR_FREE(pstSmltEngine->ltChCtr_list);
        }
        SMLT_PTR_FREE(pstSmltEngine);
    }
    return NULL;
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
int smlt_engine_run(void* pstSmltEng_handle)
{
    smlt_engine_t *pstSmltEngine = NULL;

	  if(pstSmltEng_handle == NULL)
	  {
	      return -1;
	  }
	  pstSmltEngine = (smlt_engine_t *)pstSmltEng_handle;
    smlt_key_scan(pstSmltEngine->keyObj);
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
void smlt_engine_delete(void* pstSmltEng_handle)
{
    if(pstSmltEng_handle)
    {
        SMLT_PTR_FREE(pstSmltEng_handle);
    }
}

