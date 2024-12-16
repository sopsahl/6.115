/*******************************************************************************
* File Name: LEDs.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LEDs_ALIASES_H) /* Pins LEDs_ALIASES_H */
#define CY_PINS_LEDs_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define LEDs_0			(LEDs__0__PC)
#define LEDs_0_INTR	((uint16)((uint16)0x0001u << LEDs__0__SHIFT))

#define LEDs_1			(LEDs__1__PC)
#define LEDs_1_INTR	((uint16)((uint16)0x0001u << LEDs__1__SHIFT))

#define LEDs_2			(LEDs__2__PC)
#define LEDs_2_INTR	((uint16)((uint16)0x0001u << LEDs__2__SHIFT))

#define LEDs_3			(LEDs__3__PC)
#define LEDs_3_INTR	((uint16)((uint16)0x0001u << LEDs__3__SHIFT))

#define LEDs_4			(LEDs__4__PC)
#define LEDs_4_INTR	((uint16)((uint16)0x0001u << LEDs__4__SHIFT))

#define LEDs_5			(LEDs__5__PC)
#define LEDs_5_INTR	((uint16)((uint16)0x0001u << LEDs__5__SHIFT))

#define LEDs_6			(LEDs__6__PC)
#define LEDs_6_INTR	((uint16)((uint16)0x0001u << LEDs__6__SHIFT))

#define LEDs_7			(LEDs__7__PC)
#define LEDs_7_INTR	((uint16)((uint16)0x0001u << LEDs__7__SHIFT))

#define LEDs_8			(LEDs__8__PC)
#define LEDs_8_INTR	((uint16)((uint16)0x0001u << LEDs__8__SHIFT))

#define LEDs_9			(LEDs__9__PC)
#define LEDs_9_INTR	((uint16)((uint16)0x0001u << LEDs__9__SHIFT))

#define LEDs_10			(LEDs__10__PC)
#define LEDs_10_INTR	((uint16)((uint16)0x0001u << LEDs__10__SHIFT))

#define LEDs_11			(LEDs__11__PC)
#define LEDs_11_INTR	((uint16)((uint16)0x0001u << LEDs__11__SHIFT))

#define LEDs_12			(LEDs__12__PC)
#define LEDs_12_INTR	((uint16)((uint16)0x0001u << LEDs__12__SHIFT))

#define LEDs_13			(LEDs__13__PC)
#define LEDs_13_INTR	((uint16)((uint16)0x0001u << LEDs__13__SHIFT))

#define LEDs_INTR_ALL	 ((uint16)(LEDs_0_INTR| LEDs_1_INTR| LEDs_2_INTR| LEDs_3_INTR| LEDs_4_INTR| LEDs_5_INTR| LEDs_6_INTR| LEDs_7_INTR| LEDs_8_INTR| LEDs_9_INTR| LEDs_10_INTR| LEDs_11_INTR| LEDs_12_INTR| LEDs_13_INTR))

#endif /* End Pins LEDs_ALIASES_H */


/* [] END OF FILE */
