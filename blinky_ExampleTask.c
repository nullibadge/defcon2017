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
#include "blinky_ExampleTask.h"

void blinky_Init(void *taskData) {
    struct t_blinky_taskData *data = (struct t_blinky_taskData *) taskData;
    
    /* Register Badge Hardware to be Used */
    nullifyBadge_userLedsRegister(data->badge);
    nullifyBadge_userLedsClr(data->badge);
    
    /* Initialize application data */
    data->delayTickCount = BLINKY_DELAY_TICK_COUNT;
    data->ledState = LED_OFF;
    data->appState = BLINKY_TASK_STATE_DELAY;
}

void blinky_Main (void *taskData) {
    struct t_blinky_taskData *data = (struct t_blinky_taskData *) taskData;
    
    switch (data->appState) {
        case BLINKY_TASK_STATE_TOGGLE_LED :
            
            if (data->ledState == LED_OFF) {
                nullifyBadge_userLedsSet(data->badge, 0xAAAA);
                data->ledState = LED_ON;
            }
            else {
                nullifyBadge_userLedsSet(data->badge, 0x0);
                data->ledState = LED_OFF;
            }
            
            data->delayTickCount = BLINKY_DELAY_TICK_COUNT;
            data->appState = BLINKY_TASK_STATE_DELAY;
            
            break;
        case BLINKY_TASK_STATE_DELAY :
            
            if (data->delayTickCount) {
                data->delayTickCount -= 1;
            }
            
            /*
             * If data counter is 0, change state to STATE_TOGGLE_LED
             */
            if (!data->delayTickCount) {
                data->appState = BLINKY_TASK_STATE_TOGGLE_LED;
            }
            
            break;
            
        default : 
            
            break;
    }
    
}

void blinky_Exit(void *taskData) {
    struct t_blinky_taskData *data = (struct t_blinky_taskData *) taskData;
    nullifyBadge_userLedsClr(data->badge); // erase app data
    nullifyBadge_userLedsRelease(data->badge); // un-register hardware
}

