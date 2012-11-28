#ifndef __BSP_TYPES_H
#define __BSP_TYPES_H


/* generic includes */
#include "ior5f10rlc.h"
#include "ior5f10rlc_ext.h"
#include "intrinsics.h"

#if defined ( __IAR_SYSTEMS_ICC__ )    /*!< IAR Compiler. Only avaiable in High optimization mode! */

  #define __STATICINLINE(foo)   static inline foo
  #define __WEAKFUNC(foo)       __weak foo
  #define __INLINE(foo)         inline foo

#endif



#endif