/*
 * File:   fadeDisplay_ExampleTask.c
 * Author: sean
 *
 * Created on June 25, 2017, 4:32 PM
 */

#include <xc.h>
#include "xc8_types.h"
#include "nullifyBadge.h"
#include "cooperative_scheduler.h"
#include "fadeDisplay_ExampleTask.h"

void fadeDisplay_Init(void *taskData) {
    struct t_fadeDisplay_taskData *data = (struct t_fadeDisplay_taskData *) taskData;
    
    /* Initialize Badge Hardware to be Used */
    nullifyBadge_segDisplayRegister(data->badge);
    nullifyBadge_segDisplayErase(data->badge);
    
    /* Initialize application data */
    data->fadeVal = 0;
    PWM5_LoadDutyValue(gamma_table_256x1k[0]);
    data->appState = FADE_TASK_STATE_SET_DISPLAY_UP;
}

void fadeDisplay_Main (void *taskData) {
    struct t_fadeDisplay_taskData *data = (struct t_fadeDisplay_taskData *) taskData;
    
    switch (data->appState) {
        case FADE_TASK_STATE_SET_DISPLAY_UP :
            /* Next State Logic */
            data->appState = FADE_TASK_STATE_FADE_UP;
            
            nullifyBadge_segDisplayPrintStr(data->badge, "  UP");
            
            break;
        case FADE_TASK_STATE_FADE_UP :
            /* Next State Logic */
            if (data->fadeVal == 255) {
                data->appState = FADE_TASK_STATE_SET_DISPLAY_DOWN;
            }
            else {
                data->appState = FADE_TASK_STATE_FADE_UP;
            }
            
            nullifyBadge_segDisplaySetBrightness(data->fadeVal);
            
            if (data->fadeVal != 255) {
                data->fadeVal++;
            }
            
            break;
        case FADE_TASK_STATE_SET_DISPLAY_DOWN :
            /* Next STate Data */
            data->appState = FADE_TASK_STATE_FADE_DOWN;
            
            nullifyBadge_segDisplayPrintStr(data->badge, "DOWN");
            
            break;
        case FADE_TASK_STATE_FADE_DOWN :
            /* Next State Logic */
            if (data->fadeVal == 0) {
                data->appState = FADE_TASK_STATE_SET_DISPLAY_UP;
            }
            else {
                data->appState = FADE_TASK_STATE_FADE_DOWN;
            }
            
            nullifyBadge_segDisplaySetBrightness (data->fadeVal);
            
            if (data->fadeVal != 0){
              data->fadeVal--;
            }
            
            break;
            
        default : 
            
            break;
    }
    
}

void fadeDisplay_Exit(void *taskData) {
    struct t_fadeDisplay_taskData *data = (struct t_fadeDisplay_taskData *) taskData;
    nullifyBadge_segDisplayErase (data->badge); // erase application data from display
    nullifyBadge_segDisplayRelease (data->badge); // un-register hardware
    
}

