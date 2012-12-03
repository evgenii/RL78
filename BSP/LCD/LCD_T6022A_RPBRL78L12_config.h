#ifndef __LCD_T6022A_RPBRL78L12_H
#define __LCD_T6022A_RPBRL78L12_H

#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"


/* macro to define the position and the mask for the bitfields */
#define LCD_BIT_FUNC(name,pos,width)    \
    enum { \
        name##_Pos = pos, \
        name##_Msk = (int)(((1ul << width) - 1) << pos) \
    }



/* Battery contour, PM, Celsius, Fahrenheit */
#define LCD_BATL5_PM_C_F  (SEG14)      
LCD_BIT_FUNC(F_TEMP, 3, 1);
LCD_BIT_FUNC(C_TEMP, 2, 1);
LCD_BIT_FUNC(PM_HOUR, 1, 1);
LCD_BIT_FUNC(BATL5, 0, 1);
static unsigned int batL5_pm_c_f = 0;

/* BATTERY LEVEL 1-4 */
#define LCD_BATL4_3_2_1   (SEG15)     /* Battery level 4 to 1 */
#define LCD_BATL4         (0x08)      /* 25 % battery */ 
#define LCD_BATL3         (0x0C)      /* 50 % battery */ 
#define LCD_BATL2         (0x0E)      /* 75 % battery */ 
#define LCD_BATL1         (0x0F)      /* Full battery */ 
static unsigned int batL4_l3_l2_l1 = 0;

/* Value sign, decade value */
#define LCD_SIGN_TEN_VAL_EFG    (SEG8)    
LCD_BIT_FUNC(SIGN_VAL, 3, 1);
LCD_BIT_FUNC(TEN_VAL_EFG, 0, 3);
static unsigned char sign_tenValEfg = 0;

#define LCD_TEN_VAL_ABCD        (SEG9)    
LCD_BIT_FUNC(TEN_VAL_ABCD, 0, 4);
volatile static unsigned char tenValAbcd = 0;

/* Renesas logo, unit value */
#define LCD_RENLOGO_UNIT_VAL_EFG   (SEG10)    
LCD_BIT_FUNC(RENLOGO, 3, 1);
LCD_BIT_FUNC(UNIT_VAL_EFG, 0, 3);
volatile static unsigned char logo_unitValEfg = 0;

#define LCD_UNIT_VAL_ABCD          (SEG11)    
LCD_BIT_FUNC(UNIT_VAL_ABCD, 0, 4);
volatile static unsigned char unitValAbcd = 0;

/* Value dot, fractional value digit */ 
#define LCD_DOT_FRAC_VAL_EFG     (SEG12)    
LCD_BIT_FUNC(DOT_VAL, 3, 1);
LCD_BIT_FUNC(FRAC_VAL_EFG, 0, 3);
volatile static unsigned char dot_fracValEfg = 0;

#define LCD_FRAC_VAL_ABCD        (SEG13)    
LCD_BIT_FUNC(FRAC_VAL_ABCD, 0, 4);
volatile static unsigned char fracValAbcd = 0;

/* Volts indicator, counter bit 6 (FGE) */
#define LCD_VOLT_COUNT6_FGE         (SEG32)    
LCD_BIT_FUNC(VOLT, 0, 1);
static unsigned char volt_count6_fge = 0;

/* Heartbeat indicator, counter bit 6 (BKC) */
#define LCD_HEART_COUNT6_BKC        (SEG31)    
LCD_BIT_FUNC(HEART, 0, 1);
static unsigned char heart_count6_bkc = 0;

/* Unit count HIND */
#define LCD_COUNT6_HIND    (SEG6)    
LCD_BIT_FUNC(COUNT6_HIND, 0, 4);
static volatile unsigned char count6_hind = 0;

/* Unit count AJML */
#define LCD_COUNT6_AJML    (SEG7)   
LCD_BIT_FUNC(COUNT6_AJML, 0, 4);
static volatile unsigned char count6_ajml = 0;


/* definition of the pattern values for the time digits */
#define UNIT_MIN_ABCD_0  (0xF)
#define UNIT_MIN_EFG_0   (0xA)
#define UNIT_MIN_ABCD_1  (0x6)
#define UNIT_MIN_EFG_1   (0x0)
#define UNIT_MIN_ABCD_2  (0xD)
#define UNIT_MIN_EFG_2   (0x6)
#define UNIT_MIN_ABCD_3  (0xF)
#define UNIT_MIN_EFG_3   (0x4)
#define UNIT_MIN_ABCD_4  (0x6)
#define UNIT_MIN_EFG_4   (0xC)
#define UNIT_MIN_ABCD_5  (0xB)
#define UNIT_MIN_EFG_5   (0xC)
#define UNIT_MIN_ABCD_6  (0xB)
#define UNIT_MIN_EFG_6   (0xE)
#define UNIT_MIN_ABCD_7  (0xE)
#define UNIT_MIN_EFG_7   (0x0)
#define UNIT_MIN_ABCD_8  (0xF)
#define UNIT_MIN_EFG_8   (0xE)
#define UNIT_MIN_ABCD_9  (0xF)
#define UNIT_MIN_EFG_9   (0xC)

#define TEN_MIN_ABCD_0  (0xF)
#define TEN_MIN_EFG_0   (0xA)
#define TEN_MIN_ABCD_1  (0x6)
#define TEN_MIN_EFG_1   (0x0)
#define TEN_MIN_ABCD_2  (0xD)
#define TEN_MIN_EFG_2   (0x6)
#define TEN_MIN_ABCD_3  (0xF)
#define TEN_MIN_EFG_3   (0x4)
#define TEN_MIN_ABCD_4  (0x6)
#define TEN_MIN_EFG_4   (0xC)
#define TEN_MIN_ABCD_5  (0xB)
#define TEN_MIN_EFG_5   (0xC)
#define TEN_MIN_ABCD_6  (0xB)
#define TEN_MIN_EFG_6   (0xE)
#define TEN_MIN_ABCD_7  (0xE)
#define TEN_MIN_EFG_7   (0x0)
#define TEN_MIN_ABCD_8  (0xF)
#define TEN_MIN_EFG_8   (0xE)
#define TEN_MIN_ABCD_9  (0xF)
#define TEN_MIN_EFG_9   (0xC)

#define UNIT_HOUR_ABCD_0  (0xF)
#define UNIT_HOUR_EFG_0   (0xA)
#define UNIT_HOUR_ABCD_1  (0x6)
#define UNIT_HOUR_EFG_1   (0x0)
#define UNIT_HOUR_ABCD_2  (0xD)
#define UNIT_HOUR_EFG_2   (0x6)
#define UNIT_HOUR_ABCD_3  (0xF)
#define UNIT_HOUR_EFG_3   (0x4)
#define UNIT_HOUR_ABCD_4  (0x6)
#define UNIT_HOUR_EFG_4   (0xC)
#define UNIT_HOUR_ABCD_5  (0xB)
#define UNIT_HOUR_EFG_5   (0xC)
#define UNIT_HOUR_ABCD_6  (0xB)
#define UNIT_HOUR_EFG_6   (0xE)
#define UNIT_HOUR_ABCD_7  (0xE)
#define UNIT_HOUR_EFG_7   (0x0)
#define UNIT_HOUR_ABCD_8  (0xF)
#define UNIT_HOUR_EFG_8   (0xE)
#define UNIT_HOUR_ABCD_9  (0xF)
#define UNIT_HOUR_EFG_9   (0xC)

#define TEN_HOUR_ABCD_0  (0xF)
#define TEN_HOUR_EFG_0   (0xA)
#define TEN_HOUR_ABCD_1  (0x6)
#define TEN_HOUR_EFG_1   (0x0)
#define TEN_HOUR_ABCD_2  (0xD)
#define TEN_HOUR_EFG_2   (0x6)
#define TEN_HOUR_ABCD_3  (0xF)
#define TEN_HOUR_EFG_3   (0x4)
#define TEN_HOUR_ABCD_4  (0x6)
#define TEN_HOUR_EFG_4   (0xC)
#define TEN_HOUR_ABCD_5  (0xB)
#define TEN_HOUR_EFG_5   (0xC)
#define TEN_HOUR_ABCD_6  (0xB)
#define TEN_HOUR_EFG_6   (0xE)
#define TEN_HOUR_ABCD_7  (0xE)
#define TEN_HOUR_EFG_7   (0x0)
#define TEN_HOUR_ABCD_8  (0xF)
#define TEN_HOUR_EFG_8   (0xE)
#define TEN_HOUR_ABCD_9  (0xF)
#define TEN_HOUR_EFG_9   (0xC)

#define UNIT_SEC_ABCD_INVALID   (0x0)
#define TEN_SEC_ABCD_INVALID    (0x0)


/* Minute unit EFG, thursday */
#define LCD_UNIT_MIN_EFG_THU     (SEG20)    
LCD_BIT_FUNC(THU, 0, 1);
LCD_BIT_FUNC(UNIT_MIN_EFG, 1, 3);
static unsigned char unitMinEfg_thu = 0;

/* Minute unit ABCD */
#define LCD_UNIT_MIN_ABCD         (SEG19)    
LCD_BIT_FUNC(UNIT_MIN_ABCD, 0, 4);
volatile static unsigned char unitMinAbcd = 0;

#define UNIT_MIN_ABCD_INVALID     (0x0)
#define UNIT_MIN_EFG_INVALID      (0x4)


/* Minute tens EFG, wednesday */
#define LCD_TEN_MIN_EFG_WED     (SEG22)    
LCD_BIT_FUNC(WED, 0, 1);
LCD_BIT_FUNC(TEN_MIN_EFG, 1, 3);
volatile static unsigned char tenMinEfg_wed = 0;

/* Minute tens ABCD */
#define LCD_TEN_MIN_ABCD         (SEG21)    
LCD_BIT_FUNC(TEN_MIN_ABCD, 0, 4);
volatile static unsigned char tenMinAbcd = 0;

#define TEN_MIN_ABCD_INVALID     (0x0)
#define TEN_MIN_EFG_INVALID      (0x4)


/* Hour unit EFG, sunday */
#define LCD_UNIT_HOUR_EFG_SUN     (SEG25)    
LCD_BIT_FUNC(SUN, 0, 1);
LCD_BIT_FUNC(UNIT_HOUR_EFG, 1, 3);
volatile static unsigned char unitHourEfg_sun = 0;

/* Hour unit ABCD */
#define LCD_UNIT_HOUR_ABCD         (SEG24)    
LCD_BIT_FUNC(UNIT_HOUR_ABCD, 0, 4);
volatile static unsigned char unitHourAbcd = 0;

#define UNIT_HOUR_ABCD_INVALID  (0x0)
#define UNIT_HOUR_EFG_INVALID   (0x4)

/* Hour tens EFG, heat */
#define LCD_TEN_HOUR_EFG_HEAT     (SEG27)    
LCD_BIT_FUNC(HEAT, 0, 1);
LCD_BIT_FUNC(TEN_HOUR_EFG, 1, 3);
volatile static unsigned char tenHourEfg_heat = 0;

/* Hour tens ABCD */
#define LCD_TEN_HOUR_ABCD         (SEG26)    
LCD_BIT_FUNC(TEN_HOUR_ABCD, 0, 4);
volatile static unsigned char tenHourAbcd = 0;

#define TEN_HOUR_ABCD_INVALID   (0x0)
#define TEN_HOUR_EFG_INVALID    (0x4)

/* Hour colon, hour dot, tuesday, monday */
#define LCD_HOURCOL_HOURDOT_TUE_MON    (SEG23)    
LCD_BIT_FUNC(HOURDOT, 0, 1);
LCD_BIT_FUNC(HOURCOL, 1, 1);
LCD_BIT_FUNC(TUE, 2, 1);
LCD_BIT_FUNC(MON, 3, 1);
volatile static unsigned char hourCol_hourDot_tue_mon = 0;


/* Cool, hour hundreds EFG */
#define LCD_COOL_HUND_HOUR_EFG    (SEG28)    
LCD_BIT_FUNC(COOL, 0, 1);
LCD_BIT_FUNC(HUND_HOUR_EFG, 1, 3);
static volatile unsigned char cool_hundHourEfg = 0;

/* Fan, ten count FGE */
#define LCD_FAN_COUNT5_FGE    (SEG34)    
LCD_BIT_FUNC(FAN, 0, 1);
LCD_BIT_FUNC(COUNT5_FGE, 1, 3);
static volatile unsigned char fan_count5_fge = 0;

/* Zone, ten count BKC */
#define LCD_ZONE_COUNT5_BKC    (SEG33)    
LCD_BIT_FUNC(ZONE, 0, 1);
LCD_BIT_FUNC(COUNT5_BKC, 1, 3);
static volatile unsigned char zone_count5_bkc = 0;

/* Ten count AJML */
#define LCD_COUNT5_AJML    (SEG5)   
LCD_BIT_FUNC(COUNT5_AJML, 0, 4);
static volatile unsigned char count5_ajml = 0;

/* Ten count HIND */
#define LCD_COUNT5_HIND    (SEG4)   
LCD_BIT_FUNC(COUNT5_HIND, 0, 4);
static volatile unsigned char count5_hind = 0;


/* Mg-Ml, hundred count BKC */
/* only MG-ML supported */
#define LCD_MGML_COUNT4_BKC    (SEG35)    
LCD_BIT_FUNC(MGML, 0, 1);
LCD_BIT_FUNC(COUNT4_BKC, 1, 3);
static volatile unsigned char mgml_count4_bkc = 0;

/* AM, Alarm, Sathurday, Friday */
#define LCD_AM_ALARM_SAT_FRI    (SEG16)    
LCD_BIT_FUNC(AM_HOUR, 0, 1);
LCD_BIT_FUNC(ALARM, 1, 1);
LCD_BIT_FUNC(SAT, 2, 1);
LCD_BIT_FUNC(FRI, 3, 1);
static volatile unsigned char am_alarm_sat_fri = 0;







/******************************************************************
 * the following segments are defined per general approach but are
 * not available on the kit due to DNF - missing segments - not 
 * routed
******************************************************************/
#if 0

/* not connected on LCD kit */
/* Hundred thousand count HIND - PIN 5 on display */
#define LCD_COUNT1_HIND    (SEGx)   
LCD_BIT_FUNC(COUNT1_HIND, 0, 4);
static volatile unsigned char count1_hind;

/* not connected on LCD kit */
/* Hundred thousand count AJML - PIN 6 on display */
#define LCD_COUNT1_AJML    (SEGx)   
LCD_BIT_FUNC(COUNT1_AJML, 0, 4);
static volatile unsigned char count1_ajml;

/* not connected on LCD kit */
/* Hundred thousand count BKC, Level2 BAR - PIN 47 on display */
#define LCD_BAR2_COUNT1_BKC    (SEGx)   
LCD_BIT_FUNC(BAR2, 0, 1);
LCD_BIT_FUNC(COUNT1_BKC, 1, 3);
static volatile unsigned char bar2_count1_bkc;

/* not connected on LCD kit */
/* Hundred thousand count FGE, Level1 BAR - PIN 48 on display */
#define LCD_BAR1_COUNT1_FGE    (SEGx)   
LCD_BIT_FUNC(BAR1, 0, 1);
LCD_BIT_FUNC(COUNT1_FGE, 1, 3);
static volatile unsigned char bar1_count1_fge;

/* Not connected on RSK board, pin 50 of header */
/* Ten thousand count FGE, Level3 BAR */
#define LCD_BAR3_COUNT2_FGE    (SEGx)   
LCD_BIT_FUNC(BAR3, 0, 1);
LCD_BIT_FUNC(COUNT2_FGE, 1, 3);
static volatile unsigned char bar3_count2_fge;

/* cannot be used due to other segments missing */
/* Ten thousand count HIND */
#define LCD_COUNT2_HIND    (SEGx)   
LCD_BIT_FUNC(COUNT2_HIND, 0, 4);
static volatile unsigned char count2_hind;

/* cannot be used due to other segments missing */
/* Ten thousand count AJML */
#define LCD_COUNT2_AJML    (SEGx)   
LCD_BIT_FUNC(COUNT2_AJML, 0, 4);
static volatile unsigned char count2_ajml;

/* cannot be used due to other segments missing */
/* Ten thousand count BKC, Level4 BAR */
/* J11 jumper set to TXD0 */
#define LCD_BAR4_COUNT2_BKC    (SEGx)   
LCD_BIT_FUNC(BAR4, 0, 1);
LCD_BIT_FUNC(COUNT2_BKC, 1, 3);
static volatile unsigned char bar4_count2_bkc;

/* Thousand count BKC, Level6 BAR - Resistor DNF */
#define LCD_BAR6_COUNT3_BKC    (SEG37)   
LCD_BIT_FUNC(BAR6, 0, 1);
LCD_BIT_FUNC(COUNT_BKCE, 1, 3);
static volatile unsigned char bar6_count3_bkc;

/* cannot be used due to other segments missing */
/* Thousand count FGE, Level5 BAR */
/* J10 jumper set to uart RXD0 */
#define LCD_BAR5_COUNT3_FGE    (SEG38)   
LCD_BIT_FUNC(BAR5, 0, 1);
LCD_BIT_FUNC(COUNT3_FGE, 1, 3);
static volatile unsigned char bar5_count3_fge;

/* cannot be used due to other segments missing */
/* Thousand count HIND */
#define LCD_COUNT3_HIND    (SEG0)   
LCD_BIT_FUNC(COUNT_HIND, 0, 4);
static volatile unsigned char count3_hind;

/* cannot be used due to other segments missing */
/* Thousand count AJML */
#define LCD_COUNT3_AJML    (SEG6)   
LCD_BIT_FUNC(COUNT3_AJML, 0, 4);
static volatile unsigned char count3_ajml;

/* On RSK not connected by default - Resistor DNF */
/* Mm-Hg, hundred count FGE */
#define LCD_MMHG_COUNT4_FGE    (SEG36)    
LCD_BIT_FUNC(MMHG, 0, 1);
LCD_BIT_FUNC(COUNT4_FGE, 1, 3);
static volatile unsigned char mmhg_count4_fge = 0;

/* cannot be used due to other segments missing */
/* Hundred count HIND */
#define LCD_COUNT4_HIND    (SEG2)   
LCD_BIT_FUNC(COUNT4_HIND, 0, 4);
static volatile unsigned char count4_hind = 0;

/* cannot be used due to other segments missing */
/* Hundred count AJML */
#define LCD_COUNT4_AJML    (SEG3)   
LCD_BIT_FUNC(COUNT4_AJML, 0, 4);
static volatile unsigned char count4_ajml;


#endif
/******************************************************************
 * end of unsupported segments
******************************************************************/

/* definition of the bit patterns for the value digits */
#define UNIT_VAL_ABCD_0  (0xF)  
#define UNIT_VAL_EFG_0   (0x5)
#define UNIT_VAL_ABCD_1  (0x6)
#define UNIT_VAL_EFG_1   (0x0)
#define UNIT_VAL_ABCD_2  (0xB)
#define UNIT_VAL_EFG_2   (0x6)
#define UNIT_VAL_ABCD_3  (0xF)
#define UNIT_VAL_EFG_3   (0x2)
#define UNIT_VAL_ABCD_4  (0x6)
#define UNIT_VAL_EFG_4   (0x3)
#define UNIT_VAL_ABCD_5  (0xD)
#define UNIT_VAL_EFG_5   (0x3)
#define UNIT_VAL_ABCD_6  (0xD)
#define UNIT_VAL_EFG_6   (0x7)
#define UNIT_VAL_ABCD_7  (0x7)
#define UNIT_VAL_EFG_7   (0x0)
#define UNIT_VAL_ABCD_8  (0xF)
#define UNIT_VAL_EFG_8   (0x7)
#define UNIT_VAL_ABCD_9  (0xF)
#define UNIT_VAL_EFG_9   (0x3)

#define TEN_VAL_ABCD_0  (UNIT_VAL_ABCD_0)
#define TEN_VAL_EFG_0   (UNIT_VAL_EFG_0)
#define TEN_VAL_ABCD_1  (UNIT_VAL_ABCD_1)
#define TEN_VAL_EFG_1   (UNIT_VAL_EFG_1)
#define TEN_VAL_ABCD_2  (UNIT_VAL_ABCD_2)
#define TEN_VAL_EFG_2   (UNIT_VAL_EFG_2)
#define TEN_VAL_ABCD_3  (UNIT_VAL_ABCD_3)
#define TEN_VAL_EFG_3   (UNIT_VAL_EFG_3)
#define TEN_VAL_ABCD_4  (UNIT_VAL_ABCD_4)
#define TEN_VAL_EFG_4   (UNIT_VAL_EFG_4)
#define TEN_VAL_ABCD_5  (UNIT_VAL_ABCD_5)
#define TEN_VAL_EFG_5   (UNIT_VAL_EFG_5)
#define TEN_VAL_ABCD_6  (UNIT_VAL_ABCD_6)
#define TEN_VAL_EFG_6   (UNIT_VAL_EFG_6)
#define TEN_VAL_ABCD_7  (UNIT_VAL_ABCD_7)
#define TEN_VAL_EFG_7   (UNIT_VAL_EFG_7)
#define TEN_VAL_ABCD_8  (UNIT_VAL_ABCD_8)
#define TEN_VAL_EFG_8   (UNIT_VAL_EFG_8)
#define TEN_VAL_ABCD_9  (UNIT_VAL_ABCD_9)
#define TEN_VAL_EFG_9   (UNIT_VAL_EFG_9)

#define FRAC_VAL_ABCD_0  (UNIT_VAL_ABCD_0)
#define FRAC_VAL_EFG_0   (UNIT_VAL_EFG_0)
#define FRAC_VAL_ABCD_1  (UNIT_VAL_ABCD_1)
#define FRAC_VAL_EFG_1   (UNIT_VAL_EFG_1)
#define FRAC_VAL_ABCD_2  (UNIT_VAL_ABCD_2)
#define FRAC_VAL_EFG_2   (UNIT_VAL_EFG_2)
#define FRAC_VAL_ABCD_3  (UNIT_VAL_ABCD_3)
#define FRAC_VAL_EFG_3   (UNIT_VAL_EFG_3)
#define FRAC_VAL_ABCD_4  (UNIT_VAL_ABCD_4)
#define FRAC_VAL_EFG_4   (UNIT_VAL_EFG_4)
#define FRAC_VAL_ABCD_5  (UNIT_VAL_ABCD_5)
#define FRAC_VAL_EFG_5   (UNIT_VAL_EFG_5)
#define FRAC_VAL_ABCD_6  (UNIT_VAL_ABCD_6)
#define FRAC_VAL_EFG_6   (UNIT_VAL_EFG_6)
#define FRAC_VAL_ABCD_7  (UNIT_VAL_ABCD_7)
#define FRAC_VAL_EFG_7   (UNIT_VAL_EFG_7)
#define FRAC_VAL_ABCD_8  (UNIT_VAL_ABCD_8)
#define FRAC_VAL_EFG_8   (UNIT_VAL_EFG_8)
#define FRAC_VAL_ABCD_9  (UNIT_VAL_ABCD_9)
#define FRAC_VAL_EFG_9   (UNIT_VAL_EFG_9)

#define TEN_VAL_ABCD_INVALID   (0x0)
#define UNIT_VAL_ABCD_INVALID  (TEN_VAL_ABCD_INVALID)
#define FRAC_VAL_ABCD_INVALID  (TEN_VAL_ABCD_INVALID)

#define SIGN_TEN_VAL_EFG_INVALID     (0x2)
#define RENLOGO_UNIT_VAL_EFG_INVALID (SIGN_TEN_VAL_EFG_INVALID)
#define DOT_FRAC_VAL_EFG_INVALID     (SIGN_TEN_VAL_EFG_INVALID)





#endif

