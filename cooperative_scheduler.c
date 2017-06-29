/*
 * File:   cooperative_scheduler.c
 * Author: sean
 *
 * Created on June 25, 2017, 3:47 PM
 */


#include "xc8_types.h"
#include "mcc_generated_files/mcc.h"
#include "cooperative_scheduler.h"



/* Private functions declared here */

/* This function executes a task.  It is required that the execute callback not
 * be NULL, otherwise undefined results will occur.
 */
static void scheduler_TaskRun(struct t_schedulerTask *task) {
    task->taskExecuteCallback (task->taskData);
    task->systemTickLastExecuted = TMR0_Read16bitTimer();
}


/* Public functions declared here */
void scheduler_Init(struct t_scheduler *scheduler){
    scheduler->taskEntryVector = 0x0;
    u8 k;
    
    for (k = 0; k < SCHEDULER_MAX_TASKS; k++) {
        scheduler->tasks[k] = NULL;
    }
}

void scheduler_TaskInit(struct t_schedulerTask *task) {
    task->systemTickLastExecuted = 0;
    task->taskData = NULL;
    task->taskInitCallback = NULL; 
    task->taskExitCallback = NULL;
    task->taskExecuteCallback = NULL;
    task->taskInterval = 65535;
    task->taskId = -1;
}

s8 scheduler_TaskAdd(struct t_scheduler *scheduler, struct t_schedulerTask *task) {
    u8 k;
    for (k = 0; k < SCHEDULER_MAX_TASKS; k++) {
        if (!(scheduler->taskEntryVector & (1 << k)) ) {
            scheduler->tasks[k] = task; /* Assign task pointer to task pointer array */
            scheduler->taskEntryVector |= (1 << k); /* Validate appropriate task vector bit */
            
            if (task->taskInitCallback != NULL) { /* Execute tasks initialization function if any */
                task->taskInitCallback (task->taskData);
            }
            
            task->taskId = (s8) k; /* Assign task's taskId */
            return k;
        }
    }
    
    task->taskId = -1;
    return -1;
}

/*
 * Task ID must be valid (not -1) otherwise undefined results will may occur
 */
void scheduler_TaskRemove(struct t_scheduler *scheduler, struct t_schedulerTask *task) {
    scheduler->taskEntryVector &= ~(1 << task->taskId); /* Invalidate task vector bit */
    if (task->taskExitCallback != NULL) { /* Execute task exit function if any */
        task->taskExitCallback (task->taskData);
    }
    task->taskId = -1; /* Invalidate task */
}

void schedulerExecute(struct t_scheduler *scheduler) {
    u16 currentSystemTick;
    u16 taskLastSystemTick;
    u16 tickDelta;
    u8 k;
    
    for (k = 0; k < SCHEDULER_MAX_TASKS; k++) {
        
        /* Check if task is valid */
        if (!(scheduler->taskEntryVector & (1 << k)) ) {
            continue;
        }
        
        currentSystemTick = TMR0_Read16bitTimer();
        taskLastSystemTick = scheduler->tasks[k]->systemTickLastExecuted;
        
        /* Calculate Delta with rollover handling */
//        if (currentSystemTick < taskLastSystemTick) {
//            // Handle Timer Rollover for 16 bit timer
//            tickDelta = currentSystemTick + (65535-taskLastSystemTick);
//        }
//        else {
            tickDelta = currentSystemTick - taskLastSystemTick;
//        }
        
        /* Determine to Execute Task */
        if (tickDelta >= scheduler->tasks[k]->taskInterval) {
            scheduler_TaskRun(scheduler->tasks[k]);
        }
        
    }
    
}
