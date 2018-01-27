

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

#include "smlt_key.h"

static void smlt_key_process(smlt_keyNode_t *keyNode);
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
smlt_keyObj_mgmt_t* smlt_key_init(void)
{
    smlt_keyObj_mgmt_t *keyObj = NULL;

    keyObj = (smlt_keyObj_mgmt_t *)smlt_calloc(sizeof(smlt_keyObj_mgmt_t), 1);
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

/************************************************************
  Function   : void* smlt_key_add(smlt_keyObj_mgmt_t *keyObj, void *IoGetReg, void *KeyEventCb)

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
void *smlt_key_add(smlt_keyObj_mgmt_t *keyObj, void *IoGetReg, void *KeyEventCb)
{
    list_node_t *listNode = NULL;
    smlt_keyNode_t *keyNode = NULL;

    if ( keyObj == NULL )
    {
        return NULL;
    }
    keyNode = (smlt_keyNode_t *)smlt_calloc(1, sizeof(smlt_keyNode_t));
    if(keyNode)
    {
        return NULL;
    }
    keyNode->IoGetStatus_fnPtr = (smlt_IoGetStatus)IoGetReg;
    keyNode->IoCallBack_fnPtr = (smlt_IoCallBack)KeyEventCb;
    keyNode->KsyFsm = FSM_KEY_NONE;
    
    listNode = list_node_new(keyNode);
    if(listNode == NULL)
    {
        if(keyNode)
        {
			      smlt_free(keyNode);  
        }    
        return NULL;
    }
    list_rpush(keyObj->keyObj_list, listNode);
    keyObj->key_num++;
    return (void *)listNode;
}

/************************************************************
  Function   : void smlt_key_remove(smlt_keyObj_mgmt_t *keyObj, void *keyHandle)

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
void smlt_key_remove(smlt_keyObj_mgmt_t *keyObj, void *keyHandle)
{
    list_node_t *listNode = NULL;
    smlt_keyNode_t *keyNode = NULL;

    if ( keyObj == NULL ||  keyHandle == NULL)
    {
        return;
    }

    listNode = (list_node_t *)keyHandle;
    keyNode = (smlt_keyNode_t *)(listNode->val);

    free(keyNode);
    list_remove(keyObj->keyObj_list, listNode);
    keyObj->key_num--;
}


/************************************************************
  Function   : void smlt_key_remove(smlt_keyObj_mgmt_t *keyObj, void *keyHandle)

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
void smlt_key_scan(smlt_keyObj_mgmt_t *keyObj)
{
    uint16_t i = 0;
    list_node_t *listNode = NULL;
    smlt_keyNode_t *keyNode = NULL;
    
    for (i = 0; i < keyObj->key_num; i++)
    {
        listNode = list_at(keyObj->keyObj_list, i);
        keyNode = listNode->val;
        if(keyNode->IoGetStatus_fnPtr())
        {
            keyNode->keyVal = KEY_DOWN;
            keyNode->keyDownCnt++;
            keyNode->keyUpCnt = 0;
        }    
        else
        {
            keyNode->keyVal = KEY_UP;
            keyNode->keyUpCnt++;
            keyNode->keyDownCnt = 0;
        }
        smlt_key_process(keyNode);    
    }
}

/************************************************************
  Function   : void smlt_key_process(smlt_keyNode_t *keyNode)

  Description: config init
  Calls      :
  Called By  :
  Input      : keyNode   :

  Output     :
  Return     :
  Others     :

  History    :
    2017/10/26, kun.xu create
************************************************************/
static void smlt_key_process(smlt_keyNode_t *keyNode)
{
    switch (keyNode->KsyFsm)
    {
        case FSM_KEY_NONE:
        {
            if(keyNode->keyVal)
            {
                keyNode->KsyFsm = FSM_KEY_DOWN;
            }
            else
            {
                keyNode->KsyFsm = FSM_KEY_UP;
            }
            //break;
        }
        case FSM_KEY_UP:
        {     
            if(keyNode->keyVal)
            {
                keyNode->KsyFsm = FSM_KEY_DOWN;
                break;
            }
            if(keyNode->keyUpCnt >=  KEY_DITHERLESS_DELAY)
            {
                keyNode->KsyFsm = FSM_KEY_UP_HOLD;
                keyNode->IoCallBack_fnPtr(KEY_EVENT_UP);
            }
            else
            {
              break;  
            }   
        }
        case FSM_KEY_UP_HOLD:
        {
            if(keyNode->keyVal)
            {
                keyNode->KsyFsm = FSM_KEY_DOWN;
                break;
            }
            break;
        }
        case FSM_KEY_DOWN:
        {
            if(!keyNode->keyVal)
            {
                keyNode->KsyFsm = FSM_KEY_UP;
                break;
            }
            if(keyNode->keyDownCnt >=  KEY_DITHERLESS_DELAY)
            {
                keyNode->KsyFsm = FSM_KEY_DOWN_HOLD;
                keyNode->IoCallBack_fnPtr(KEY_EVENT_DOWN);
            }
            else
            {
               break;  
            }         
            break;
        }
        case FSM_KEY_DOWN_HOLD:
        {
            if(!keyNode->keyVal)
            {
                keyNode->KsyFsm = FSM_KEY_UP;
                break;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

