/******************************************************************************/
#ifndef SSD_H
#define SSD_H
#endif
/******************************************************************************/
#ifndef GPIO_H
#include "GPIO.h"
#endif
/******************************************************************************/
typedef enum{
        SSD_DATA_A_PORT_ID = GPIO_PORTB,
        SSD_DATA_B_PORT_ID = GPIO_PORTB,
        SSD_DATA_C_PORT_ID = GPIO_PORTB,
        SSD_DATA_D_PORT_ID = GPIO_PORTB
}SSD_DATA_PORT_ID_t;
typedef enum{
        SSD_DATA_A_PIN_ID = GPIO_PIN0,
        SSD_DATA_B_PIN_ID = GPIO_PIN1,
        SSD_DATA_C_PIN_ID = GPIO_PIN2,
        SSD_DATA_D_PIN_ID = GPIO_PIN3
}SSD_DATA_PIN_ID_t;
typedef enum{
        SSD_STATE_ON = 0,
        SSD_STATE_OFF
}SSD_STATE_t;
typedef struct{
        GPIO_Port_ID_t Port  : 4;
        GPIO_Pin_ID_t  Pin   : 3;
        SSD_STATE_t    State : 1;
        u8_t Symbol;
}SSD_t;
typedef enum{
        SSD_HOURS_TENS = 0,
        SSD_HOURS_UNITS,
        SSD_MINUTES_TENS,
        SSD_MINUTES_UNITS,
        SSD_SECONDS_TENS,
        SSD_SECONDS_UNITS,
        SSD_MAX_NUMBERS
}SSD_ID_t;
/******************************************************************************/
typedef enum{
        SSD_NORMAL_MODE = 0,
        SSD_SETTING_HOURS_MODE,
        SSD_SETTING_MINUTES_MODE
}SSD_MODE_t;
/******************************************************************************/
extern SSD_t SSD_g[SSD_MAX_NUMBERS];
extern SSD_MODE_t SSD_Mode_g;
/******************************************************************************/
void SSD_Init(void);
void SSD_Update(void);
/******************************************************************************/