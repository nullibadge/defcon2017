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
#ifndef NULLIFYBADGE_DISPLAYL2_H
#define	NULLIFYBADGE_DISPLAYL2_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include "xc8_types.h"
#include "mcc_generated_files/mcc.h"
#include "nullifyBadge_displayL1.h"

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


/* Level 2 Display API */
struct t_nullifyDisplay_l2 {
    char charVect[4];
    u8   dpVect;
    u16  ledVect;
    
    struct t_nullifyDisplay_l1 display_l1;
    
};

void displayL2_Initialize (struct t_nullifyDisplay_l2 *display);
void displayL2_PutChar (struct t_nullifyDisplay_l2 *display, char c);
void displayL2_PrintChar (struct t_nullifyDisplay_l2 *display, char c);
void displayL2_ForceUpdate (struct t_nullifyDisplay_l2 *display);
void displayL2_PutStr (struct t_nullifyDisplay_l2 *display, char *str);
void displayL2_PrintStr (struct t_nullifyDisplay_l2 *display, char *str);
void displayL2_EraseSegDisplay (struct t_nullifyDisplay_l2 *display);
void displayL2_SetUserLeds (struct t_nullifyDisplay_l2 *display, u16 userLedData);
void displayL2_ClrUserLeds (struct t_nullifyDisplay_l2 *display);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* NULLIFYBADGE_DISPLAYL2_H */

