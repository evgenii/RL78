#include "BSP.h"

#include "stdlib.h"

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

  LCD_element i;
  for(i=(LCD_element)0;i<NUM_LCD_ELEMENTS;i++) 
    LCD_clear((LCD_element)i);
  
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
      
    case AM_HOUR:
      am_alarm_sat_fri |= AM_HOUR_Msk;
      LCD_AM_ALARM_SAT_FRI = am_alarm_sat_fri;
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

    case AM_HOUR:
      am_alarm_sat_fri &= ~AM_HOUR_Msk;
      LCD_AM_ALARM_SAT_FRI = am_alarm_sat_fri;
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

    case VALUE_PLUS:     /* fall though by purpose */
    case VALUE_MINUS:
      sign_tenValEfg &= ~SIGN_VAL_Msk;
      LCD_SIGN_TEN_VAL_EFG = sign_tenValEfg;      
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
    if((newValue.quot < 10) && (fractionalValue < 10)) {
      
      
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


/* Self test function, toggles all segments on the display */
extern volatile uint8_t rtcInterrupt;
void LCD_selfTest(void) {
  
  unsigned int i,j;
  rtc_counter_value_t testTime;
  
  j = 0;
  while(j<9) {
    
      if(1 == rtcInterrupt) {      
        rtcInterrupt = 0;
        
        if(j%2) {
          for(i=0;i<NUM_LCD_ELEMENTS;i++) LCD_set((LCD_element)i);
        }
        else {
          for(i=0;i<NUM_LCD_ELEMENTS;i++) LCD_clear((LCD_element)i);
        }
        
        j++;    
      } 
            
  }; 
        
  /* cycle through the displayed time */
  testTime.hour = 0;
  testTime.min = 0;
  j=0;
  while(j<10) {
    
    if(1 == rtcInterrupt) {      
        rtcInterrupt = 0;
        testTime.min = (j | (j<< 4));
        testTime.hour = (j | (j<< 4));        
        LCD_displayTime(&testTime);
        j++;
    }
  } 

  /* cycle through the displayed values */ 
  j = 0;
  while(j<10) {
    
    if(1 == rtcInterrupt) {      
        rtcInterrupt = 0;
        LCD_displayVolt(PLUS, j*10+j, j);
        j++;
    };

  } 
     

  
}


