
/***********************************************************************************
 * �� �� ��   : kj_key.h
 * �� �� ��   : kun
 * ��������   : 2017��12��24��
 * �ļ�����   : kj_key.h  key obj mgmt
 * ��Ȩ˵��   : Copyright (c) 2008-2017   xx xx xx xx �������޹�˾
 * ��    ��   :
 * �޸���־   :
***********************************************************************************/
#ifndef _SMLT_COMMON_H_
#define  _SMLT_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdlib.h"
#include "list.h"
#include  "..\port\smlt_port.h"

#ifndef  FALSE
#define   FALSE                     (0)
#endif
#ifndef  TRUE
#define  TRUE                       (1)

/* exact-width signed integer types */
typedef   signed		  char int8_t;
typedef   signed short	   int int16_t;
typedef   signed		   int int32_t;
typedef   signed	   __INT64 int64_t;

/* exact-width unsigned integer types */
typedef unsigned		  char uint8_t;
typedef unsigned short	   int uint16_t;
typedef unsigned		   int uint32_t;
typedef unsigned	   __INT64 uint64_t;


#endif

#ifdef __cplusplus
};
#endif

#endif

