
#ifndef __SMLT_ARCH_H__
#define __SMLT_ARCH_H__

#define  SMLT_ARM_STM32F103

#include "port/smlt_port.h"

#if   defined ( __CC_ARM )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */
  #define __STATIC_INLINE  static __inline
#elif defined ( __ICCARM__ )
  #define __ASM            __asm                                      /*!< asm keyword for IAR Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */
  #define __STATIC_INLINE  static inline
#elif defined ( __GNUC__ )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */
  #define __STATIC_INLINE  static inline
#endif


#define SMLT_CPU             8000000L
#define SMLT_DEALY_CNT       (SMLT_CPU/1000/1000/4)

#pragma push     
#pragma O3         
#pragma Ospace   
__forceinline void smlt_delayUs(register unsigned long volatile us)
{
    unsigned long i;

    for (i = 0; i < us; i++)
    {
        __ASM("NOP");
        __ASM("NOP");
        __ASM("NOP");
        __ASM("NOP");
    }
}
#pragma pop 


#endif

