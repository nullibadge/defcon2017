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
  0x0000,
  0x2000, // slot1
  0x1010, // slot2
  0x0020, // slot3
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
  0x0000, // Space
  0x1010, // !
  0x1010, // "
  0x1010, // #
  0x35B4, // $
  0x1010, // %
  0x1010, // &
  0x1010, // '
  0x0808, // (
  0x0202, // )
  0x1E1E, // *
  0x1414, // +
  0x1010, // ,
  0x1010, // -
  0x0040, // .
  0x0802, // /
  0x63A9, // 0
  0x4080, // 1
  0x7031, // 2
  0x60B0, // 3
  0x5190, // 4
  0x31B0, // 5
  0x31B1, // 6
  0x6080, // 7 
  0x71B1, // 8 
  0x7190, // 9
  0x1010, // :
  0x1010, // ; skip 
  0x0808, // <
  0x1030, // =
  0x0202, // >
  0xE114, // ?
  0x1010, // @
  0x7191, // A
  0x11B1, // B
  0x2121, // C
  0x50B1, // D
  0x3121, // E
  0x3101, // F
  0x21B1, // G
  0x5191, // H
  0x2424, // I
  0x40A1, // J
  0x1909, // K
  0x0121, // L
  0x4B81, // M
  0x4389, // N
  0x61A1, // O
  0x7111, // P
  0x61A9, // Q
  0x7119, // R
  0x31B0, // S
  0x2404, // T
  0x41A1, // U
  0x0903, // V
  0x418B, // W
  0x0A0A, // X
  0x0A04, // Y
  0x2822, // Z
  0x2121, // [
  0x0208, // \
  0x60A0, // ]
  0x1010, // ^ skip
  0x0020, // _ 
  0x1010, // ` skip 
  0x7191, // a
  0x11B1, // b
  0x2121, // c
  0x50B1, // d
  0x3121, // e
  0x3101, // f
  0x21B1, // g
  0x5191, // h
  0x2424, // i
  0x40A1, // j
  0x1909, // k
  0x0121, // l
  0x4B81, // m
  0x4389, // n
  0x61A1, // o
  0x7111, // p
  0x61A9, // q
  0x7119, // r
  0x31B0, // s
  0x2404, // t
  0x41A1, // u
  0x0903, // v
  0x418B, // w
  0x0A0A, // x
  0x0A04, // y
  0x2822, // z
  0x1010, // {
  0x0404, // |
  0x1010, // }
  0x1010, // ~
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

