/*
 * File:   nullifyBadge_displayL2.c
 * Author: sean
 *
 * Created on June 26, 2017, 9:24 PM
 */


#include <xc.h>
#include "nullifyBadge_displayL2.h"

void displayL2_Initialize (struct t_nullifyDisplay_l2 *display) {
    displayL1_Initialize(&display->display_l1);
    memset(display->charVect, ' ', sizeof(display->charVect));
    display->dpVect = 0;
    display->ledVect = 0;
}

void displayL2_PrintChar (struct t_nullifyDisplay_l2 *display, char c) {
    /* Shift the character vector */
    display->charVect[0] = display->charVect[1];
    display->charVect[1] = display->charVect[2];
    display->charVect[2] = display->charVect[3];
    
    /* Put the new character at character 3 */
    display->charVect[3] = c;
    
    /* Update the display */
    u8 k = 0;
    for (k = 0; k < 4; k++) {
        displayL1_SetSegChar(&display->display_l1, display->charVect[k], k);
    }
    
    displayL1_Update(&display->display_l1);
    
}

void displayL2_PutChar (struct t_nullifyDisplay_l2 *display, char c) {
    /* Shift the character vector */
    display->charVect[0] = display->charVect[1];
    display->charVect[1] = display->charVect[2];
    display->charVect[2] = display->charVect[3];
    
    /* Put the new character at character 3 */
    display->charVect[3] = c;
    
    /* Update the display */
    u8 k = 0;
    for (k = 0; k < 4; k++) {
        displayL1_SetSegChar(&display->display_l1, display->charVect[k], k);
    }
    
}

void displayL2_PutStr (struct t_nullifyDisplay_l2 *display, char *str) {
    
    u8 k = 0;
    
    while (str[k] != '\0') {
        displayL2_PutChar(display, str[k]);
        k++;
    }
    
}

void displayL2_PrintStr (struct t_nullifyDisplay_l2 *display, char *str) {
    
    u8 k = 0;
    
    while (str[k] != '\0') {
        displayL2_PrintChar(display, str[k]);
        k++;
    }
    
    displayL1_Update(&display->display_l1);
    
}

void displayL2_ForceUpdate (struct t_nullifyDisplay_l2 *display) {
    displayL1_Update(&display->display_l1);
}

void displayL2_EraseSegDisplay (struct t_nullifyDisplay_l2 *display) {
    displayL2_PutStr(display, "    ");
    displayL1_Update(&display->display_l1);
}

void displayL2_SetUserLeds (struct t_nullifyDisplay_l2 *display, u16 userLedData) {
    display->ledVect = userLedData;
    displayL1_SetUserLed(&display->display_l1, display->ledVect);
    displayL1_Update(&display->display_l1);
}

void displayL2_ClrUserLeds (struct t_nullifyDisplay_l2 *display) {
    displayL1_SetUserLed(&display->display_l1, 0);
    displayL1_Update(&display->display_l1);
}
