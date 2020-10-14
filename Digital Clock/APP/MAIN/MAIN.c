/******************************************************************************/
#ifndef OS_H
#include "OS.h"
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
#ifndef TIME_H
#include "TIME.h"
#endif
/******************************************************************************/
void main() {
     OS_Tick_Init(); /* Tick = 5 MS */
     SSD_Init();
     SW_Init();
     TIME_Init();
     while(1){
            if(TRUE == OS_Update){
               SW_Update();    /* SW Period 20 ms */
               TIME_Update();  /* TIME Period 20 ms */
               SSD_Update();   /* SSD Period 5 ms */
               OS_Update = FALSE;
            }
     }
}