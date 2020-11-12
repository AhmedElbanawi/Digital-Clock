/******************************************************************************/
#ifndef SSD_H
#include "SSD.h"
#endif
/******************************************************************************/
#ifndef SW_H
#include "SW.h"
#endif
/******************************************************************************/
#define PERIOD_20_MS 4
#define PERIOD_5_SEC 5
#define PERIOD_1_SEC 200
/******************************************************************************/
SSD_t SSD_g[SSD_MAX_NUMBERS] = {  
                                  {GPIO_PORTD, GPIO_PIN0, SSD_STATE_OFF, 0},
                                  {GPIO_PORTD, GPIO_PIN1, SSD_STATE_OFF, 0},
                                  {GPIO_PORTD, GPIO_PIN2, SSD_STATE_OFF, 0},
                                  {GPIO_PORTD, GPIO_PIN3, SSD_STATE_OFF, 0},
                                  {GPIO_PORTD, GPIO_PIN4, SSD_STATE_OFF, 0},
                                  {GPIO_PORTD, GPIO_PIN5, SSD_STATE_OFF, 0}
                                };
/******************************************************************************/
typedef struct{
        BOOL_t Flag   : 1;
        u8_t   Period : 7;
        u8_t   Cnt;
}MODE_t;
/******************************************************************************/
SSD_MODE_t SSD_Mode_g = SSD_NORMAL_MODE;
static SSD_ID_t SSD_Id = SSD_HOURS_TENS;
static MODE_t Mode = {TRUE, PERIOD_5_SEC, PERIOD_1_SEC};
/******************************************************************************/
static void Init(SSD_t* const SSD);
static void On(SSD_t* const SSD);
static void Off(SSD_t* const SSD);
static void Set_Symbol(SSD_t* const SSD);
static void Update_Mode(void);
static void Refresh(void);
static void Toggle_Mode(const SSD_ID_t ID);
static void Reset_Mode(MODE_t* const MODE);
/******************************************************************************/
static void Init(SSD_t* const SSD){
     GPIO_SetPinDirection(SSD->Port, SSD->Pin, GPIO_OUTPUT);
     Off(SSD);
}
/******************************************************************************/
static void Off(SSD_t* const SSD){
     GPIO_SetPinValue(SSD->Port, SSD->Pin, GPIO_HIGH);
     SSD->State = SSD_STATE_OFF;
}
/******************************************************************************/
static void On(SSD_t* const SSD){
     GPIO_SetPinValue(SSD->Port, SSD->Pin, GPIO_LOW);
     SSD->State = SSD_STATE_ON;
}
/******************************************************************************/
static void Set_Symbol(SSD_t* const SSD){
     GPIO_SetPinValue(SSD_DATA_A_PORT_ID, SSD_DATA_A_PIN_ID, GET_BIT(SSD->Symbol, 0));
     GPIO_SetPinValue(SSD_DATA_B_PORT_ID, SSD_DATA_B_PIN_ID, GET_BIT(SSD->Symbol, 1));
     GPIO_SetPinValue(SSD_DATA_C_PORT_ID, SSD_DATA_C_PIN_ID, GET_BIT(SSD->Symbol, 2));
     GPIO_SetPinValue(SSD_DATA_D_PORT_ID, SSD_DATA_D_PIN_ID, GET_BIT(SSD->Symbol, 3));
}
/******************************************************************************/
void SSD_Update(void){
     Update_Mode();
     Refresh();
}
/******************************************************************************/
static void Update_Mode(void){
       static u8_t Period = PERIOD_20_MS;
       Period--;
        switch(SSD_Mode_g){
              case SSD_NORMAL_MODE:
                   if(ENDED == Period){
                      if(SW_STATE_ON == SW_g[SW_SETTING].State){
                         SSD_Mode_g = SSD_SETTING_HOURS_MODE;
                         Reset_Mode(&Mode);
                      }
                      Period = PERIOD_20_MS;
                   }
                   break;
              case SSD_SETTING_HOURS_MODE:
                   if(ENDED == Period){
                      if(SW_STATE_ON == SW_g[SW_SETTING].State){
                         SSD_Mode_g = SSD_SETTING_MINUTES_MODE;
                         Reset_Mode(&Mode);
                      }else if(SW_STATE_ON == SW_g[SW_Up].State || SW_STATE_ON == SW_g[SW_DOWN].State){
                         Reset_Mode(&Mode);
                         Mode.Flag = FALSE;
                      }
                      Period = PERIOD_20_MS;
                   }
                   Toggle_Mode(SSD_HOURS_TENS);
                   break;
              case SSD_SETTING_MINUTES_MODE:
                   if(ENDED == Period){
                      if(SW_STATE_ON == SW_g[SW_SETTING].State){
                         SSD_Mode_g = SSD_NORMAL_MODE;
                      }else if(SW_STATE_ON == SW_g[SW_Up].State || SW_STATE_ON == SW_g[SW_DOWN].State){
                         Reset_Mode(&Mode);
                         Mode.Flag = FALSE;
                      }
                      Period = PERIOD_20_MS;
                   }
                   Toggle_Mode(SSD_MINUTES_TENS);
                   break;
              default:
                   /* Error: Undefined SSD_Mode */
                   break;
        }
}
/******************************************************************************/
static void Toggle_Mode(const SSD_ID_t ID){
       if(TRUE == Mode.Flag){
          Mode.Cnt--;
          if(ENDED == Mode.Cnt){
             Mode.Period--;
             if(ENDED == Mode.Period){
                SSD_Mode_g = SSD_NORMAL_MODE;
             }
             Mode.Cnt = PERIOD_1_SEC;
             Mode.Flag = FALSE;
          }else if(ID == SSD_Id){
             SSD_Id += 2;
          }
       }else{
          Mode.Cnt--;
          if(ENDED == Mode.Cnt){
             Mode.Period--;
             if(ENDED == Mode.Period){
                SSD_Mode_g = SSD_NORMAL_MODE;
             }else if(ID == SSD_Id){
                SSD_Id += 2;
             }
             Mode.Cnt = PERIOD_1_SEC;
             Mode.Flag = TRUE;
          }
       }
}
/******************************************************************************/
static void Reset_Mode(MODE_t* const MODE){
       MODE->Flag = TRUE;
       MODE->Period = PERIOD_5_SEC;
       MODE->Cnt = PERIOD_1_SEC;
}
/******************************************************************************/
static void Refresh(void){
     Off(&SSD_g[SSD_HOURS_TENS]);
     Off(&SSD_g[SSD_HOURS_UNITS]);
     Off(&SSD_g[SSD_MINUTES_TENS]);
     Off(&SSD_g[SSD_MINUTES_UNITS]);
     Off(&SSD_g[SSD_SECONDS_TENS]);
     Off(&SSD_g[SSD_SECONDS_UNITS]);
     switch(SSD_Id){
            case SSD_HOURS_TENS:
                 Set_Symbol(&SSD_g[SSD_HOURS_TENS]);
                 On(&SSD_g[SSD_HOURS_TENS]);
                 SSD_Id = SSD_HOURS_UNITS;
                 break;
            case SSD_HOURS_UNITS:
                 Set_Symbol(&SSD_g[SSD_HOURS_UNITS]);
                 On(&SSD_g[SSD_HOURS_UNITS]);
                 SSD_Id = SSD_MINUTES_TENS;
                 break;
            case SSD_MINUTES_TENS:
                 Set_Symbol(&SSD_g[SSD_MINUTES_TENS]);
                 On(&SSD_g[SSD_MINUTES_TENS]);
                 SSD_Id = SSD_MINUTES_UNITS;
                 break;
            case SSD_MINUTES_UNITS:
                 Set_Symbol(&SSD_g[SSD_MINUTES_UNITS]);
                 On(&SSD_g[SSD_MINUTES_UNITS]);
                 SSD_Id = SSD_SECONDS_TENS;
                 break;
            case SSD_SECONDS_TENS:
                 Set_Symbol(&SSD_g[SSD_SECONDS_TENS]);
                 On(&SSD_g[SSD_SECONDS_TENS]);
                 SSD_Id = SSD_SECONDS_UNITS;
                 break;
            case SSD_SECONDS_UNITS:
                 Set_Symbol(&SSD_g[SSD_SECONDS_UNITS]);
                 On(&SSD_g[SSD_SECONDS_UNITS]);
                 SSD_Id = SSD_HOURS_TENS;
                 break;
            default:
                 /* Error: Undefined SSD */
                 break;
     }
}
/******************************************************************************/
void SSD_Init(void){
     SSD_ID_t Id;
     for(Id = SSD_HOURS_TENS; Id < SSD_MAX_NUMBERS; Id++){
         Init(SSD_g + Id);
     }
     GPIO_SetPinDirection(SSD_DATA_A_PORT_ID, SSD_DATA_A_PIN_ID, GPIO_OUTPUT);
     GPIO_SetPinDirection(SSD_DATA_B_PORT_ID, SSD_DATA_B_PIN_ID, GPIO_OUTPUT);
     GPIO_SetPinDirection(SSD_DATA_C_PORT_ID, SSD_DATA_C_PIN_ID, GPIO_OUTPUT);
     GPIO_SetPinDirection(SSD_DATA_D_PORT_ID, SSD_DATA_D_PIN_ID, GPIO_OUTPUT);
     SSD_Update();
}
/******************************************************************************/