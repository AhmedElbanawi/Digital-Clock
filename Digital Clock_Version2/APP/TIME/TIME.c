/******************************************************************************/
#ifndef TIME_H
#include "TIME.h"
#endif
/******************************************************************************/
#ifndef SSD_H
#include "SSD.h"
#endif
/******************************************************************************/
#ifndef SW_H
#include "SW.h"
#endif
/******************************************************************************/
#define MAX_HOURS 23
#define MIN_HOURS 0
#define MAX_MINUTES 59
#define MIN_MINUTES 0
#define MAX_SECONDS 59
#define MIN_SECONDS 0
#define PERIOD_1_SEC 50
/******************************************************************************/
typedef struct{
        u8_t Hours, Minutes, Seconds;
}TIME_t;
/******************************************************************************/
static TIME_t TIME_Clk = { 0, 0, 0 };
/******************************************************************************/
static void Auto_Update(void);
static void Manual_Update(void);
/******************************************************************************/
void TIME_Update(void){
     Auto_Update();
     Manual_Update();
     SSD_g[SSD_HOURS_TENS].Symbol = TIME_Clk.Hours / 10;
     SSD_g[SSD_HOURS_UNITS].Symbol = TIME_Clk.Hours % 10;
     SSD_g[SSD_MINUTES_TENS].Symbol = TIME_Clk.Minutes / 10;
     SSD_g[SSD_MINUTES_UNITS].Symbol = TIME_Clk.Minutes % 10;
     SSD_g[SSD_SECONDS_TENS].Symbol = TIME_Clk.Seconds / 10;
     SSD_g[SSD_SECONDS_UNITS].Symbol = TIME_Clk.Seconds % 10;
}
/******************************************************************************/
static void Auto_Update(void){
       static u8_t Period = PERIOD_1_SEC; /* Based on Derived Tick of 20 ms */
       Period--;
       if(ENDED == Period){
          if(MAX_SECONDS == TIME_Clk.Seconds){
             TIME_Clk.Seconds = MIN_SECONDS;
             if(MAX_MINUTES == TIME_Clk.Minutes){
                TIME_Clk.Minutes = MIN_MINUTES;
                if(MAX_HOURS == TIME_Clk.Hours){
                   TIME_Clk.Hours = MIN_HOURS;
                }else{
                   TIME_Clk.Hours++;
                }
             }else{
                TIME_Clk.Minutes++;
             }
          }else{
             TIME_Clk.Seconds++;
          }
          Period = PERIOD_1_SEC;
       }
}
/******************************************************************************/
static void Manual_Update(void){
       switch(SSD_Mode_g){
              case SSD_NORMAL_MODE:
                   /* Time Updated automatically */
                   break;
              case SSD_SETTING_HOURS_MODE:
                   if(SW_STATE_ON == SW_g[SW_Up].State){
                      if(TIME_Clk.Hours < MAX_HOURS){
                         TIME_Clk.Hours++;
                      }
                   }else if(SW_STATE_ON == SW_g[SW_DOWN].State){
                      if(TIME_Clk.Hours > MIN_HOURS){
                         TIME_Clk.Hours--;
                      }
                   }
                   break;
              case SSD_SETTING_MINUTES_MODE:
                   if(SW_STATE_ON == SW_g[SW_Up].State){
                        if(TIME_Clk.Minutes < MAX_MINUTES){
                           TIME_Clk.Minutes++;
                        }
                     }else if(SW_STATE_ON == SW_g[SW_DOWN].State){
                        if(TIME_Clk.Minutes > MIN_MINUTES){
                           TIME_Clk.Minutes--;
                        }
                     }
                     break;
              default:
                   /* Error: Undefined TIME_MODE */
                   break;
       }
}
/******************************************************************************/
void TIME_Init(void){
     SSD_g[SSD_HOURS_TENS].Symbol = TIME_Clk.Hours / 10;
     SSD_g[SSD_HOURS_UNITS].Symbol = TIME_Clk.Hours % 10;
     SSD_g[SSD_MINUTES_TENS].Symbol = TIME_Clk.Minutes / 10;
     SSD_g[SSD_MINUTES_UNITS].Symbol = TIME_Clk.Minutes % 10;
     SSD_g[SSD_SECONDS_TENS].Symbol = TIME_Clk.Seconds / 10;
     SSD_g[SSD_SECONDS_UNITS].Symbol = TIME_Clk.Seconds % 10;
}
/******************************************************************************/