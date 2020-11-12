/******************************************************************************/
#ifndef SW_H
#include "SW.h"
#endif
/******************************************************************************/
#ifndef SSD_H
#include "SSD.h"
#endif
/******************************************************************************/
#ifndef TIME_H
#include "TIME.h"
#endif
/******************************************************************************/
#ifndef CO_SCH_H
#include "CO_SCH.h"
#endif
/******************************************************************************/
void main() {
     CO_SCH_Init();
     SW_Init();
     TIME_Init();
     SSD_Init();
     CO_SCH_Add_Task(SW_Update, 0, 4);    /* Every 20 ms */
     CO_SCH_Add_Task(TIME_Update, 0, 4);  /* Every 20 ms */
     CO_SCH_Add_Task(SSD_Update, 0, 1);   /* Every 5 ms */
     CO_SCH_Start();
     while(1){
         CO_SCH_Dispatch_Tasks();
     }
}