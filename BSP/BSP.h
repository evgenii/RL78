#ifndef __BSP_H
#define __BSP_H

/* DO NOT EDIT THESE DEFINITIONS */
/* define the supported platforms */
#define RSKRL78L12  (1)
#define RPBRL78L12  (2)
/* end of supported platform list */


/*
* User setup: choose the platform to build against 
*/
#define PLATFORM    RPBRL78L12









/* DO NOT EDIT THESE DEFINITIONS */
/* automatcally include relevant header */

#if (PLATFORM == RSKRL78L12)
//    #warning "Building for RL12 Starter Kit"
    #include "BSP_RSKRL78L12.h"

#elif (PLATFORM == RPBRL78L12)
//    #warning "Building for RL12 Promotion Board"
    #include "BSP_RPBRL78L12.h"
#else
    #error "Please choose a platform within header BSP.h"
#endif



#endif
