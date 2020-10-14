/******************************************************************************/
#ifndef SSD_H
#include "SSD.h"
#endif
/******************************************************************************/
#define ENDED 0
#define PERIODE_1_SEC 200
/******************************************************************************/
typedef enum{
        SSD_HOURS_TENS = 0,
        SSD_HOURS_ONES,
        SSD_MINUTES_TENS,
        SSD_MINUTES_ONES,
        SSD_SECONDS_TENS,
        SSD_SECONDS_ONES
}SSD_t;
typedef enum{
        SW_STATE_OFF = 0,
        SW_STATE_ON
}SW_State_t;
typedef enum{
        SSD_NORMAL_MODE = 0,
        SSD_SETTING_HOURS_MODE,
        SSD_SETTING_MINUTES_MODE
}SSD_Mode_t;
/******************************************************************************/
void SSD_Set_Hours(const u8_t SSD_HOURS);
void SSD_Set_Minutes(const u8_t SSD_MINUTES);
void SSD_Set_Seconds(const u8_t SSD_SECONDS);
/******************************************************************************/
static void SSD_On(const SSD_t SSD_ID);
static void SSD_Off(const SSD_t SSD_ID);
static void SSD_Time(const u8_t TIME);
static void SSD_Update_Mode(void);
static void SSD_Update_Blinking(void);
static void SSD_Refesh(void);
/******************************************************************************/
extern SW_State_t SW_UP_Get_State(void);
extern SW_State_t SW_DOWN_Get_State(void);
extern SW_State_t SW_SETTING_Get_State(void);
/******************************************************************************/
static u8_t Hours = 12, Minutes = 55, Seconds = 0, SSD_Off_Periode = PERIODE_1_SEC, SSD_On_Periode = PERIODE_1_SEC, Counter = 5;
SSD_Mode_t SSD_Mode = SSD_NORMAL_MODE;
static SSD_t SSD_Id = SSD_HOURS_TENS;
extern Bool_t SW_Periode_Is_Ended;
/******************************************************************************/
void SSD_Set_Hours(const u8_t SSD_HOURS){
     Hours = SSD_HOURS;
}
void SSD_Set_Minutes(const u8_t SSD_MINUTES){
     Minutes = SSD_MINUTES;
}
void SSD_Set_Seconds(const u8_t SSD_SECONDS){
     Seconds = SSD_SECONDS;
}
void SSD_Init(void){
                    /* Init Data Lines */
     GPIO_SetPinDirection(SSD_A_PORT_ID, SSD_A_PIN_ID, SSD_DIRECTION);
     GPIO_SetPinDirection(SSD_B_PORT_ID, SSD_B_PIN_ID, SSD_DIRECTION);
     GPIO_SetPinDirection(SSD_C_PORT_ID, SSD_C_PIN_ID, SSD_DIRECTION);
     GPIO_SetPinDirection(SSD_D_PORT_ID, SSD_D_PIN_ID, SSD_DIRECTION);
                    /* Init Control Lines */
     GPIO_SetPinDirection(SSD_HOURS_TENS_PORT_ID, SSD_HOURS_TENS_PIN_ID, SSD_DIRECTION);
     GPIO_SetPinDirection(SSD_HOURS_ONES_PORT_ID, SSD_HOURS_ONES_PIN_ID, SSD_DIRECTION);
     GPIO_SetPinDirection(SSD_MINUTES_TENS_PORT_ID, SSD_MINUTES_TENS_PIN_ID, SSD_DIRECTION);
     GPIO_SetPinDirection(SSD_MINUTES_ONES_PORT_ID, SSD_MINUTES_ONES_PIN_ID, SSD_DIRECTION);
     GPIO_SetPinDirection(SSD_SECONDS_TENS_PORT_ID, SSD_SECONDS_TENS_PIN_ID, SSD_DIRECTION);
     GPIO_SetPinDirection(SSD_SECONDS_ONES_PORT_ID, SSD_SECONDS_ONES_PIN_ID, SSD_DIRECTION);
}
static void SSD_On(const SSD_t SSD_ID){
       switch(SSD_ID){
              case SSD_HOURS_TENS:
                   GPIO_SetPinValue(SSD_HOURS_TENS_PORT_ID, SSD_HOURS_TENS_PIN_ID, SSD_STATE_ON);
                   break;
              case SSD_HOURS_ONES:
                   GPIO_SetPinValue(SSD_HOURS_ONES_PORT_ID, SSD_HOURS_ONES_PIN_ID, SSD_STATE_ON);
                   break;
              case SSD_MINUTES_TENS:
                   GPIO_SetPinValue(SSD_MINUTES_TENS_PORT_ID, SSD_MINUTES_TENS_PIN_ID, SSD_STATE_ON);
                   break;
              case SSD_MINUTES_ONES:
                   GPIO_SetPinValue(SSD_MINUTES_ONES_PORT_ID, SSD_MINUTES_ONES_PIN_ID, SSD_STATE_ON);
                   break;
              case SSD_SECONDS_TENS:
                   GPIO_SetPinValue(SSD_SECONDS_TENS_PORT_ID, SSD_SECONDS_TENS_PIN_ID, SSD_STATE_ON);
                   break;
              case SSD_SECONDS_ONES:
                   GPIO_SetPinValue(SSD_SECONDS_ONES_PORT_ID, SSD_SECONDS_ONES_PIN_ID, SSD_STATE_ON);
                   break;
              default:
                   /* Error: Undefined SSD */
                   break;
       }
} 
static void SSD_Off(const SSD_t SSD_ID){
       switch(SSD_ID){
              case SSD_HOURS_TENS:
                   GPIO_SetPinValue(SSD_HOURS_TENS_PORT_ID, SSD_HOURS_TENS_PIN_ID, SSD_STATE_OFF);
                   break;
              case SSD_HOURS_ONES:
                   GPIO_SetPinValue(SSD_HOURS_ONES_PORT_ID, SSD_HOURS_ONES_PIN_ID, SSD_STATE_OFF);
                   break;
              case SSD_MINUTES_TENS:
                   GPIO_SetPinValue(SSD_MINUTES_TENS_PORT_ID, SSD_MINUTES_TENS_PIN_ID, SSD_STATE_OFF);
                   break;
              case SSD_MINUTES_ONES:
                   GPIO_SetPinValue(SSD_MINUTES_ONES_PORT_ID, SSD_MINUTES_ONES_PIN_ID, SSD_STATE_OFF);
                   break;
              case SSD_SECONDS_TENS:
                   GPIO_SetPinValue(SSD_SECONDS_TENS_PORT_ID, SSD_SECONDS_TENS_PIN_ID, SSD_STATE_OFF);
                   break;
              case SSD_SECONDS_ONES:
                   GPIO_SetPinValue(SSD_SECONDS_ONES_PORT_ID, SSD_SECONDS_ONES_PIN_ID, SSD_STATE_OFF);
                   break;
              default:
                   /* Error: Undefined SSD */
                   break;
       }
}
static void SSD_Time(const u8_t TIME){
       GPIO_SetPinValue(SSD_A_PORT_ID, SSD_A_PIN_ID, GET_BIT(TIME, 0));
       GPIO_SetPinValue(SSD_B_PORT_ID, SSD_B_PIN_ID, GET_BIT(TIME, 1));
       GPIO_SetPinValue(SSD_C_PORT_ID, SSD_C_PIN_ID, GET_BIT(TIME, 2));
       GPIO_SetPinValue(SSD_D_PORT_ID, SSD_D_PIN_ID, GET_BIT(TIME, 3));
}
void SSD_Update(void){
     /* Check 20 Ms Periode Ended */
     if(TRUE == SW_Periode_Is_Ended){
        if(SW_STATE_ON == SW_SETTING_Get_State()){
           SSD_Update_Mode();
        }
        switch(SSD_Mode){
               case SSD_NORMAL_MODE:
                    /* Do Nothing */
                    break;
               case SSD_SETTING_HOURS_MODE:
               case SSD_SETTING_MINUTES_MODE:
                    if(SW_STATE_ON == SW_UP_Get_State() ||
                       SW_STATE_ON == SW_DOWN_Get_State() ||
                       SW_STATE_ON == SW_SETTING_Get_State()){

                       SSD_Off_Periode = PERIODE_1_SEC;
                       SSD_On_Periode = PERIODE_1_SEC;
                       Counter = 5; /* Mapping For 5 Sec */
                    }
                    break;
               default:
                    /* Error: Undefined SSD Mode */
                    break;
        }
        SW_Periode_Is_Ended = FALSE;
     }
     SSD_Update_Blinking();
     SSD_Refesh();
}
static void SSD_Update_Mode(void){
       switch(SSD_Mode){
              case SSD_NORMAL_MODE:
                    SSD_Mode = SSD_SETTING_HOURS_MODE;
                    break;
              case SSD_SETTING_HOURS_MODE:
                    SSD_Mode = SSD_SETTING_MINUTES_MODE;
                    break;
              case SSD_SETTING_MINUTES_MODE:
                    SSD_Mode = SSD_NORMAL_MODE;
                    break;
              default:
                    /* Error: Undefined SSD Mode */
                    break;
       }
}
static void SSD_Update_Blinking(void){
       switch(SSD_Mode){
             case SSD_NORMAL_MODE:
                  /* No Blinking */
                  break;
             case SSD_SETTING_HOURS_MODE:
                  /* Don't Allow Refreshing SSD_Hours */
                  if(SSD_Off_Periode != ENDED){
                     SSD_Off_Periode--;
                     if(ENDED == SSD_Off_Periode){
                        Counter--; /* Decrement 1 Sec From 5 Sec */
                     }
                     switch(SSD_Id){
                            case SSD_HOURS_TENS:
                            case SSD_HOURS_ONES:
                                 SSD_Id = SSD_MINUTES_TENS;
                                 break;
                     }
                  }
                  /* Allow Refreshing SSD_Hours */
                  else{
                     SSD_On_Periode--;
                     if(ENDED == SSD_On_Periode){
                        SSD_Off_Periode = PERIODE_1_SEC;
                        SSD_On_Periode = PERIODE_1_SEC;
                        Counter--; /* Decrement 1 Sec From 5 Sec */
                     }
                  }
                  /* Check 5 Sec Periode is Ended */
                  if(ENDED == Counter){
                     SSD_Mode = SSD_NORMAL_MODE;
                  }
                  break;
             case SSD_SETTING_MINUTES_MODE:
                  /* Don't Allow Refreshing SSD_Minutes */
                  if(SSD_Off_Periode != 0){
                     SSD_Off_Periode--;
                     if(ENDED == SSD_Off_Periode){
                        Counter--; /* Decrement 1 Sec From 5 Sec */
                     }
                     switch(SSD_Id){
                            case SSD_MINUTES_TENS:
                            case SSD_MINUTES_ONES:
                                 SSD_Id = SSD_SECONDS_TENS;
                                 break;
                     }
                  }
                  /* Allow Refreshing SSD_Minutes */
                  else{
                     SSD_On_Periode--;
                     if(ENDED == SSD_On_Periode){
                        SSD_Off_Periode = PERIODE_1_SEC;
                        SSD_On_Periode = PERIODE_1_SEC;
                        Counter--; /* Decrement 1 Sec From 5 Sec */
                     }
                  }
                  /* Check if 5 Sec Periode Ended */
                  if(ENDED == Counter){
                     SSD_Mode = SSD_NORMAL_MODE;
                  }
                  break;
             default:
                  /* Error: Undefined SSD Mode */
                  break;
       }
}
static void SSD_Refesh(void){
       SSD_Off(SSD_HOURS_TENS);
       SSD_Off(SSD_HOURS_ONES);
       SSD_Off(SSD_MINUTES_TENS);
       SSD_Off(SSD_MINUTES_ONES);
       SSD_Off(SSD_SECONDS_TENS);
       SSD_Off(SSD_SECONDS_ONES);
       switch(SSD_Id){
              case SSD_HOURS_TENS:
                   SSD_Time(Hours / 10);
                   SSD_On(SSD_HOURS_TENS);
                   SSD_Id = SSD_HOURS_ONES;
                   break;
              case SSD_HOURS_ONES:
                   SSD_Time(Hours % 10);
                   SSD_On(SSD_HOURS_ONES);
                   SSD_Id = SSD_MINUTES_TENS;
                   break;
              case SSD_MINUTES_TENS:
                   SSD_Time(Minutes / 10);
                   SSD_On(SSD_MINUTES_TENS);
                   SSD_Id = SSD_MINUTES_ONES;
                   break;
              case SSD_MINUTES_ONES:
                   SSD_Time(Minutes % 10);
                   SSD_On(SSD_MINUTES_ONES);
                   SSD_Id = SSD_SECONDS_TENS;
                   break;
              case SSD_SECONDS_TENS:
                   SSD_Time(Seconds / 10);
                   SSD_On(SSD_SECONDS_TENS);
                   SSD_Id = SSD_SECONDS_ONES;
                   break;
              case SSD_SECONDS_ONES:
                   SSD_Time(Seconds % 10);
                   SSD_On(SSD_SECONDS_ONES);
                   SSD_Id = SSD_HOURS_TENS;
                   break;
              default:
                   /* Error: Undefined SSD */
                   break;
       }
}