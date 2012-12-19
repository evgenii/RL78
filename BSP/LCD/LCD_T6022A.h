#ifndef __LCD_T6022A_H
#define __LCD_T6022A_H

#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"

typedef enum LCD_element {
  
  BAT_CONTOUR,
  BAT_FULL,
  BAT_75,
  BAT_50,
  BAT_25,
  BAT_EMPTY,
  PM_HOUR,
  AM_HOUR,
  C_TEMP,
  F_TEMP,
  VALUE_DOT,
  VALUE_PLUS,
  VALUE_MINUS, 
  RENLOGO,
  VOLT,
  HEART,
  HOUR_COL,
  HOUR_DOT,
  HEAT,
  COOL,
  FAN,
  ZONE,
  MG_ML,
  MM_HG,      
  ALARM,
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,  
  BAR1,       
  BAR2,       
  BAR3,       
  BAR4,       
  BAR5,      
  BAR6,       
  NUM_LCD_ELEMENTS
 
} LCD_element;

typedef enum LCD_digit {
  
  ZERO = 0,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  NUM_LCD_DIGITS
  
} LCD_digit;

typedef enum LCD_glyph_num {
  
  gZERO = 0,
  gONE,gTWO,gTHREE,gFOUR,gFIVE,gSIX,gSEVEN,gEIGHT,gNINE,
  gA,gB,gC,gD,gE,gF,gG,gH,gI,gL,gM,gN,gO,gP,gQ,gR,gS,gT,gU,gV,gW,gX,gY,gZ,gSTAR,gDOLLAR,
  NUM_LCD_GLYPH
  
} LCD_glyph_num;

typedef enum LCD_glyph_letter {
  
  gA = 65,
  gB,gC,gD,gE,gF,gG,gH,gI,gL,gM,gN,gO,gP,gQ,gR,gS,gT,gU,gV,gW,gX,gY,gZ,
  gSTAR = 42,
  gDOLLAR = 36,
  NUM_LCD_GLYPH
  
} LCD_glyph_letter;

typedef enum LCD_sign {

  PLUS = 0,
  MINUS = 1

} LCD_sign;


typedef unsigned char LCD_integerVal;
typedef unsigned char LCD_fractionalVal;


void LCD_initDisplay(void);

void LCD_set(const LCD_element element);
void LCD_clear(const LCD_element element);

void LCD_switchTemp(const LCD_element element);
void LCD_switchTemp(const LCD_element element);

void LCD_displayValue(const LCD_sign sign, const LCD_integerVal integerValue, const LCD_fractionalVal fractionalValue);

#define LCD_displayTemp LCD_displayValue
#define LCD_displayVolt LCD_displayValue


void LCD_displayTime(rtc_counter_value_t const * time);
void LCD_blinkHourColumn(void);


/* not all digits can be supported due to hw layout, currently not implemented */
void LCD_displayCount(const LCD_integerVal integerValue);

/* test function, not needed for production code */
void LCD_selfTest(void);

#endif

