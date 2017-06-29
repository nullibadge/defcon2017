/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef COOPERATIVE_SCHEDULER_H
#define	COOPERATIVE_SCHEDULER_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include "xc8_types.h"

#define SCHEDULER_MAX_TASKS 16

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

struct t_schedulerTask {
    u16 systemTickLastExecuted;           /* System Tick value of when the task was last executed */
    void *taskData;                       /* Pointer to task specific data structure */
    void (*taskInitCallback)(void *); /* Function pointer to task initialization function */
    void (*taskExitCallback)(void *); /* Function pointer to task exit function */
    void (*taskExecuteCallback)(void *); /* Function pointer to task execution function */
    u16 taskInterval;                      /* Interval that the task is run in system ticks */
    s8 taskId;                            /* Task Identifier.  Assigned and invalidated by the scheduler */
};

struct t_scheduler {
    struct t_schedulerTask *tasks[SCHEDULER_MAX_TASKS]; /* Array of pointers to task structs */
    u16 taskEntryVector;                         /* Vector used to manage active tasks */
};


void scheduler_TaskInit(struct t_schedulerTask *task);
void scheduler_Init(struct t_scheduler *scheduler);

/* This function adds a task to the scheduler queue.
 * It returns the task ID upon success, or returns -1 if the task is not
 * successfully added to the scheduler.  A task is not added when the scheduler
 * is full.
 */
s8 scheduler_TaskAdd(struct t_scheduler *scheduler, struct t_schedulerTask *task);

/*
 * This function removes a task from the scheduler queue.
 */
void scheduler_TaskRemove(struct t_scheduler *scheduler, struct t_schedulerTask *task);

/* This function executes the scheduler itself */
void schedulerExecute(struct t_scheduler *scheduler);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* COOPERATIVE_SCHEDULER_H */

