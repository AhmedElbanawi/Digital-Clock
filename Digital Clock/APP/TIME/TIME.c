/******************************************************************************/
#ifndef TIME_H
#include "TIME.h"
#endif
/******************************************************************************/
#ifndef SYS_DATA_TYPES_H
#include "Sys_Data_Types.h"
#endif
/******************************************************************************/
#define SECONDS_MAX_VAL 59
#define MINUTES_MAX_VAL 59
#define HOURS_MAX_VAL 23
/******************************************************************************/
#define HOURS_MIN_VAL 0
#define MINUTES_MIN_VAL 0
#define SECONDS_MIN_VAL 0
/******************************************************************************/
#define SECONDS_VAL 0
#define MINUTES_VAL 0
#define HOURS_VAL 0
/******************************************************************************/
#define ENDED 0
#define TIME_1_SEC 50
/******************************************************************************/
typedef enum{
        SW_UP = 0,
        SW_DOWN,
        SW_SETTING,
        SW_MAX_NUMBER
}SW_t;
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
static void Auto_Time_Update(void); /* Every 1 Sec */
static void Manul_Time_Update(void); /* Every 20 Ms */
extern SW_State_t SW_UP_Get_State(void);
extern SW_State_t SW_DOWN_Get_State(void);
extern SW_State_t SW_SETTING_Get_State(void);
/******************************************************************************/
extern void SSD_Set_Hours(const u8_t SSD_HOURS);
extern void SSD_Set_Minutes(const u8_t SSD_MINUTES);
extern void SSD_Set_Seconds(const u8_t SSD_SECONDS);
/******************************************************************************/
extern Bool_t SW_Periode_Is_Ended;
static u8_t Hours = HOURS_VAL, Minutes = MINUTES_VAL, Seconds = SECONDS_VAL;
extern SSD_Mode_t SSD_Mode;
/******************************************************************************/
void TIME_Init(void){
     SSD_Set_Hours(Hours);
     SSD_Set_Minutes(Minutes);
     SSD_Set_Seconds(Seconds);
}
/******************************************************************************/
static void Auto_Time_Update(void){
       static u8_t Timer = TIME_1_SEC;
       Timer--;
       if(ENDED == Timer){
          Timer = TIME_1_SEC;
          if(SECONDS_MAX_VAL == Seconds){
             Seconds = SECONDS_MIN_VAL;
             if(MINUTES_MAX_VAL == Minutes){
                Minutes = MINUTES_MIN_VAL;
                if(HOURS_MAX_VAL == Hours){
                  Hours = HOURS_MIN_VAL;
                }else{
                   Hours++;
                }
                SSD_Set_Hours(Hours);
             }else{
                Minutes++;
             }
             SSD_Set_Minutes(Minutes);
          }else{
             Seconds++;
          }
          SSD_Set_Seconds(Seconds);
       }
}
/******************************************************************************/
static void Manul_Time_Update(void){
       switch(SSD_Mode){
              case SSD_NORMAL_MODE:
                   /* Time is Updated Automatic Only */
                   break;
              case SSD_SETTING_HOURS_MODE:
                   if(Hours < HOURS_MAX_VAL && SW_STATE_ON == SW_UP_Get_State()){
                      Hours++;
                      SSD_Set_Hours(Hours);
                   }else if(Hours > HOURS_MIN_VAL && SW_STATE_ON == SW_DOWN_Get_State()){
                      Hours--;
                      SSD_Set_Hours(Hours);
                   }
                   break;
              case SSD_SETTING_MINUTES_MODE:
                   if(Minutes < MINUTES_MAX_VAL && SW_STATE_ON == SW_STATE_ON == SW_UP_Get_State()){
                      Minutes++;
                      SSD_Set_Minutes(Minutes);
                   }else if(Minutes > MINUTES_MIN_VAL && SW_STATE_ON == SW_DOWN_Get_State()){
                      Minutes--;
                      SSD_Set_Minutes(Minutes);
                   }
                   break;
              default:
                   /* Error: Undefined SSD Mode */
                   break;
       }
}
/******************************************************************************/
void TIME_Update(void){
     /* Check 20 Ms Periode Ended */
     if(TRUE == SW_Periode_Is_Ended){
        Auto_Time_Update(); /* Every 1 Sec */
        Manul_Time_Update(); /* Every 20 Ms */
     }
}
/******************************************************************************/