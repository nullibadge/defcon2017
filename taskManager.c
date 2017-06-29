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
#include "taskManager.h"

/* Task data structure defined and allocated here */
struct t_taskManager_taskData taskManager_TaskData;


void taskManager_Init(void *taskData) {
    struct t_taskManager_taskData *data = (struct t_taskManager_taskData *) taskData;
    
    data->holdTickCount = 0;
    data->appState = TASKMANAGER_STATE_START;
    
    
}

void taskManager_Main (void *taskData) {
    struct t_taskManager_taskData *data = (struct t_taskManager_taskData *) taskData;
    
    switch (data->appState) {
        case TASKMANAGER_STATE_START :
            /* Add badge default tasks */
            scheduler_TaskAdd(data->scheduler, data->availableTasks[TASK_BLINKY]);
            scheduler_TaskAdd(data->scheduler, data->availableTasks[TASK_FADE_DISPLAY]);
            
            data->appState = TASKMANAGER_STATE_IDLE;
            
            break;
        case TASKMANAGER_STATE_IDLE :
            data->appState = TASKMANAGER_STATE_IDLE;
            
            break;
            
        default : 
            
            break;
    }
    
}

void taskManager_Exit(void *taskData) {
    struct t_taskManager_taskData *data = (struct t_taskManager_taskData *) taskData;
    ;  // should never get here 
}

