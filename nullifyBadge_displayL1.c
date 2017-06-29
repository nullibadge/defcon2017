/*
 * File:   nullifyBadge_displayL1.c
 * Author: sean
 *
 * Created on June 26, 2017, 9:11 PM
 */


#include "nullifyBadge_displayL1.h"

u16 displayCharReverse (u16 cVal);

void displayL1_Initialize (struct t_nullifyDisplay_l1 *display) {
    memset(display->displayVect, 0, sizeof(struct t_nullifyDisplay_l1));
    displayL1_Update(display);
}

void displayL1_SetSegChar (struct t_nullifyDisplay_l1 *display, char c, u8 charPos) {
    /* 
     * Convert ASCII Character to equivalent data
     * vector for use with the display.
     */
    u16 charData = asciiCharTableLookup[(u8) c];
    
    /*
     * If the character is an odd position,
     * then perform reverse operation
     */
    if (charPos & 0x1) {
        charData = displayCharReverse(charData);
    }
    
    /* 
     * Write to correct character position within
     * the data vector.  16 bit to 8 bit character
     * mapping is as follows : 
     * 
     * NOTE : Character positions are read from left
     *        to right when looking at the badge, right
     *        side up.  Character 0 is the leftmost and 
     *        character 3 is the rightmost.
     * 
     * Character 0 :
     *   - Lower 8bits - Vector Byte 9
     *   - Upper 8bits - Vector Byte 8
     * 
     * Character 1 :
     *   - Lower 8bits - Vector Byte 7
     *   - Upper 8bits - Vector Byte 6
     * 
     * Character 2 :
     *   - Lower 8bits - Vector Byte 5
     *   - Upper 8bits - Vector Byte 4
     * 
     * Character 3 :
     *   - Lower 8bits - Vector Byte 3
     *   - Upper 8bits - Vector Byte 2
     * 
     */
    
    u8 dispDataVectBaseIdx = 8-(charPos<<1);
    
    /* Assign Upper */
    display->displayVect[dispDataVectBaseIdx] = (u8) (charData >> 8);
    
    /* Assign Lower */
    display->displayVect[dispDataVectBaseIdx+1] = (u8) (charData & 0xFF);
    
}

void displayL1_SetUserLed (struct t_nullifyDisplay_l1 *display, u16 userLedVect) {
    /* Assign user LED Vector to display bytes */
    display->displayVect[0] = (u8) (userLedVect >> 8);
    display->displayVect[1] = (u8) (userLedVect & 0xFF);
}

/* TODO : Fix this function ...eventually */
void displayL1_SetDp (struct t_nullifyDisplay_l1 *display, u8 displayDpVect) {
    /* 
     * Assign Decimal Point Bits to display bytes 
     * Only the bottom 4 bits are valid
     */
    
    /* Character 0 DP */
    display->displayVect[8] = (display->displayVect[8]) | ((displayDpVect & 0x8) << 6);
    
    /* Character 1 DP */
    display->displayVect[7] = (display->displayVect[7]) | ((displayDpVect & 0x4) << 6);
    
    /* Character 2 DP */
    display->displayVect[4] = (display->displayVect[4]) | ((displayDpVect & 0x2) << 6);
    
    /* Character 3 DP */
    display->displayVect[3] = (display->displayVect[3]) | ((displayDpVect & 0x1) << 6);
}

void displayL1_Update (struct t_nullifyDisplay_l1 *display) {
    u8 tmpRxBuf[10];
    
    SPI1_Exchange8bitBuffer(display->displayVect, 10, tmpRxBuf);
    TLC_LAT_SetHigh();
    TLC_LAT_SetLow();
}

u16 displayCharReverse (u16 cVal) {
    u8 retValUpper, retValLower, retValUpperRev;
    
    u8 k;
    
    /* Separate Upper from Lower */
    retValUpper = cVal >> 8;
    retValLower = cVal & 0xFF;
    
    /* Reverse Upper */
    retValUpperRev = 0;
    
    for (k = 0; k < 7; k++) {
        retValUpperRev |= (retValUpper & 0x1);
        retValUpper >>= 1;
        retValUpperRev <<= 1;
    }
    
    return (retValLower << 8) | (retValUpperRev);
}


