#ifndef __BSP_RSKRL78L12_H
#define __BSP_RSKRL78L12_H


#if defined ( __IAR_SYSTEMS_ICC__ )    /*!< IAR Compiler. Only avaiable in High optimization mode! */

/* RL78 and IAR compiler specific stuff */
#include "ior5f10rlc.h"
#include "ior5f10rlc_ext.h"
#include "intrinsics.h"

  #define __STATICINLINE(foo)   static inline foo
  #define __WEAKFUNC(foo)       __weak foo
  #define __INLINE(foo)         inline foo

#endif



/* LCD device interface*/
#include "LCD\LCD_T6022A_RSKRL78L12_config.h"
#include "LCD\LCD_T6022A.h"


#endif