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
#ifndef NULLIFYBADGE_DISPLAYL1_H
#define	NULLIFYBADGE_DISPLAYL1_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include "xc8_types.h"
#include "mcc_generated_files/mcc.h"
#include <string.h>

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

u16 asciiCharTableLookup[128] = {
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x0000,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1E1E,
  0x1414,
  0x1010,
  0x1010,
  0x0040,
  0x0802,
  0x63A9,
  0x4080,
  0x7031,
  0x60B0,
  0x5190,
  0x31B0,
  0x31B1,
  0x6080,
  0x71B1,
  0x7190,
  0x1010,
  0x1010,
  0x0808,
  0x1010,
  0x0202,
  0x1010,
  0x1010,
  0x7191,
  0x11B1,
  0x2121,
  0x50B1,
  0x3121,
  0x3101,
  0x21B1,
  0x5191,
  0x2424,
  0x40A1,
  0x1909,
  0x0121,
  0x4B81,
  0x4389,
  0x61A1,
  0x7111,
  0x61A9,
  0x7119,
  0x31B0,
  0x2404,
  0x41A1,
  0x0903,
  0x418B,
  0x0A0A,
  0x0A04,
  0x2822,
  0x2121,
  0x0208,
  0x60A0,
  0x1010,
  0x1010,
  0x1010,
  0x7191,
  0x11B1,
  0x2121,
  0x50B1,
  0x3121,
  0x3101,
  0x21B1,
  0x5191,
  0x2424,
  0x40A1,
  0x1909,
  0x0121,
  0x4B81,
  0x4389,
  0x61A1,
  0x7111,
  0x61A9,
  0x7119,
  0x31B0,
  0x2404,
  0x41A1,
  0x0903,
  0x418B,
  0x0A0A,
  0x0A04,
  0x2822,
  0x1010,
  0x1010,
  0x1010,
  0x1010,
  0x1010
};

/* Level 1 Display API */
struct t_nullifyDisplay_l1 {
    u8 displayVect[10];
};

void displayL1_Initialize (struct t_nullifyDisplay_l1 *display);
void displayL1_SetSegChar (struct t_nullifyDisplay_l1 *display, char c, u8 charPos);
void displayL1_SetUserLed (struct t_nullifyDisplay_l1 *display, u16 userLedVect);
void displayL1_SetDp (struct t_nullifyDisplay_l1 *display, u8 displayDpVect);
void displayL1_Update (struct t_nullifyDisplay_l1 *display);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* NULLIFYBADGE_DISPLAYL1_H */

