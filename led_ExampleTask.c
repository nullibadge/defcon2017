/*
 * File:   blinky_ExampleTask.c
 * Author: sean
 *
 * Created on June 25, 2017, 4:32 PM
 */


#include <xc.h>
#include "xc8_types.h"
#include "nullifyBadge.h"
#include "cooperative_scheduler.h"
#include "led_ExampleTask.h"

void ledTask_Init(void *taskData) {
    struct t_ledTask_taskData *data = (struct t_ledTask_taskData *) taskData;
    
    /* Register Badge Hardware to be Used */
    nullifyBadge_userLedsRegister(data->badge);
    nullifyBadge_userLedsClr(data->badge);
    
    /* Initialize application data */
    data->delayTickCount = LED_TASK_DELAY_TICK_COUNT;
    data->ledVect = 0x0;
    data->ledCnt = 0x0;
    data->setNotClr = 0x0;
    data->appState = LED_TASK_STATE_DELAY;
}

void ledTask_Main (void *taskData) {
    struct t_ledTask_taskData *data = (struct t_ledTask_taskData *) taskData;
    
    switch (data->appState) {
        case LED_TASK_STATE_SET_LED :
            
            /* LED Set/Clear */
            if (data->setNotClr) {
              data->ledVect |= (1 << data->ledCnt);    
            }
            else {
                data->ledVect &= ~(1 << data->ledCnt);
            }
            
            nullifyBadge_userLedsSet(data->badge, data->ledVect);
            
            /* Counter Control */
            if (data->ledCnt == 15) {
                data->setNotClr = ~data->setNotClr;
                data->ledCnt = 0;
            }
            else {
                data->ledCnt++;
            }
            
            data->delayTickCount = LED_TASK_DELAY_TICK_COUNT;
            data->appState = LED_TASK_STATE_DELAY;
            
            break;
        case LED_TASK_STATE_DELAY :
            
            if (data->delayTickCount) {
                data->delayTickCount--;
            }
            
            /*
             * If data counter is 0, change state to STATE_TOGGLE_LED
             */
            if (!data->delayTickCount) {
                data->appState = LED_TASK_STATE_SET_LED;
            }
            
            break;
            
        default : 
            
            break;
    }
    
}

void ledTask_Exit(void *taskData) {
    struct t_ledTask_taskData *data = (struct t_ledTask_taskData *) taskData;
    nullifyBadge_userLedsClr(data->badge); // erase app data
    nullifyBadge_userLedsRelease(data->badge); // un-register hardware
}

