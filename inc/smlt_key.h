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
#ifndef _SMLT_KEY_H_
#define  _SMLT_KEY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "smlt_common.h"

typedef uint8_t (*smlt_IoGetStatus)(void);
typedef int8_t  (*smlt_IoCallBack)(char);
                          
#define KEY_DITHERLESS_DELAY    10      


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
	uint16_t         keyDownCnt; 
	uint16_t         keyUpCnt; 
	uint8_t          keyVal;
	smlt_keyFsm_t    KsyFsm;
	smlt_keyEvent_t  KeyEvent;
    smlt_IoGetStatus *IoGetStatus_fnPtr;
	smlt_IoCallBack  *IoCallBack_fnPtr;
}smlt_keyNode_t;

typedef struct _smlt_keyObj_mgmt
{
	int      keyObj_is_enalbe;
    int      key_num;
    list_t   *keyObj_list;
}smlt_keyObj_mgmt_t;

void smlt_key_init(void);

#ifdef __cplusplus
};
#endif

#endif

