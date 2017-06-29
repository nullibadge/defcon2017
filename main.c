/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC16LF18346
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.42
        MPLAB             :  MPLAB X 3.65
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/
#include <stdio.h>
#include <pic16f18346.h>
#include "xc8_types.h"

#include "nullifyBadge.h"
#include "cooperative_scheduler.h"

#include "blinky_ExampleTask.h"
#include "fadeDisplay_ExampleTask.h"
#include "led_ExampleTask.h"

/*
                         Main application
 */

/* Declare Badge Hardware Instance */
struct t_nullifyBadge badge_inst;

/* Define available tasks */
static struct t_schedulerTask blinky_ExampleTask;
static struct t_schedulerTask ledTask_ExampleTask;
static struct t_schedulerTask fadeDisplay_ExampleTask;

/* Allocate task data structures */
struct t_blinky_taskData blinky_TaskData;
struct t_fadeDisplay_taskData fadeDisplay_TaskData;
struct t_ledTask_taskData ledTask_TaskData;

struct t_scheduler schedulerInst;

void main(void)
{
    /* Initialize the platform */
    nullifyBadge_platformInit(&badge_inst);
    
    /* Initialize Cooperative Scheduler */
    scheduler_Init(&schedulerInst);

    /* Initialize tasks */
    scheduler_TaskInit(&blinky_ExampleTask);
    scheduler_TaskInit(&ledTask_ExampleTask);
    scheduler_TaskInit(&fadeDisplay_ExampleTask);
    
    /* Pass external data to task data structures */
    blinky_TaskData.badge      = &badge_inst;
    ledTask_TaskData.badge     = &badge_inst;
    fadeDisplay_TaskData.badge = &badge_inst;
    
    /* Configure Tasks */
    blinky_ExampleTask.taskData = (void *) &blinky_TaskData;
    blinky_ExampleTask.taskInitCallback = blinky_Init;
    blinky_ExampleTask.taskExecuteCallback = blinky_Main;
    blinky_ExampleTask.taskExitCallback = blinky_Exit;
    blinky_ExampleTask.taskInterval = 10;
    
    ledTask_ExampleTask.taskData = (void *) &ledTask_TaskData;
    ledTask_ExampleTask.taskInitCallback = ledTask_Init;
    ledTask_ExampleTask.taskExecuteCallback = ledTask_Main;
    ledTask_ExampleTask.taskExitCallback = ledTask_Exit;
    ledTask_ExampleTask.taskInterval = 10;
    
    fadeDisplay_ExampleTask.taskData = (void *) &fadeDisplay_TaskData;
    fadeDisplay_ExampleTask.taskInitCallback = fadeDisplay_Init;
    fadeDisplay_ExampleTask.taskExecuteCallback = fadeDisplay_Main;
    fadeDisplay_ExampleTask.taskExitCallback = fadeDisplay_Exit;
    fadeDisplay_ExampleTask.taskInterval = 3;
    
    /* Launch Tasks */
    scheduler_TaskAdd(&schedulerInst, &fadeDisplay_ExampleTask);
    scheduler_TaskAdd(&schedulerInst, &ledTask_ExampleTask);
    
    while(1){
        schedulerExecute(&schedulerInst);
    }
    
}
    




    
/**
 End of File
*/

