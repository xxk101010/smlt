
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
#include  "smlt_cfg.h"
#include  "smlt_port.h"


#define  SMLT_VERSION            0x0100


#ifndef   FALSE
#define   FALSE                     (0)
#endif
#ifndef  TRUE
#define  TRUE                       (1)

/* exact-width signed integer types */
typedef   signed char        int8_t;
typedef   signed short       int16_t;
typedef   signed long        int32_t;
typedef   signed long  long  int64_t;

/* exact-width unsigned integer types */
typedef unsigned  char         uint8_t;
typedef unsigned  short        uint16_t;
typedef unsigned  long         uint32_t;
typedef unsigned  long long    uint64_t;


#define SMLT_PTR_FREE(ptr)                                              do                       \
                                                                        {                        \
                                                                             if (ptr)            \
                                                                             {                   \
                                                                                 free(ptr);      \
                                                                                 ptr = NULL;     \
                                                                              }                  \
                                                                         }while (0)
                             
#define SMLT_PTR_CHECK(ptr, flag)                                        do                                                                           \
                                                                         {                                                                            \
                                                                              if (NULL == ptr)                                                        \
                                                                              {                                                                       \
                                                                                  smlt_err("%s(): %d point is NULL.\n", __FUNCTION__, __LINE__);      \
                                                                                  goto flag;                                                          \
                                                                              }                                                                       \
                                                                         }while (0)

#endif

#ifdef __cplusplus
};
#endif

#endif

