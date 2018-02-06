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
#ifndef _SMLT_DEV_KEY_H_
#define  _SMLT_DEV_KEY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "smlt_common.h"
#include "smlt_list.h"

typedef char (*smlt_IoGetStatus)(void);
typedef char (*smlt_IoCallBack)(char);

#define KEY_NAME_MAX            10
#define KEY_DITHERLESS_DELAY    30      


#define KEY_HOLD_TIME           10              
#define KEY_REPEAT_TIME         3                
#define KEY_LONGHOLD_TIME       30               
#define KEY_DELAY_        0
#define KEY_LOOP_CHECK          1

typedef enum
{
    KEY_UP            = 0,
    KEY_DOWN,
}smlt_keyStatus_t;

typedef enum
{
    KEY_EVENT_UP_NULL = 0,
    KEY_EVENT_UP,                  //!< key release
    KEY_EVENT_DOWN,                //!< key press down
    KEY_EVENT_PRESSED,             //!< key pressed
    KEY_EVENT_LONG_PRESSED,        //!< key long pressed
    KEY_EVENT_REPEAT,              //!< key repeat
}smlt_keyEvent_t;

typedef enum
{
    FSM_KEY_NONE = 0,
    FSM_KEY_UP,                    //!< key released
    FSM_KEY_UP_HOLD,               //!< key released sure hold
    FSM_KEY_DOWN,                  //!< key press down
    FSM_KEY_DOWN_HOLD,             //!< key press down sure hold
}smlt_keyFsm_t;

typedef struct _smlt_keyNode
{
    UINT16_t         keyDownCnt; 
    UINT16_t         keyUpCnt; 
    UINT8_t          keyVal;
    char             name[KEY_NAME_MAX];
    smlt_keyFsm_t    KsyFsm;
    smlt_keyEvent_t  KeyEvent;
    smlt_IoGetStatus IoGetStatus_fnPtr;
    smlt_IoCallBack  IoCallBack_fnPtr;
}smlt_keyNode_t;

typedef struct _smlt_keyObj_mgmt
{
    int        keyObj_is_enalbe;
    int        key_num;
    list_t     *keyObj_list;
}smlt_keyObj_mgmt_t;


smlt_keyObj_mgmt_t* smlt_key_init(void);
smlt_keyNode_t *smlt_key_add(smlt_keyObj_mgmt_t *keyObj_handle, void *IoGetReg, void *KeyEventCb, char *name);
void smlt_key_remove(smlt_keyObj_mgmt_t *keyObj_handle, void *keyHandle);
void smlt_key_scan(smlt_keyObj_mgmt_t *keyObj_handle);

#ifdef __cplusplus
};
#endif

#endif

