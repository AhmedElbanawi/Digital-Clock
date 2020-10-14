/******************************************************************************/
#ifndef SW_H
#define SW_H
#endif
/******************************************************************************/
#ifndef GPIO_H
#include "GPIO.h"
#endif
/******************************************************************************/
typedef enum{
        SW_UP_PIN_ID = GPIO_PIN0,
        SW_DOWN_PIN_ID = GPIO_PIN1,
        SW_SETTING_PIN_ID = GPIO_PIN2
}SW_Pin_ID_t;
typedef enum{
        SW_UP_PORT_ID = GPIO_PORTC,
        SW_DOWN_PORT_ID = GPIO_PORTC,
        SW_SETTING_PORT_ID = GPIO_PORTC
}SW_Port_ID_t;
typedef enum{
        SW_STATE_OFF = 0,
        SW_STATE_ON
}SW_State_t;
typedef enum{
        SW_PIN_DIRECTION = GPIO_INPUT
}SW_Pin_Direction_t;
typedef enum{
        SW_UP = 0,
        SW_DOWN,
        SW_SETTING,
        SW_MAX_NUMBER
}SW_t;
/******************************************************************************/
void SW_Init(void);
void SW_Update(void);
/******************************************************************************/