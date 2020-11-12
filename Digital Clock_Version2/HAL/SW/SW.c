/******************************************************************************/
#ifndef SW_H
#include "SW.h"
#endif
/******************************************************************************/
SW_t SW_g[SW_MAX_NUMBERS] = {
                               {GPIO_PORTC, GPIO_PIN0, SW_FALLING, SW_STATE_OFF},
                               {GPIO_PORTC, GPIO_PIN1, SW_FALLING, SW_STATE_OFF},
                               {GPIO_PORTC, GPIO_PIN2, SW_FALLING, SW_STATE_OFF}
                               
                            };
/******************************************************************************/
static void Init(SW_t* const SW);
static void Read(SW_t* const SW);
/******************************************************************************/
static void Init(SW_t* const SW){
     GPIO_SetPinDirection(SW->Port, SW->Pin, GPIO_INPUT);
}
/******************************************************************************/
static void Read(SW_t* const SW){
     switch(SW->Time){
            case SW_FALLING:
                 SW->State = SW_STATE_OFF;
                 if(GPIO_LOW == GPIO_ReadPinValue(SW->Port, SW->Pin)){
                    SW->Time = SW_RISING;
                 }
                 break;
            case SW_RISING:
                 if(GPIO_HIGH == GPIO_ReadPinValue(SW->Port, SW->Pin)){
                    SW->State = SW_STATE_ON;
                    SW->Time = SW_FALLING;
                 }
                 break;
            default:
                 /* Error: Undefined SW Time */
                 break;
                 
     }
}
/******************************************************************************/
void SW_Init(void){
     SW_ID_t Id;
     for(Id = SW_SETTING; Id < SW_MAX_NUMBERS; Id++){
         Init(SW_g + Id);
     }
}
/******************************************************************************/
void SW_Update(void){
     SW_ID_t Id;
     for(Id = SW_SETTING; Id < SW_MAX_NUMBERS; Id++){
         Read(SW_g + Id);
     }
}
/******************************************************************************/