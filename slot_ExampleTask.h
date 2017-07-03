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
#ifndef SLOT_EXAMPLETASK_H
#define	SLOT_EXAMPLETASK_H

#include <xc.h> // include processor files - each processor file is guarded.  

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

/* Delay parameters time value can be calculated as ITERATIONS x TASK INTERVAL */
#define SLOT_IDLE_FADE_DELAY_ITERATIONS           0
#define SLOT_SPIN_ANIMATION_HOLD_ITERATIONS       2
#define SLOT_FLASH_ANIMATION_HOLD_HIGH_ITERATIONS 12
#define SLOT_FLASH_ANIMATION_HOLD_LOW_ITERATIONS  7
#define SLOT_FLASH_ANIMATION_NUM_FLASHES          11
#define SLOT_HOLD_RESULT_ITERATIONS               200

#define SLOT_LED_IDLE_DELAY_ITERATONS 50;

static const char* slotStrTable[9] = {
    "BEER",
    "WSKY",
    "TQLA",
    "SHOT",
    "CPTN",
    "VDKA",
    " GIN",
    "CHUG",
    " RUM"
};

enum t_slotAppStates {
    SLOT_STATE_IDLE,
    SLOT_STATE_SPIN,
    SLOT_STATE_FLASH_RESULT,
    SLOT_STATE_HOLD_RESULT
};

struct t_slot_taskData {
    /* Badge Hardware */
    struct t_nullifyBadge *badge;
    
    /* Internal App Data */
    u16 delayTickCount;
    u8 slotIsIdle;
    
    u16 ledCntr;
    u16 ledVect;
    u8  ledSetNotClr;
    u8  ledDir;
    
    u16 cntr;
    u8 displayBrightness;
    u8 displayFadeUp;
    u8 i;
    u8 j;
    u8 k;
    
    u8 strIdx;
    u16 userLeds;
    
    enum t_slotAppStates appState;
};

void slot_Init(void *taskData);
void slot_Main (void *taskData);
void slot_Exit(void *taskData);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* SLOT_EXAMPLETASK_H */

