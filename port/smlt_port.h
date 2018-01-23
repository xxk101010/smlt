/***********************************************************************************
 * 文 件 名   : kj_key.h
 * 负 责 人   : kun
 * 创建日期   : 2017年12月24日
 * 文件描述   : kj_key.h  key obj mgmt
 * 版权说明   : Copyright (c) 2008-2017   xx xx xx xx 技术有限公司
 * 其    他   :
 * 修改日志   :
***********************************************************************************/
#ifndef _SMLT_PORT_H_
#define  _SMLT_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif


#define    SMLT_MEMORY_MGMT
#define    SMLT_PRINTF



#ifndef       SMLT_MEMORY_MGMT
#define       smlt_calloc                   calloc
#define       smlt_malloc                   malloc
#define       smlt_free                     free
#else
#define       SMLT_MEMORY_ADDR
#define       SMLT_MEMORY_LEN
#endif


#ifdef        SMLT_PRINTF
#define       smlt_printf  
#else
#define       smlt_printf  
#endif


#ifdef __cplusplus
};
#endif

#endif


