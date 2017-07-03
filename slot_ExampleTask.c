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
#include "slot_ExampleTask.h"

void slot_Init(void *taskData) {
    struct t_slot_taskData *data = (struct t_slot_taskData *) taskData;
    
    /* Register Badge Hardware to be Used */
    nullifyBadge_userLedsRegister(data->badge);
    nullifyBadge_userLedsClr(data->badge);
    
    nullifyBadge_segDisplayRegister(data->badge);
    nullifyBadge_segDisplayErase(data->badge);
    
    /* Initialize application data */
    data->delayTickCount = 0;
    data->slotIsIdle = 0;
    data->strIdx = 0;
    data->userLeds = 0;
    data->cntr = SLOT_IDLE_FADE_DELAY_ITERATIONS;
    data->displayBrightness = 128;
    data->displayFadeUp = 1;
    data->i = 0;
    data->j = 0;
    data->k = 0;
    data->appState = SLOT_STATE_IDLE;
    
    data->ledCntr = SLOT_LED_IDLE_DELAY_ITERATONS;
    data->ledVect = 0;
    data->ledSetNotClr = 0;
    data->ledDir = 0;
}

void slot_Main (void *taskData) {
    struct t_slot_taskData *data = (struct t_slot_taskData *) taskData;
    
    u8 buttonYPressed = nullifyBadge_buttonYGet();
    
    switch (data->appState) {
        
        /*
         * ---------------------------------------------------------------------
         * SLOT_STATE_IDLE
         * ---------------------------------------------------------------------
         */
        case SLOT_STATE_IDLE :
            nullifyBadge_userLedsSet(data->badge, 0xAAAA);
            data->i = 4;
            data->k = 0;
            data->j = 4;
            
            /* Increment Slot Counter to give pseudo random behavior */
            if (data->strIdx == 8) {
                data->strIdx = 0;
            }
            else {
                data->strIdx++;
            }
            
            /* Set display */
            nullifyBadge_segDisplayPutStr(data->badge, "SLOT");
            nullifyBadge_segDisplayForceUpdate(data->badge);
            
            
            /* Set display brightness */
            if (buttonYPressed) {
                nullifyBadge_segDisplaySetBrightness(128);
            }
            else {
                if (!data->cntr) {
                    data->cntr = SLOT_IDLE_FADE_DELAY_ITERATIONS;

                    if(data->displayBrightness == 0) {
                        data->displayFadeUp = 1;
                    }
                    else if (data->displayBrightness == 255) {
                        data->displayFadeUp = 0;
                    }

                    nullifyBadge_segDisplaySetBrightness(data->displayBrightness);

                    if (data->displayFadeUp) {
                        data->displayBrightness++;
                    }
                    else {
                        data->displayBrightness--;
                    }
                }
                else {
                    data->cntr--;
                }
            }
            
            
            if (buttonYPressed) {
                data->cntr = SLOT_SPIN_ANIMATION_HOLD_ITERATIONS;
            }
            
            /* Next State Logic */
            if (buttonYPressed){
                data->appState = SLOT_STATE_SPIN;
            }
            else {
                data->appState = SLOT_STATE_IDLE;
            }
            
            break;
        
        /*
         * ---------------------------------------------------------------------
         * SLOT_STATE_SPIN
         * ---------------------------------------------------------------------
         */
        case SLOT_STATE_SPIN :
            nullifyBadge_userLedsSet(data->badge, 0xF81F);
            
            if (!data->cntr) {
                data->cntr = SLOT_SPIN_ANIMATION_HOLD_ITERATIONS;
                
                /* Perform Animation */
                if (data->i != 0) {
                    if (data->j != 0) {
                        if (data->k != 4) {
                            u8 p;
                            nullifyBadge_segDisplayPutStr(data->badge, slotStrTable[data->strIdx]);
                            for (p = 0; p < data->i; p++) {
                                nullifyBadge_segDisplayPutCharPos(data->badge, (data->k & 0x3), p);
                            }
                            nullifyBadge_segDisplayForceUpdate(data->badge);
                            data->k++;
                        }
                        else {
                            data->k = 0;
                            data->j--;
                        }
                    }
                    else {
                        data->j = 4;
                        data->i--;
                    }
                }
                
            }
            else{
                data->cntr--;
            }
            
            /* Next State Logic */
            if (data->k == 0 && data->j == 4 && data->i == 0) {
                data->k = 0; // reuse k for next state
                data->j = 0; // reuse j for next state
                data->cntr = 0;
                data->appState = SLOT_STATE_FLASH_RESULT;
            }
            else {
                data->appState = SLOT_STATE_SPIN;
            }
            
            break;
            
        /*
         * ---------------------------------------------------------------------
         * SLOT_STATE_FLASH_RESULT
         * ---------------------------------------------------------------------
         */
        case SLOT_STATE_FLASH_RESULT :
            
            if (!data->cntr) {
                
                /* Perform Animation */
                if (data->k) { // Set display
                     nullifyBadge_userLedsSet(data->badge, 0xFFFF);
                    nullifyBadge_segDisplayPutStr(data->badge, slotStrTable[data->strIdx]);
                    nullifyBadge_segDisplayForceUpdate(data->badge);
                    data->cntr = SLOT_FLASH_ANIMATION_HOLD_LOW_ITERATIONS;
                    data->k = 0;
                    data->j++;
                }
                else {
                    nullifyBadge_userLedsClr(data->badge);
                    nullifyBadge_segDisplayErase(data->badge);
                    data->cntr = SLOT_FLASH_ANIMATION_HOLD_HIGH_ITERATIONS;
                    data->k = 1;
                }
                
                
            }
            else {
                data->cntr--;
            }
            
            /* Next State Logic */
            if (data->j == SLOT_FLASH_ANIMATION_NUM_FLASHES) {
                data->cntr = SLOT_HOLD_RESULT_ITERATIONS;
                data->appState = SLOT_STATE_HOLD_RESULT;
            }
            else {
                data->appState = SLOT_STATE_FLASH_RESULT;
            }
            
            break;
            
        /*
         * ---------------------------------------------------------------------
         * SLOT_STATE_HOLD_RESULT
         * ---------------------------------------------------------------------
         */
        case SLOT_STATE_HOLD_RESULT : 
            nullifyBadge_userLedsSet(data->badge, 0xFFFF);
            
            nullifyBadge_segDisplayPutStr(data->badge, slotStrTable[data->strIdx]);
            nullifyBadge_segDisplayForceUpdate(data->badge);
            
            data->cntr--;
            
            if (!data->cntr) {
                data->appState = SLOT_STATE_IDLE;
            }
            else {
                data->appState = SLOT_STATE_HOLD_RESULT;
            }
            
            break;
            
        default : 
            data->appState = SLOT_STATE_IDLE;
            break;
    }
    
}

void slot_Exit (void *taskData) {
    struct t_slot_taskData *data = (struct t_slot_taskData *) taskData;
    nullifyBadge_userLedsClr(data->badge); // erase app data
    nullifyBadge_userLedsRelease(data->badge); // un-register hardware
}

