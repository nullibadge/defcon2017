/*
 * File:   nullifyBadge.c
 * Author: sean
 *
 * Created on May 18, 2017, 1:26 AM
 */

#include <string.h>
#include <xc.h>
#include "nullifyBadge.h"

/* Initializes Nullify Badge Version 1 Revision 1 DEFCON 2017 Platform */
void nullifyBadge_platformInit(struct t_nullifyBadge *badge) {
    /* Initialize Device and Oscillator */
    SYSTEM_Initialize();
    OSCILLATOR_Initialize();
    
    /* Initialize Peripherals */
    TMR0_Initialize();
    TMR2_Initialize();
    TMR4_Initialize();
    
    PIN_MANAGER_Initialize();
    PWM1_Initialize();
    
    PWM2_Initialize();
    PWM5_Initialize();
    PWM6_Initialize();
    SPI1_Initialize();
    
    /* Digit Select, set duty cycle to 50% */
    PWM1_LoadDutyValue(128);
    
    /*
     * IR LED TX Carrier frequency generator
     * Set to 26.6 kHz to transmit to to 15 % of receiver sensitivity
     * 
     * Default the value to OFF for active low signals.
     * 
     * Set the duty cycle to 75% which is effective 25% for active low signal.
     * This will ensure that the IR LED does not burn out
     * DO NOT MODIFY UNLESS YOU REALLY KNOW WHAT YOU'RE DOING!!!
     */
    IR_TXD_N_SetHigh();
    PWM2_LoadDutyValue(192); // DO NOT MODIFY UNLESS YOU ARE FEELIN' BALLSY AND WANT POTENTIALLY BROKEN HW
    
    /*
     * Default display led brightness levels to 50%
     */
    PWM5_LoadDutyValue(gamma_table_256x1k[128]); // Display PWM
    PWM6_LoadDutyValue(gamma_table_256x1k[128]); // LED PWM
    
    /* Initialize the display driver */
    displayL2_Initialize(&badge->display);
    
    /* Initialize HW registry */
    badge->registeredHw = 0x0;
    
}

/* 
 * -----------------------------------------------------------------------------
 * API Functions for Segment Display 
 * -----------------------------------------------------------------------------
 */

/* Registers Segment Display hardware for use */
s8 nullifyBadge_segDisplayRegister(struct t_nullifyBadge *badge) {
    if (badge->registeredHw & HW_SEG_DISPLAY) {
        return -1;
    }
    else {
        badge->registeredHw |= (1 << HW_SEG_DISPLAY);
        return 0;
    }
}

/* Sets brightness of Segment Display */
void nullifyBadge_segDisplaySetBrightness(u8 brightness) {
    PWM5_LoadDutyValue(gamma_table_256x1k[brightness]);
}

/* Releases the Segment Display hardware from use */
void nullifyBadge_segDisplayRelease(struct t_nullifyBadge *badge) {
    badge->registeredHw &= ~(1 << HW_SEG_DISPLAY);
}

/* Queries the Segment Display hardware to deem if in use or not*/
u8 nullifyBadge_segDisplayIsRegistered(struct t_nullifyBadge *badge) {
    return badge->registeredHw & (1 << HW_SEG_DISPLAY);
}

/* Left shifts a single character onto the display - does not update display */
void nullifyBadge_segDisplayPutChar (struct t_nullifyBadge *badge, char c) {
    displayL2_PutChar(&badge->display, c);
}

void nullifyBadge_segDisplayPutCharPos (struct t_nullifyBadge *badge, char c, u8 pos) {
    displayL1_SetSegChar(&badge->display.display_l1, c, pos);
}

/* Left shifts a single character ontot the display - updates the display*/
void nullifyBadge_segDisplayPrintChar (struct t_nullifyBadge *badge, char c){
    displayL2_PrintChar(&badge->display, c);
}

/* Forces the display to update with current character buffer */
void nullifyBadge_segDisplayForceUpdate (struct t_nullifyBadge *badge) {
    displayL2_ForceUpdate(&badge->display);
}

/* Left shifts a character array onto the display - does not update - will only retain last 4 characters of string */
void nullifyBadge_segDisplayPutStr (struct t_nullifyBadge *badge, char *str) {
    displayL2_PutStr(&badge->display, str);
}

/* Left shifts a character array onto the display - updates display - will only retain last 4 characters of string */
void nullifyBadge_segDisplayPrintStr (struct t_nullifyBadge *badge, char *str) {
    displayL2_PrintStr(&badge->display, str);
}

/* Erases the segment display - forces an update with space characters */
void nullifyBadge_segDisplayErase (struct t_nullifyBadge *badge) {
    displayL2_EraseSegDisplay(&badge->display);
}

/* 
 * -----------------------------------------------------------------------------
 * API Functions for User LEDs 
 * -----------------------------------------------------------------------------
 */
/* Registers User LED hardware for use */
s8 nullifyBadge_userLedsRegister (struct t_nullifyBadge *badge) {
    if (badge->registeredHw & HW_USER_LEDS) {
        return -1;
    }
    else {
        badge->registeredHw |= (1 << HW_USER_LEDS);
        return 0;
    }
}

/* Releases the User LED hardware from use */
void nullifyBadge_userLedsRelease (struct t_nullifyBadge *badge) {
    badge->registeredHw &= ~(1 << HW_USER_LEDS);
}

/* Queries the User LED hardware to deem if in use or not*/
u8 nullifyBadge_userLedsAreRegistered(struct t_nullifyBadge *badge) {
    return badge->registeredHw & (1 << HW_USER_LEDS);
}

/* Sets brightness of User LEDs*/
void nullifyBadge_userLedsSetBrightness(u8 brightness) {
    PWM6_LoadDutyValue(gamma_table_256x1k[brightness]);
}

/* Reads and returns current state of User LEDs */
u16  nullifyBadge_userLedsGet (struct t_nullifyBadge *badge) {
    return badge->display.ledVect;
}

/* Sets data to the User LED vector */
void nullifyBadge_userLedsSet (struct t_nullifyBadge *badge, u16 userLedData) {
    displayL2_SetUserLeds(&badge->display, userLedData);
}

/* Clears all User LEDs */
void nullifyBadge_userLedsClr (struct t_nullifyBadge *badge) {
    displayL2_ClrUserLeds(&badge->display);
}

/* 
 * -----------------------------------------------------------------------------
 * API Functions for buttons 
 * -----------------------------------------------------------------------------
 */
/* Reads the current state of the buttons */
u8 nullifyBadge_buttonsGet() {
    u8 retVal = 0x0F;
    
    retVal &= ~(USER_BTN_A_GetValue() << BUTTON_A);
    retVal &= ~(USER_BTN_B_GetValue() << BUTTON_B);
    retVal &= ~(USER_BTN_X_GetValue() << BUTTON_X);
    retVal &= ~(USER_BTN_Y_GetValue() << BUTTON_Y);
    
    return retVal;
}

/* Reads the current state Button A*/
u8 nullifyBadge_buttonAGet() {
    u8 retVal = 0x1;
    retVal &= ~USER_BTN_A_GetValue();
    return retVal;
}

/* Reads the current state Button B*/
u8 nullifyBadge_buttonBGet() {
    u8 retVal = 0x1;
    retVal &= ~USER_BTN_B_GetValue();
    return retVal;
}

/* Reads the current state Button X*/
u8 nullifyBadge_buttonXGet() {
    u8 retVal = 0x1;
    retVal &= ~USER_BTN_X_GetValue();
    return retVal;
}

/* Reads the current state Button Y*/
u8 nullifyBadge_buttonYGet() {
    u8 retVal = 0x1;
    retVal &= ~USER_BTN_Y_GetValue();
    return retVal;
}

/* 
 * -----------------------------------------------------------------------------
 * API Functions for Infrared 38 kHz Receiver
 * -----------------------------------------------------------------------------
 */
/* Reads the current state of the IR receiver */
u8 nullifyBadge_irGet() {
    return IR_RXD_GetValue();
}

/* 
 * -----------------------------------------------------------------------------
 * API Functions for Infrared Transmitter
 * -----------------------------------------------------------------------------
 */
/* Registers IR Tx hardware for use */
s8   nullifyBadge_irTxRegister(struct t_nullifyBadge *badge) {
    if (badge->registeredHw & HW_IR_TX) {
        return -1;
    }
    else {
        badge->registeredHw |= (1 << HW_IR_TX);
        return 0;
    }
}


/* Releases the IR Tx hardware from use */
void nullifyBadge_irTxRelease(struct t_nullifyBadge *badge) {
    badge->registeredHw &= ~(1 << HW_IR_TX);
}

/* Queries the IR Tx hardware to deem if in use or not*/
u8   nullifyBadge_irTxIsRegistered(struct t_nullifyBadge *badge) {
    return badge->registeredHw & (1 << HW_IR_TX);
}

/* Sets the Infrared LED */
void nullifyBadge_irTxSet() {
    /* The IR LED is active LOW signal */
    IR_TXD_N_SetLow();
}

/* Clears the Infrared LED */
void nullifyBadge_irTxClr() {
    /* The IR LED is active LOW signal */
    IR_TXD_N_SetHigh();
}

/* 
 * -----------------------------------------------------------------------------
 * API Functions for EEPROM
 * -----------------------------------------------------------------------------
 */
/* Registers EEPROM hardware for use */
s8   nullifyBadge_eepromRegister(struct t_nullifyBadge *badge) {
    if (badge->registeredHw & HW_EEPROM) {
        return -1;
    }
    else {
        badge->registeredHw |= (1 << HW_EEPROM);
        return 0;
    }
}

/* Releases the EEPROM hardware from use */
void nullifyBadge_eepromRelease(struct t_nullifyBadge *badge) {
    badge->registeredHw &= ~(1 << HW_EEPROM);
}

/* Queries the EEPROM hardware to deem if in use or not*/
u8   nullifyBadge_eepromRegistered(struct t_nullifyBadge *badge) {
    return badge->registeredHw & (1 << HW_EEPROM);
}

/* Performs 8bit write to EEPROM */
void nullifyBadge_eepromWrite8bit(u16 addr, u8 data) {
    DATAEE_WriteByte(addr, data);
}

/* Performs 16bit write to EEPROM*/
void nullifyBadge_eepromWrite16bit(u16 addr, u16 data) {
    /* First write lower byte to lower location */
    DATAEE_WriteByte(addr, (u8) (data & 0xFF));
    
    /* Increment address and shift data */
    addr++;
    data >>= 8;
    
    /* Write upper byte to upper location */
    DATAEE_WriteByte(addr, (u8) data);
    
}

/* Performs 8bit read from EEPROM */
u8 nullifyBadge_eepromRead8bit(u16 addr) {
    return (u8) DATAEE_ReadByte(addr);
}


/* Performs 16bit read from EEPROM */
u16 nullifyBadge_eepromRead16bit(u16 addr) {
    u16 retVal;
    /* First read lower byte */
    retVal = DATAEE_ReadByte(addr);
    
    /* Increment address */
    addr++;
    
    retVal |= (DATAEE_ReadByte(addr) << 8);
    
    return retVal;
}



