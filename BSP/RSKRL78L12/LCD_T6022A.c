#include "BSP_RSKRL78L12.h"

#include "stdlib.h"

/* macro to define the position and the mask for the bitfields */
#define LCD_BIT_FUNC(name,pos,width)    \
    enum { \
        name##_Pos = pos, \
        name##_Msk = (int)(((1ul << width) - 1) << pos) \
    }



/* Battery contour, PM, Celsius, Fahrenheit */
#define LCD_BATL5_PM_C_F  (SEG16)      
LCD_BIT_FUNC(F_TEMP, 3, 1);
LCD_BIT_FUNC(C_TEMP, 2, 1);
LCD_BIT_FUNC(PM_HOUR, 1, 1);
LCD_BIT_FUNC(BATL5, 0, 1);
static unsigned int batL5_pm_c_f = 0;

/* BATTERY LEVEL 1-4 */
#define LCD_BATL4_3_2_1   (SEG19)     /* Battery level 4 to 1 */
#define LCD_BATL4         (0x08)      /* 25 % battery */ 
#define LCD_BATL3         (0x0C)      /* 50 % battery */ 
#define LCD_BATL2         (0x0E)      /* 75 % battery */ 
#define LCD_BATL1         (0x0F)      /* Full battery */ 
static unsigned int batL4_l3_l2_l1 = 0;

/* Value sign, decade value */
#define LCD_SIGN_TEN_VAL_EFG    (SEG10)    
LCD_BIT_FUNC(SIGN_VAL, 3, 1);
LCD_BIT_FUNC(TEN_VAL_EFG, 0, 3);
static unsigned char sign_tenValEfg = 0;

#define LCD_TEN_VAL_ABCD        (SEG11)    
LCD_BIT_FUNC(TEN_VAL_ABCD, 0, 4);
volatile static unsigned char tenValAbcd = 0;

/* Renesas logo, unit value */
#define LCD_RENLOGO_UNIT_VAL_EFG   (SEG12)    
LCD_BIT_FUNC(RENLOGO, 3, 1);
LCD_BIT_FUNC(UNIT_VAL_EFG, 0, 3);
volatile static unsigned char logo_unitValEfg = 0;

#define LCD_UNIT_VAL_ABCD          (SEG13)    
LCD_BIT_FUNC(UNIT_VAL_ABCD, 0, 4);
volatile static unsigned char unitValAbcd = 0;

/* Value dot, fractional value digit */ 
#define LCD_DOT_FRAC_VAL_EFG     (SEG14)    
LCD_BIT_FUNC(DOT_VAL, 3, 1);
LCD_BIT_FUNC(FRAC_VAL_EFG, 0, 3);
volatile static unsigned char dot_fracValEfg = 0;

#define LCD_FRAC_VAL_ABCD        (SEG15)    
LCD_BIT_FUNC(FRAC_VAL_ABCD, 0, 4);
volatile static unsigned char fracValAbcd = 0;

/* Volts indicator, counter bit 6 (FGE) */
#define LCD_VOLT_COUNT6_FGE         (SEG35)    
LCD_BIT_FUNC(VOLT, 0, 1);
static unsigned char volt_count6_fge = 0;

/* Heartbeat indicator, counter bit 6 (BKC) */
#define LCD_HEART_COUNT6_BKC        (SEG34)    
LCD_BIT_FUNC(HEART, 0, 1);
static unsigned char heart_count6_bkc = 0;

/* Unit count HIND */
#define LCD_COUNT6_HIND    (SEG8)    
LCD_BIT_FUNC(COUNT6_HIND, 0, 4);
static volatile unsigned char count6_hind = 0;

/* Unit count AJML */
#define LCD_COUNT6_AJML    (SEG9)   
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
#define LCD_UNIT_MIN_EFG_THU     (SEG22)    
LCD_BIT_FUNC(THU, 0, 1);
LCD_BIT_FUNC(UNIT_MIN_EFG, 1, 3);
static unsigned char unitMinEfg_thu = 0;

/* Minute unit ABCD */
#define LCD_UNIT_MIN_ABCD         (SEG21)    
LCD_BIT_FUNC(UNIT_MIN_ABCD, 0, 4);
volatile static unsigned char unitMinAbcd = 0;

#define UNIT_MIN_ABCD_INVALID     (0x0)
#define UNIT_MIN_EFG_INVALID      (0x4)


/* Minute tens EFG, wednesday */
#define LCD_TEN_MIN_EFG_WED     (SEG24)    
LCD_BIT_FUNC(WED, 0, 1);
LCD_BIT_FUNC(TEN_MIN_EFG, 1, 3);
volatile static unsigned char tenMinEfg_wed = 0;

/* Minute tens ABCD */
#define LCD_TEN_MIN_ABCD         (SEG23)    
LCD_BIT_FUNC(TEN_MIN_ABCD, 0, 4);
volatile static unsigned char tenMinAbcd = 0;

#define TEN_MIN_ABCD_INVALID     (0x0)
#define TEN_MIN_EFG_INVALID      (0x4)


/* Hour unit EFG, sunday */
#define LCD_UNIT_HOUR_EFG_SUN     (SEG27)    
LCD_BIT_FUNC(SUN, 0, 1);
LCD_BIT_FUNC(UNIT_HOUR_EFG, 1, 3);
volatile static unsigned char unitHourEfg_sun = 0;

/* Hour unit ABCD */
#define LCD_UNIT_HOUR_ABCD         (SEG26)    
LCD_BIT_FUNC(UNIT_HOUR_ABCD, 0, 4);
volatile static unsigned char unitHourAbcd = 0;

#define UNIT_HOUR_ABCD_INVALID  (0x0)
#define UNIT_HOUR_EFG_INVALID   (0x4)

/* Hour tens EFG, heat */
#define LCD_TEN_HOUR_EFG_HEAT     (SEG31)    
LCD_BIT_FUNC(HEAT, 0, 1);
LCD_BIT_FUNC(TEN_HOUR_EFG, 1, 3);
volatile static unsigned char tenHourEfg_heat = 0;

/* Hour tens ABCD */
#define LCD_TEN_HOUR_ABCD         (SEG28)    
LCD_BIT_FUNC(TEN_HOUR_ABCD, 0, 4);
volatile static unsigned char tenHourAbcd = 0;

#define TEN_HOUR_ABCD_INVALID   (0x0)
#define TEN_HOUR_EFG_INVALID    (0x4)

/* Hour colon, hour dot, tuesday, monday */
#define LCD_HOURCOL_HOURDOT_TUE_MON    (SEG25)    
LCD_BIT_FUNC(HOURDOT, 0, 1);
LCD_BIT_FUNC(HOURCOL, 1, 1);
LCD_BIT_FUNC(TUE, 2, 1);
LCD_BIT_FUNC(MON, 3, 1);
volatile static unsigned char hourCol_hourDot_tue_mon = 0;


/* Cool, hour hundreds EFG */
#define LCD_COOL_HUND_HOUR_EFG    (SEG33)    
LCD_BIT_FUNC(COOL, 0, 1);
LCD_BIT_FUNC(HUND_HOUR_EFG, 1, 3);
static volatile unsigned char cool_hundHourEfg = 0;

/* Fan, ten count FGE */
#define LCD_FAN_COUNT5_FGE    (SEG37)    
LCD_BIT_FUNC(FAN, 0, 1);
LCD_BIT_FUNC(COUNT5_FGE, 1, 3);
static volatile unsigned char fan_count5_fge = 0;

/* Zone, ten count BKC */
#define LCD_ZONE_COUNT5_BKC    (SEG36)    
LCD_BIT_FUNC(ZONE, 0, 1);
LCD_BIT_FUNC(COUNT5_BKC, 1, 3);
static volatile unsigned char zone_count5_bkc = 0;

/* Ten count AJML */
#define LCD_COUNT5_AJML    (SEG7)   
LCD_BIT_FUNC(COUNT5_AJML, 0, 4);
static volatile unsigned char count5_ajml = 0;

/* Ten count HIND */
#define LCD_COUNT5_HIND    (SEG6)   
LCD_BIT_FUNC(COUNT5_HIND, 0, 4);
static volatile unsigned char count5_hind = 0;


/* Mg-Ml, hundred count BKC */
/* only MG-ML supported */
#define LCD_MGML_COUNT4_BKC    (SEG38)    
LCD_BIT_FUNC(MGML, 0, 1);
LCD_BIT_FUNC(COUNT4_BKC, 1, 3);
static volatile unsigned char mgml_count4_bkc = 0;

/* AM, Alarm, Sathurday, Friday */
#define LCD_AM_ALARM_SAT_FRI    (SEG20)    
LCD_BIT_FUNC(AM, 0, 1);
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
#define LCD_COUNT2_HIND    (SEG0)   
LCD_BIT_FUNC(COUNT2_HIND, 0, 4);
static volatile unsigned char count2_hind;

/* cannot be used due to other segments missing */
/* Ten thousand count AJML */
#define LCD_COUNT2_AJML    (SEG1)   
LCD_BIT_FUNC(COUNT2_AJML, 0, 4);
static volatile unsigned char count2_ajml;

/* cannot be used due to other segments missing */
/* Ten thousand count BKC, Level4 BAR */
/* J11 jumper set to TXD0 */
#define LCD_BAR4_COUNT2_BKC    (SEG30)   
LCD_BIT_FUNC(BAR4, 0, 1);
LCD_BIT_FUNC(COUNT2_BKC, 1, 3);
static volatile unsigned char bar4_count2_bkc;

/* Thousand count BKC, Level6 BAR - Resistor DNF */
#define LCD_BAR6_COUNT3_BKC    (SEG18)   
LCD_BIT_FUNC(BAR6, 0, 1);
LCD_BIT_FUNC(COUNT_BKCE, 1, 3);
static volatile unsigned char bar6_count3_bkc;

/* cannot be used due to other segments missing */
/* Thousand count FGE, Level5 BAR */
/* J10 jumper set to uart RXD0 */
#define LCD_BAR5_COUNT3_FGE    (SEG29)   
LCD_BIT_FUNC(BAR5, 0, 1);
LCD_BIT_FUNC(COUNT3_FGE, 1, 3);
static volatile unsigned char bar5_count3_fge;

/* cannot be used due to other segments missing */
/* Thousand count HIND */
#define LCD_COUNT3_HIND    (SEG2)   
LCD_BIT_FUNC(COUNT_HIND, 0, 4);
static volatile unsigned char count3_hind;

/* cannot be used due to other segments missing */
/* Thousand count AJML */
#define LCD_COUNT3_AJML    (SEG3)   
LCD_BIT_FUNC(COUNT3_AJML, 0, 4);
static volatile unsigned char count3_ajml;

/* On RSK not connected by default - Resistor DNF */
/* Mm-Hg, hundred count FGE */
#define LCD_MMHG_COUNT4_FGE    (SEG17)    
LCD_BIT_FUNC(MMHG, 0, 1);
LCD_BIT_FUNC(COUNT4_FGE, 1, 3);
static volatile unsigned char mmhg_count4_fge = 0;

/* cannot be used due to other segments missing */
/* Hundred count HIND */
#define LCD_COUNT4_HIND    (SEG4)   
LCD_BIT_FUNC(COUNT4_HIND, 0, 4);
static volatile unsigned char count4_hind = 0;

/* cannot be used due to other segments missing */
/* Hundred count AJML */
#define LCD_COUNT4_AJML    (SEG5)   
LCD_BIT_FUNC(COUNT4_AJML, 0, 4);
static volatile unsigned char count4_ajml;


#endif
/******************************************************************
 * end of unsupported segments
******************************************************************/


/* used for interrupt tracking */
static __istate_t intStatus;

/* local prototypes */
static void LCD_invalidateTime(void);


static const uint8_t TEN_HOUR_EFG[NUM_LCD_DIGITS] = {
	TEN_HOUR_EFG_0,
	TEN_HOUR_EFG_1,
	TEN_HOUR_EFG_2,
	TEN_HOUR_EFG_3,
	TEN_HOUR_EFG_4,
	TEN_HOUR_EFG_5,
	TEN_HOUR_EFG_6,
	TEN_HOUR_EFG_7,
	TEN_HOUR_EFG_8,
	TEN_HOUR_EFG_9,	
};

static const uint8_t TEN_HOUR_ABCD[NUM_LCD_DIGITS] = {
	TEN_HOUR_ABCD_0,
	TEN_HOUR_ABCD_1,
	TEN_HOUR_ABCD_2,
	TEN_HOUR_ABCD_3,
	TEN_HOUR_ABCD_4,
	TEN_HOUR_ABCD_5,
	TEN_HOUR_ABCD_6,
	TEN_HOUR_ABCD_7,
	TEN_HOUR_ABCD_8,
	TEN_HOUR_ABCD_9,	
};

static const uint8_t UNIT_HOUR_EFG[NUM_LCD_DIGITS] = {
	UNIT_HOUR_EFG_0,
	UNIT_HOUR_EFG_1,
	UNIT_HOUR_EFG_2,
	UNIT_HOUR_EFG_3,
	UNIT_HOUR_EFG_4,
	UNIT_HOUR_EFG_5,
	UNIT_HOUR_EFG_6,
	UNIT_HOUR_EFG_7,
	UNIT_HOUR_EFG_8,
	UNIT_HOUR_EFG_9,	
};

static const uint8_t UNIT_HOUR_ABCD[NUM_LCD_DIGITS] = {
	UNIT_HOUR_ABCD_0,
	UNIT_HOUR_ABCD_1,
	UNIT_HOUR_ABCD_2,
	UNIT_HOUR_ABCD_3,
	UNIT_HOUR_ABCD_4,
	UNIT_HOUR_ABCD_5,
	UNIT_HOUR_ABCD_6,
	UNIT_HOUR_ABCD_7,
	UNIT_HOUR_ABCD_8,
	UNIT_HOUR_ABCD_9,	
};

static const uint8_t TEN_MIN_EFG[NUM_LCD_DIGITS] = {
	TEN_MIN_EFG_0,
	TEN_MIN_EFG_1,
	TEN_MIN_EFG_2,
	TEN_MIN_EFG_3,
	TEN_MIN_EFG_4,
	TEN_MIN_EFG_5,
	TEN_MIN_EFG_6,
	TEN_MIN_EFG_7,
	TEN_MIN_EFG_8,
	TEN_MIN_EFG_9,	
};

static const uint8_t TEN_MIN_ABCD[NUM_LCD_DIGITS] = {
	TEN_MIN_ABCD_0,
	TEN_MIN_ABCD_1,
	TEN_MIN_ABCD_2,
	TEN_MIN_ABCD_3,
	TEN_MIN_ABCD_4,
	TEN_MIN_ABCD_5,
	TEN_MIN_ABCD_6,
	TEN_MIN_ABCD_7,
	TEN_MIN_ABCD_8,
	TEN_MIN_ABCD_9,	
};

static const uint8_t UNIT_MIN_EFG[NUM_LCD_DIGITS] = {
	UNIT_MIN_EFG_0,
	UNIT_MIN_EFG_1,
	UNIT_MIN_EFG_2,
	UNIT_MIN_EFG_3,
	UNIT_MIN_EFG_4,
	UNIT_MIN_EFG_5,
	UNIT_MIN_EFG_6,
	UNIT_MIN_EFG_7,
	UNIT_MIN_EFG_8,
	UNIT_MIN_EFG_9,	
};

static const uint8_t UNIT_MIN_ABCD[NUM_LCD_DIGITS] = {
	UNIT_MIN_ABCD_0,
	UNIT_MIN_ABCD_1,
	UNIT_MIN_ABCD_2,
	UNIT_MIN_ABCD_3,
	UNIT_MIN_ABCD_4,
	UNIT_MIN_ABCD_5,
	UNIT_MIN_ABCD_6,
	UNIT_MIN_ABCD_7,
	UNIT_MIN_ABCD_8,
	UNIT_MIN_ABCD_9,	
};


/* shows a time value */
void LCD_displayTime(rtc_counter_value_t const * time) {
  
    /* minute display values */  
    unsigned char local_unitMinEfg_thu = 0;
    unsigned char local_unitMinAbcd = 0;      
    unsigned char local_tenMinEfg_wed = 0;
    unsigned char local_tenMinAbcd = 0;
    
    /* hour display values */
    unsigned char local_tenHourEfg_heat = 0;
    unsigned char local_tenHourAbcd = 0;
    unsigned char local_unitHourEfg_sun = 0;
    unsigned char local_unitHourAbcd = 0;      

    unsigned char newValue = time->hour;
    
    /* configure tenths of hours from BCD value */
    local_tenHourEfg_heat |= TEN_HOUR_EFG[(LCD_digit) newValue >> 4];
    local_tenHourAbcd |= TEN_HOUR_ABCD[(LCD_digit) newValue >> 4];
      
    /* configure units of hours from BCD value */  
    local_unitHourEfg_sun |= UNIT_HOUR_EFG[(LCD_digit) (newValue & 0xF)];
    local_unitHourAbcd |= UNIT_HOUR_ABCD[(LCD_digit) (newValue & 0xF)];
		              
    /* configure tenths of minutes from BCD value */
    newValue = time->min;
    
	local_tenMinEfg_wed |= TEN_MIN_EFG[(LCD_digit) (newValue >> 4)];
    local_tenMinAbcd |= TEN_MIN_ABCD[(LCD_digit) (newValue >> 4)];
		      
    /* configure units of minutes from BCD value */
    local_unitMinEfg_thu |= UNIT_MIN_EFG[(LCD_digit) (newValue & 0xF)];
    local_unitMinAbcd |= UNIT_MIN_ABCD[(LCD_digit) (newValue & 0xF)];
	  
      
      
    /* treat as critical section */
    intStatus = __get_interrupt_state();
    __disable_interrupt();
    
    /* preserve the other bits */
    local_tenHourEfg_heat |= (tenHourEfg_heat & ~TEN_HOUR_EFG_Msk);  
    local_unitHourEfg_sun |= (unitHourEfg_sun & ~UNIT_HOUR_EFG_Msk);
    local_tenMinEfg_wed |= (tenMinEfg_wed & ~TEN_MIN_EFG_Msk);
    local_unitMinEfg_thu |= (unitMinEfg_thu & ~UNIT_MIN_EFG_Msk);

      
    /* apply new settings */
    LCD_TEN_HOUR_EFG_HEAT = local_tenHourEfg_heat;
    LCD_TEN_HOUR_ABCD = local_tenHourAbcd;
    LCD_UNIT_HOUR_EFG_SUN = local_unitHourEfg_sun;
    LCD_UNIT_HOUR_ABCD = local_unitHourAbcd;

    LCD_TEN_MIN_EFG_WED = local_tenMinEfg_wed;
    LCD_TEN_MIN_ABCD = local_tenMinAbcd;
    LCD_UNIT_MIN_EFG_THU = local_unitMinEfg_thu;
    LCD_UNIT_MIN_ABCD = local_unitMinAbcd;
    
    
    
    /* backup new state */
    tenHourEfg_heat = local_tenHourEfg_heat;
    tenHourAbcd = local_tenHourAbcd; 
    unitHourEfg_sun = local_unitHourEfg_sun;
    unitHourAbcd = local_unitHourAbcd;    

    tenMinEfg_wed = local_tenMinEfg_wed;
    tenMinAbcd = local_tenMinAbcd;
    unitMinEfg_thu = local_unitMinEfg_thu;
    unitMinAbcd = local_unitMinAbcd;
        
    __set_interrupt_state(intStatus);  
    
}



void LCD_blinkHourColumn(void) {
  
    unsigned char local_hourCol_hourDot_tue_mon = 0;

    /* treat as critical section */
    intStatus = __get_interrupt_state();
    __disable_interrupt();

    /* if not set, set it */
    if(!(hourCol_hourDot_tue_mon & HOURCOL_Msk)) 
      local_hourCol_hourDot_tue_mon = HOURCOL_Msk;
    
    /* preserve the other bits */
    local_hourCol_hourDot_tue_mon |= (hourCol_hourDot_tue_mon & ~HOURCOL_Msk);   

    LCD_HOURCOL_HOURDOT_TUE_MON = local_hourCol_hourDot_tue_mon;
    
    hourCol_hourDot_tue_mon = local_hourCol_hourDot_tue_mon;
      
    __set_interrupt_state(intStatus);    
}



static void LCD_invalidateTime(void) {
  
    /* hour display values */
    unsigned char local_tenHourEfg_heat = TEN_HOUR_EFG_INVALID;
    unsigned char local_unitHourEfg_sun = UNIT_HOUR_EFG_INVALID;
    unsigned char local_tenMinEfg_wed = TEN_MIN_EFG_INVALID;
    unsigned char local_unitMinEfg_thu = UNIT_MIN_EFG_INVALID;
    
    local_tenHourEfg_heat |= (tenHourEfg_heat & ~TEN_HOUR_EFG_Msk);  
    local_unitHourEfg_sun |= (unitHourEfg_sun & ~UNIT_HOUR_EFG_Msk);
    local_tenMinEfg_wed |= (tenMinEfg_wed & ~TEN_MIN_EFG_Msk);
    local_unitMinEfg_thu |= (unitMinEfg_thu & ~UNIT_MIN_EFG_Msk);

    /* treat as critical section */
    intStatus = __get_interrupt_state();
    __disable_interrupt();
    
    /* apply settings */
    LCD_TEN_HOUR_EFG_HEAT = local_tenHourEfg_heat;
    LCD_TEN_HOUR_ABCD = TEN_HOUR_ABCD_INVALID;
    LCD_UNIT_HOUR_EFG_SUN = local_unitHourEfg_sun;
    LCD_UNIT_HOUR_ABCD = UNIT_HOUR_ABCD_INVALID;
    LCD_TEN_MIN_EFG_WED = local_tenMinEfg_wed;
    LCD_TEN_MIN_ABCD = TEN_MIN_ABCD_INVALID;
    LCD_UNIT_MIN_EFG_THU = local_unitMinEfg_thu;
    LCD_UNIT_MIN_ABCD = UNIT_MIN_ABCD_INVALID;

    
    /* backup new state */
    tenHourEfg_heat = local_tenHourEfg_heat;
    tenHourAbcd = TEN_HOUR_ABCD_INVALID; 
    unitHourEfg_sun = local_unitHourEfg_sun;
    unitHourAbcd = UNIT_HOUR_ABCD_INVALID;
    tenMinEfg_wed = local_tenMinEfg_wed;
    tenMinAbcd = TEN_MIN_ABCD_INVALID;
    unitMinEfg_thu = local_unitMinEfg_thu;
    unitMinAbcd = UNIT_MIN_ABCD_INVALID;
    
    __set_interrupt_state(intStatus); 
}


/* initialize the display */
void LCD_initDisplay(void) {

  LCD_set(RENLOGO);
  LCD_set(VOLT);
  LCD_set(VALUE_DOT);
  LCD_displayValue(PLUS, 0, 0); 

  LCD_set(HOUR_COL);
  LCD_invalidateTime();
}


/* set an item */
__INLINE(void LCD_set(const LCD_element element)) {
  
     intStatus = __get_interrupt_state();
    __disable_interrupt();
    
    switch(element) {
  
    case BAT_CONTOUR:
      batL5_pm_c_f |= BATL5_Msk;
      LCD_BATL5_PM_C_F = batL5_pm_c_f;
      break;
      
    case BAT_FULL:
      batL4_l3_l2_l1 = LCD_BATL1;
      LCD_BATL4_3_2_1 = batL4_l3_l2_l1;      
      break;
      
    case BAT_75:
      batL4_l3_l2_l1 = LCD_BATL2;
      LCD_BATL4_3_2_1 = batL4_l3_l2_l1;      
      break;
      
    case BAT_50:
      batL4_l3_l2_l1 = LCD_BATL3;
      LCD_BATL4_3_2_1 = batL4_l3_l2_l1;      
      break;
      
    case BAT_25:
      batL4_l3_l2_l1 = LCD_BATL4;
      LCD_BATL4_3_2_1 = batL4_l3_l2_l1;      
      break;
      
    case BAT_EMPTY:
      batL4_l3_l2_l1 =0x0;
      LCD_BATL4_3_2_1 = batL4_l3_l2_l1;   
      break;
      
    case PM_HOUR:
      batL5_pm_c_f |= PM_HOUR_Msk;  
      LCD_BATL5_PM_C_F = batL5_pm_c_f;
      break;
      
    case C_TEMP:
      batL5_pm_c_f |= C_TEMP_Msk;  
      LCD_BATL5_PM_C_F = batL5_pm_c_f;
      break;
      
    case F_TEMP:
      batL5_pm_c_f |= F_TEMP_Msk;  
      LCD_BATL5_PM_C_F = batL5_pm_c_f;
      break;

    case VALUE_DOT:
      dot_fracValEfg |= DOT_VAL_Msk;  
      LCD_DOT_FRAC_VAL_EFG = dot_fracValEfg;      
      break;
      
    case VALUE_PLUS:
      sign_tenValEfg &= ~SIGN_VAL_Msk;
      LCD_SIGN_TEN_VAL_EFG = sign_tenValEfg;
      break;
    
    case VALUE_MINUS:
      sign_tenValEfg |= SIGN_VAL_Msk;
      LCD_SIGN_TEN_VAL_EFG = sign_tenValEfg;      
      break;
      
    case RENLOGO:
      logo_unitValEfg |= RENLOGO_Msk;  
      LCD_RENLOGO_UNIT_VAL_EFG = logo_unitValEfg;
      break;
      
    case VOLT:
      volt_count6_fge |= VOLT_Msk;
      LCD_VOLT_COUNT6_FGE = volt_count6_fge;
      break;
      
    case HEART:
      heart_count6_bkc |= HEART_Msk;
      LCD_HEART_COUNT6_BKC = heart_count6_bkc;
      break;

    case HOUR_COL:
      hourCol_hourDot_tue_mon |= HOURCOL_Msk;
      LCD_HOURCOL_HOURDOT_TUE_MON = hourCol_hourDot_tue_mon;     
      break;
      
    case HOUR_DOT:
      hourCol_hourDot_tue_mon |= HOURDOT_Msk;
      LCD_HOURCOL_HOURDOT_TUE_MON = hourCol_hourDot_tue_mon;
      break;

    case HEAT:
      tenHourEfg_heat |= HEAT_Msk;
      LCD_TEN_HOUR_EFG_HEAT = tenHourEfg_heat;
      break;
        
    case COOL:
      cool_hundHourEfg |= COOL_Msk;
      LCD_COOL_HUND_HOUR_EFG = cool_hundHourEfg;
      break;
      
    case FAN:
      fan_count5_fge |= FAN_Msk;
      LCD_FAN_COUNT5_FGE = fan_count5_fge;
      break;
        
    case ZONE:
      zone_count5_bkc |= ZONE_Msk;
      LCD_ZONE_COUNT5_BKC = zone_count5_bkc;
      break;
        
    case MG_ML:
      mgml_count4_bkc |= MGML_Msk;     
      LCD_MGML_COUNT4_BKC = mgml_count4_bkc;
      break;

    case MM_HG:
			/* unsupported */
      break;
      
    case ALARM:
      am_alarm_sat_fri |= ALARM_Msk;
      LCD_AM_ALARM_SAT_FRI = am_alarm_sat_fri;
      break;
      
    case SUNDAY:
      unitHourEfg_sun |= SUN_Msk;
      LCD_UNIT_HOUR_EFG_SUN = unitHourEfg_sun;      
      break;

    case MONDAY:
      hourCol_hourDot_tue_mon |= MON_Msk;
      LCD_HOURCOL_HOURDOT_TUE_MON =  hourCol_hourDot_tue_mon;    
      break;

    case TUESDAY:    
      hourCol_hourDot_tue_mon |= TUE_Msk;
      LCD_HOURCOL_HOURDOT_TUE_MON = hourCol_hourDot_tue_mon;
      break;
      
    case WEDNESDAY:   
      tenMinEfg_wed |= WED_Msk;
      LCD_TEN_MIN_EFG_WED = tenMinEfg_wed;
      break;
      
    case THURSDAY:
      unitMinEfg_thu |= THU_Msk;
      LCD_UNIT_MIN_EFG_THU = unitMinEfg_thu;
      break;
      
    case FRIDAY:    
      am_alarm_sat_fri |= FRI_Msk;
      LCD_AM_ALARM_SAT_FRI = am_alarm_sat_fri;
      break;

    case SATURDAY:
       am_alarm_sat_fri |= SAT_Msk;
       LCD_AM_ALARM_SAT_FRI = am_alarm_sat_fri; 
      break;

    case BAR1:
			/* unsupported */
      break;
      
    case BAR2:
			/* unsupported */
      break;
      
    case BAR3:
			/* unsupported */
      break;
      
    case BAR4:
			/* unsupported */
      break;
      
    case BAR5:
			/* unsupported */
      break;
      
    case BAR6:
			/* unsupported */
      break;

    default:
      break; 

    };
    
   __set_interrupt_state(intStatus);     
   
}

/* clear an item from the screen */
__INLINE(void LCD_clear(const LCD_element element)) {
  
    intStatus = __get_interrupt_state();
    __disable_interrupt();
    
    switch(element) {
  
    case BAT_CONTOUR:
       batL5_pm_c_f &= ~BATL5_Msk;
       LCD_BATL5_PM_C_F = batL5_pm_c_f;       
      break;
            
    case PM_HOUR:
      batL5_pm_c_f &= ~PM_HOUR_Msk;  
      LCD_BATL5_PM_C_F = batL5_pm_c_f;
      break;
      
    case C_TEMP:
      batL5_pm_c_f &= ~C_TEMP_Msk;
      LCD_BATL5_PM_C_F = batL5_pm_c_f;             
      break;
      
    case F_TEMP:
      batL5_pm_c_f &= ~F_TEMP_Msk;
      LCD_BATL5_PM_C_F = batL5_pm_c_f;       
      break;
      
    case VALUE_DOT:
      dot_fracValEfg &= ~DOT_VAL_Msk;  
      LCD_DOT_FRAC_VAL_EFG = dot_fracValEfg;      
      break;

    case RENLOGO:  
      logo_unitValEfg &= ~RENLOGO_Msk;  
      LCD_RENLOGO_UNIT_VAL_EFG = logo_unitValEfg;
      break;

    case VOLT:
      volt_count6_fge &= ~VOLT_Msk;
      LCD_VOLT_COUNT6_FGE = volt_count6_fge;
 			break;
			
    case HEART:
      heart_count6_bkc &= ~HEART_Msk;
      LCD_HEART_COUNT6_BKC = heart_count6_bkc;
			break;
			
    case HOUR_COL:
      hourCol_hourDot_tue_mon &= ~HOURCOL_Msk;
      LCD_HOURCOL_HOURDOT_TUE_MON = hourCol_hourDot_tue_mon;     
      break;
      
    case HOUR_DOT:
      hourCol_hourDot_tue_mon &= ~HOURDOT_Msk;
      LCD_HOURCOL_HOURDOT_TUE_MON = hourCol_hourDot_tue_mon;
      break;
      
    case HEAT:
      tenHourEfg_heat &= ~HEAT_Msk;
      LCD_TEN_HOUR_EFG_HEAT = tenHourEfg_heat;
      break;
        
    case COOL:
      cool_hundHourEfg &= ~COOL_Msk;
      LCD_COOL_HUND_HOUR_EFG = cool_hundHourEfg;
      break;
      
    case FAN:
      fan_count5_fge &= ~FAN_Msk;
      LCD_FAN_COUNT5_FGE = fan_count5_fge;
      break;
        
    case ZONE:
      zone_count5_bkc &= ~ZONE_Msk;
      LCD_ZONE_COUNT5_BKC = zone_count5_bkc;
      break;
        
    case MG_ML:
      mgml_count4_bkc &= ~MGML_Msk;     
      LCD_MGML_COUNT4_BKC = mgml_count4_bkc;
      break;

    case MM_HG:
			/* unsupported */
      break;
      
    case ALARM:
      am_alarm_sat_fri &= ~ALARM_Msk;
      LCD_AM_ALARM_SAT_FRI = am_alarm_sat_fri;
      break;
      
    case SUNDAY:
      unitHourEfg_sun &= ~SUN_Msk;
      LCD_UNIT_HOUR_EFG_SUN = unitHourEfg_sun;      
      break;

    case MONDAY:
      hourCol_hourDot_tue_mon &= ~MON_Msk;
      LCD_HOURCOL_HOURDOT_TUE_MON =  hourCol_hourDot_tue_mon;    
      break;

    case TUESDAY:    
      hourCol_hourDot_tue_mon &= ~TUE_Msk;
      LCD_HOURCOL_HOURDOT_TUE_MON = hourCol_hourDot_tue_mon;
      break;
      
    case WEDNESDAY:   
      tenMinEfg_wed &= ~WED_Msk;
      LCD_TEN_MIN_EFG_WED = tenMinEfg_wed;
      break;
      
    case THURSDAY:
      unitMinEfg_thu &= ~THU_Msk;
      LCD_UNIT_MIN_EFG_THU = unitMinEfg_thu;
      break;
      
    case FRIDAY:    
      am_alarm_sat_fri &= ~FRI_Msk;
      LCD_AM_ALARM_SAT_FRI = am_alarm_sat_fri;
      break;

    case SATURDAY:
       am_alarm_sat_fri &= ~SAT_Msk;
       LCD_AM_ALARM_SAT_FRI = am_alarm_sat_fri; 
      break;

    case BAR1:
			/* unsupported */
      break;
      
    case BAR2:
			/* unsupported */
      break;
      
    case BAR3:
			/* unsupported */
      break;
      
    case BAR4:
			/* unsupported */
      break;
      
    case BAR5:
			/* unsupported */
      break;
      
    case BAR6:
			/* unsupported */
      break;
      
    default:
      /* unconfigured or unsupported */
      break;
       
  };

  __set_interrupt_state(intStatus);  
}

/* function to change between celsius and fahrenheit */
__INLINE(void LCD_switchTemp(const LCD_element element)) {
  
    intStatus = __get_interrupt_state();
    __disable_interrupt();
    
    switch(element) {
  
    case C_TEMP:
      batL5_pm_c_f &= ~F_TEMP_Msk;  
      batL5_pm_c_f |= C_TEMP_Msk;
      LCD_BATL5_PM_C_F = batL5_pm_c_f;
      break;
            
    case F_TEMP:
      batL5_pm_c_f &= ~C_TEMP_Msk;  
      batL5_pm_c_f |= F_TEMP_Msk;
      LCD_BATL5_PM_C_F = batL5_pm_c_f;
      break;
      
    default:
      break;
   
    
  };

  __set_interrupt_state(intStatus);  
}





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


static const uint8_t TEN_VAL_EFG[NUM_LCD_DIGITS] = {
	(~TEN_VAL_EFG_Msk),
	TEN_VAL_EFG_1,
	TEN_VAL_EFG_2,
	TEN_VAL_EFG_3,
	TEN_VAL_EFG_4,
	TEN_VAL_EFG_5,
	TEN_VAL_EFG_6,
	TEN_VAL_EFG_7,
	TEN_VAL_EFG_8,
	TEN_VAL_EFG_9,	
};

static const uint8_t TEN_VAL_ABCD[NUM_LCD_DIGITS] = {
	(~TEN_VAL_ABCD_Msk),
	TEN_VAL_ABCD_1,
	TEN_VAL_ABCD_2,
	TEN_VAL_ABCD_3,
	TEN_VAL_ABCD_4,
	TEN_VAL_ABCD_5,
	TEN_VAL_ABCD_6,
	TEN_VAL_ABCD_7,
	TEN_VAL_ABCD_8,
	TEN_VAL_ABCD_9,	
};

static const uint8_t UNIT_VAL_EFG[NUM_LCD_DIGITS] = {
	UNIT_VAL_EFG_0,
	UNIT_VAL_EFG_1,
	UNIT_VAL_EFG_2,
	UNIT_VAL_EFG_3,
	UNIT_VAL_EFG_4,
	UNIT_VAL_EFG_5,
	UNIT_VAL_EFG_6,
	UNIT_VAL_EFG_7,
	UNIT_VAL_EFG_8,
	UNIT_VAL_EFG_9,	
};

static const uint8_t UNIT_VAL_ABCD[NUM_LCD_DIGITS] = {
	UNIT_VAL_ABCD_0,
	UNIT_VAL_ABCD_1,
	UNIT_VAL_ABCD_2,
	UNIT_VAL_ABCD_3,
	UNIT_VAL_ABCD_4,
	UNIT_VAL_ABCD_5,
	UNIT_VAL_ABCD_6,
	UNIT_VAL_ABCD_7,
	UNIT_VAL_ABCD_8,
	UNIT_VAL_ABCD_9,	
};

static const uint8_t FRAC_VAL_EFG[NUM_LCD_DIGITS] = {
	FRAC_VAL_EFG_0,
	FRAC_VAL_EFG_1,
	FRAC_VAL_EFG_2,
	FRAC_VAL_EFG_3,
	FRAC_VAL_EFG_4,
	FRAC_VAL_EFG_5,
	FRAC_VAL_EFG_6,
	FRAC_VAL_EFG_7,
	FRAC_VAL_EFG_8,
	FRAC_VAL_EFG_9,	
};

static const uint8_t FRAC_VAL_ABCD[NUM_LCD_DIGITS] = {
	FRAC_VAL_ABCD_0,
	FRAC_VAL_ABCD_1,
	FRAC_VAL_ABCD_2,
	FRAC_VAL_ABCD_3,
	FRAC_VAL_ABCD_4,
	FRAC_VAL_ABCD_5,
	FRAC_VAL_ABCD_6,
	FRAC_VAL_ABCD_7,
	FRAC_VAL_ABCD_8,
	FRAC_VAL_ABCD_9,	
};


__INLINE(void LCD_displayValue(const LCD_sign sign, const LCD_integerVal integerValue, const LCD_fractionalVal fractionalValue)) {

    unsigned char local_logo_unitValEfg= 0;
    unsigned char local_unitValAbcd = 0;    

    unsigned char local_sign_tenValEfg= 0;
    unsigned char local_tenValAbcd = 0;    

    unsigned char local_dot_fracValEfg= 0;
    unsigned char local_fracValAbcd = 0;    

    div_t newValue = div(integerValue, 10);
    
    /* display only valid ranges */
    if((newValue.quot < 100) && (fractionalValue < 10)) {
      
      
	  if(ZERO == (LCD_digit) newValue.quot) {
	    // do not display a zero upfront on the decade value
        // mask out
        local_sign_tenValEfg &= TEN_VAL_EFG[ZERO];
        local_tenValAbcd &= TEN_VAL_ABCD[ZERO];	  
	  }
	  else {
        local_sign_tenValEfg |= TEN_VAL_EFG[(LCD_digit) newValue.quot];
        local_tenValAbcd |= TEN_VAL_ABCD[(LCD_digit) newValue.quot]; 		
	  };   
	  
      local_logo_unitValEfg |= UNIT_VAL_EFG[(LCD_digit) newValue.rem];
      local_unitValAbcd |= UNIT_VAL_ABCD[(LCD_digit) newValue.rem]; 
      
      local_dot_fracValEfg |= FRAC_VAL_EFG[(LCD_digit) fractionalValue];
      local_fracValAbcd |= FRAC_VAL_ABCD[(LCD_digit) fractionalValue];   

      
    }
    else {

        local_sign_tenValEfg |= SIGN_TEN_VAL_EFG_INVALID;
        local_tenValAbcd |= TEN_VAL_ABCD_INVALID; 
        local_logo_unitValEfg |= RENLOGO_UNIT_VAL_EFG_INVALID;
        local_unitValAbcd |= UNIT_VAL_ABCD_INVALID;      
        local_dot_fracValEfg |= DOT_FRAC_VAL_EFG_INVALID;
        local_fracValAbcd |= FRAC_VAL_ABCD_INVALID;      
    };
    
    if(MINUS == sign) { local_sign_tenValEfg |= SIGN_VAL_Msk;  }
    else { local_sign_tenValEfg &= ~SIGN_VAL_Msk;}
    
    /* treat as critical section */
    intStatus = __get_interrupt_state();
    __disable_interrupt();
    
    /* preserve the other bits */
    local_logo_unitValEfg |= (logo_unitValEfg & ~UNIT_VAL_EFG_Msk);  
    local_dot_fracValEfg |= (dot_fracValEfg & ~FRAC_VAL_EFG_Msk);
    
    /* apply new settings */
    LCD_SIGN_TEN_VAL_EFG = local_sign_tenValEfg;
    LCD_TEN_VAL_ABCD = local_tenValAbcd;
    LCD_RENLOGO_UNIT_VAL_EFG = local_logo_unitValEfg;
    LCD_UNIT_VAL_ABCD = local_unitValAbcd;
    LCD_DOT_FRAC_VAL_EFG = local_dot_fracValEfg;
    LCD_FRAC_VAL_ABCD = local_fracValAbcd;
    
    /* backup new state */
    logo_unitValEfg = local_logo_unitValEfg;
    unitValAbcd = local_unitValAbcd; 
    sign_tenValEfg = local_sign_tenValEfg;
    tenValAbcd = local_tenValAbcd;
    dot_fracValEfg = local_dot_fracValEfg;
    fracValAbcd = local_fracValAbcd;
    
    __set_interrupt_state(intStatus);  
}


/* only two digits supported on the display */
/* TODO - perhaps add support for the two unit displays */
/* limited visualization since due to hw layout it is not completely connected */
void LCD_displayCount(const LCD_integerVal integerValue) {
	
	
}


/* Self test function, list and sets all usable segments on the display */
void LCD_selfTest(void) {
  
  unsigned int i;
  rtc_counter_value_t testTime;
  
  LCD_set(RENLOGO);
  LCD_clear(RENLOGO);

  LCD_set(HEAT);
  LCD_set(COOL);
  LCD_set(FAN);
  LCD_set(ZONE);
  LCD_set(MG_ML);
  LCD_set(ALARM);
  
  LCD_clear(HEAT);
  LCD_clear(COOL);
  LCD_clear(FAN);
  LCD_clear(ZONE);
  LCD_clear(MG_ML);
  LCD_clear(ALARM);

  LCD_set(VOLT);
  LCD_set(HEART);
  LCD_clear(VOLT);
  LCD_clear(HEART); 

  LCD_set(HOUR_COL);      
  LCD_set(HOUR_DOT);
  LCD_clear(HOUR_COL);
  LCD_clear(HOUR_DOT);
  
  testTime.min = 0;
  testTime.hour = 0;
  LCD_displayTime(&testTime);      
  
  for(i=0;i<9;i++) {
    
    testTime.hour++;
    testTime.min++;
    LCD_displayTime(&testTime);
  }
  
  testTime.min = 0x12;
  testTime.hour = 0x15;
  LCD_displayTime(&testTime);      
  testTime.min = 0x59;
  testTime.hour = 0x23;
  LCD_displayTime(&testTime);      
  
  LCD_displayTemp(PLUS, 0, 0);  
  LCD_set(VALUE_MINUS);
  LCD_set(VALUE_DOT);
  LCD_displayTemp(PLUS, 1, 1);      
  LCD_displayTemp(PLUS, 2, 2);            
  LCD_displayTemp(MINUS, 3, 3);
  
  LCD_displayTemp(PLUS, 120, 3);
  LCD_displayTemp(PLUS, 41, 4);
  LCD_displayTemp(PLUS, 10, 40);      
  LCD_displayTemp(MINUS, 52, 5);
  LCD_displayTemp(PLUS, 63, 6);      
  LCD_displayTemp(MINUS, 74, 7);      
  LCD_displayTemp(PLUS, 85, 8);      
  LCD_displayTemp(MINUS, 99, 9);      
  LCD_displayTemp(PLUS, 1, 0);
  
  LCD_set(PM_HOUR);
  LCD_set(AM_HOUR);	
  LCD_set(F_TEMP);   
  LCD_set(C_TEMP);         

  LCD_clear(PM_HOUR);            
  LCD_clear(AM_HOUR);	
  LCD_clear(F_TEMP);         
  LCD_clear(C_TEMP);               
    
  LCD_switchTemp(C_TEMP); 
  LCD_switchTemp(F_TEMP);
  
  LCD_set(BAT_CONTOUR);
  LCD_set(BAT_FULL);
  LCD_set(BAT_75);
  LCD_set(BAT_50);
  LCD_set(BAT_25);
  LCD_set(BAT_EMPTY);  
  LCD_clear(BAT_CONTOUR);
	
  LCD_set(SUNDAY);  	
  LCD_set(MONDAY);  	
  LCD_set(TUESDAY);  	
  LCD_set(WEDNESDAY);  	
  LCD_set(THURSDAY);  	
  LCD_set(FRIDAY);  	
  LCD_set(SATURDAY); 
 	
  LCD_clear(SUNDAY);  	
  LCD_clear(MONDAY);  	
  LCD_clear(TUESDAY);  	
  LCD_clear(WEDNESDAY);  	
  LCD_clear(THURSDAY);  	
  LCD_clear(FRIDAY);  	
  LCD_clear(SATURDAY);   
}


