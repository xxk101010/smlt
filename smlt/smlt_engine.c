

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
  Function   : smlt_key_init()

  Description: config init
  Calls      :
  Called By  :
  Input      : pstFendCfg   : config structure
               cfg          : config bin file
  Output     :
  Return     :
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
smlt_keyObj_mgmt_t* smlt_engine_new(char *cfg)
{
	smlt_keyObj_mgmt_t *keyObj = NULL;
	list_t *key_list = NULL;

	keyObj = (smlt_keyObj_t *)smlt_calloc(sizeof(smlt_keyObj_t), 1);
	if(keyObj)
    {
        return  NULL;
    }
	keyObj->keyObj_list = list_new();
	if(keyObj->keyObj_list == NULL)
    {
    	smlt_free(keyObj);
        return NULL;
    }
	
    keyObj->key_num = 0;
	keyObj->keyObj_is_enalbe = 1;
	return keyObj;
}


