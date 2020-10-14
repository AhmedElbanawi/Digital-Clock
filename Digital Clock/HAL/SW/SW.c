/******************************************************************************/
#ifndef SW_H
#include "SW.h"
#endif
/******************************************************************************/
#define SW_PERIODE 4
#define ENDED 0
/******************************************************************************/
typedef enum{
        SW_PRESSING_TIME_FALLING_EDGE = 0,
        SW_PRESSING_TIME_RISING_EDGE
}SW_Pressing_Time_t;
/******************************************************************************/
SW_State_t SW_UP_Get_State(void);
SW_State_t SW_DOWN_Get_State(void);
SW_State_t SW_SETTING_Get_State(void);
/******************************************************************************/
static SW_State_t SW_Get_State(const SW_t SW_ID);
static void SW_Update_State(const SW_t SW_ID);
/******************************************************************************/
static SW_State_t SW_State[SW_MAX_NUMBER] = { SW_STATE_OFF };
Bool_t SW_Periode_Is_Ended = FALSE;
/******************************************************************************/
void SW_Init(void){
                   /* Init SW Up */
     GPIO_SetPinDirection(SW_UP_PORT_ID, SW_UP_PIN_ID, SW_PIN_DIRECTION);
                   /* Init SW Down */
     GPIO_SetPinDirection(SW_DOWN_PORT_ID, SW_DOWN_PIN_ID, SW_PIN_DIRECTION);
                   /* Init SW Setting */
     GPIO_SetPinDirection(SW_SETTING_PORT_ID, SW_SETTING_PIN_ID, SW_PIN_DIRECTION);
}
/******************************************************************************/
static SW_State_t SW_Get_State(const SW_t SW_ID){
       SW_State_t SW_State_Ret;
       switch(SW_ID){
              case SW_UP:
                   if(GPIO_HIGH == GPIO_ReadPinValue(SW_UP_PORT_ID, SW_UP_PIN_ID)){
                      SW_State_Ret = SW_STATE_ON;
                   }
                   else{
                      SW_State_Ret = SW_STATE_OFF;
                   }
                   break;
              case SW_DOWN:
                   if(GPIO_HIGH == GPIO_ReadPinValue(SW_DOWN_PORT_ID, SW_DOWN_PIN_ID)){
                      SW_State_Ret = SW_STATE_ON;
                   }
                   else{
                      SW_State_Ret = SW_STATE_OFF;
                   }
                   break;
              case SW_SETTING:
                   if(GPIO_HIGH == GPIO_ReadPinValue(SW_SETTING_PORT_ID, SW_SETTING_PIN_ID)){
                      SW_State_Ret = SW_STATE_ON;
                   }
                   else{
                      SW_State_Ret = SW_STATE_OFF;
                   }
                   break;
              default:
                   /* Error: Undefined SW */
                   SW_State_Ret = SW_STATE_OFF;
                   break;
       }
       return SW_State_Ret;
}
/******************************************************************************/
void SW_Update(void){
     static u8_t Timer_Ms = SW_PERIODE; /* SW Periode is 20 Ms */
     Timer_Ms--;
     if(ENDED == Timer_Ms){
        SW_Update_State(SW_UP);
        SW_Update_State(SW_DOWN);
        SW_Update_State(SW_SETTING);
        Timer_Ms = SW_PERIODE;
        SW_Periode_Is_Ended = TRUE;
     }
}
/******************************************************************************/
static void SW_Update_State(const SW_t SW_ID){
       static SW_Pressing_Time_t SW_Pressing_Time[SW_MAX_NUMBER] = { SW_PRESSING_TIME_FALLING_EDGE };
       switch(SW_ID){
              case SW_UP:
              case SW_DOWN:
              case SW_SETTING:
                   switch(SW_Pressing_Time[SW_ID]){
                          case SW_PRESSING_TIME_FALLING_EDGE:
                               SW_State[SW_ID] = SW_STATE_OFF;
                               if(SW_STATE_OFF == SW_Get_State(SW_ID)){
                                  SW_Pressing_Time[SW_ID] = SW_PRESSING_TIME_RISING_EDGE;
                               }
                               break;
                          case SW_PRESSING_TIME_RISING_EDGE:
                               if(SW_STATE_ON == SW_Get_State(SW_ID)){
                                  SW_Pressing_Time[SW_ID] = SW_PRESSING_TIME_FALLING_EDGE;
                                  SW_State[SW_ID] = SW_STATE_ON;
                               }
                               break;
                          default:
                               /* Error: Undefined State */
                               break;
                   }
                   break;
              default:
                   /* Error: Undefined SW */
                   break;
       }
}
/******************************************************************************/
SW_State_t SW_UP_Get_State(void){
           return SW_State[SW_UP];
}
/******************************************************************************/
SW_State_t SW_DOWN_Get_State(void){
           return SW_State[SW_DOWN];
}
/******************************************************************************/
SW_State_t SW_SETTING_Get_State(void){
           return SW_State[SW_SETTING];
}
/******************************************************************************/