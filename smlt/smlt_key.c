

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
#include "protoal.h"


char smlt_servCallback(char event)
{
    switch((smlt_keyEvent_t)event)
    {
        case KEY_EVENT_UP:
        {
            break;
        }
        case KEY_EVENT_DOWN:
        {
            CMD_Search_CMD();
            break;
        }
        case KEY_EVENT_PRESSED:
        {
            break;
        }
        case KEY_EVENT_LONG_PRESSED:
        {
            break;
        }
        default:
        {
            break;
        }
    }
    return 0;
}


