/***********************************************************************************
 * �� �� ��   : kj_key.h
 * �� �� ��   : kun
 * ��������   : 2017��12��24��
 * �ļ�����   : kj_key.h  key obj mgmt
 * ��Ȩ˵��   : Copyright (c) 2008-2017   xx xx xx xx �������޹�˾
 * ��    ��   :
 * �޸���־   :
***********************************************************************************/
#ifndef _SMLT_PORT_H_
#define  _SMLT_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif


#ifndef       SMLT_MEMORY_MGMT
#define       calloc                   calloc
#define       malloc                   malloc
#define       free                     free
#else
#define       SMLT_MEMORY_ADDR
#define       SMLT_MEMORY_LEN
#endif

#ifdef __cplusplus
};
#endif

#endif


