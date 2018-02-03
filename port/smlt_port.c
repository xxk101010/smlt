
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
#include "smlt_port.h"
#include "stm32f0xx_hal.h"

char smlt_keyServ_get(void)
{
    return !(char)HAL_GPIO_ReadPin(Service_GPIO_Port, Service_Pin);
}

