/***********************************************************************************
 * �� �� ��   : kj_key.h
 * �� �� ��   : kun
 * ��������   : 2017��12��24��
 * �ļ�����   : kj_key.h  key obj mgmt
 * ��Ȩ˵��   : Copyright (c) 2008-2017   xx xx xx xx �������޹�˾
 * ��    ��   :
 * �޸���־   :
***********************************************************************************/
#ifndef  _SMLT_CFG_H_
#define  _SMLT_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define      SMLT_DEBUG

#define      SMLT_SWITCH_MODULE    (0x94)
#define      SMLT_DIMM_MODULE      (0xE4)

/*   here to choose MODULE  */
#define      SMLT_MODULE           SMLT_SWITCH_MODULE 
/*   here to choose channel Num(less than 16)  */
#define      SMLT_CHANNEL_NUM      6
/*   here to choose smlt poll freq (example 1000hz = delay 1ms)  */
#define      SMLT_POLL_FREQ        1000
/*   here to deside lever max  */
#define      SMLT_LEVER_MAX        255
/*     here to deside serv key  */
#define      SMLT_SERV_KEY
#define      KEY_SERV_NAME         "serv"
/*     here to deside arch   */
#define      SMLT_ARM_STM32F103


#ifdef __cplusplus
};
#endif

#endif


