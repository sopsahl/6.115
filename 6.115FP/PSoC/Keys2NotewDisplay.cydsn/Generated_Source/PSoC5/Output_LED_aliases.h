/*******************************************************************************
* File Name: Output_LED.h  
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

#if !defined(CY_PINS_Output_LED_ALIASES_H) /* Pins Output_LED_ALIASES_H */
#define CY_PINS_Output_LED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Output_LED_0			(Output_LED__0__PC)
#define Output_LED_0_INTR	((uint16)((uint16)0x0001u << Output_LED__0__SHIFT))

#define Output_LED_1			(Output_LED__1__PC)
#define Output_LED_1_INTR	((uint16)((uint16)0x0001u << Output_LED__1__SHIFT))

#define Output_LED_2			(Output_LED__2__PC)
#define Output_LED_2_INTR	((uint16)((uint16)0x0001u << Output_LED__2__SHIFT))

#define Output_LED_3			(Output_LED__3__PC)
#define Output_LED_3_INTR	((uint16)((uint16)0x0001u << Output_LED__3__SHIFT))

#define Output_LED_4			(Output_LED__4__PC)
#define Output_LED_4_INTR	((uint16)((uint16)0x0001u << Output_LED__4__SHIFT))

#define Output_LED_5			(Output_LED__5__PC)
#define Output_LED_5_INTR	((uint16)((uint16)0x0001u << Output_LED__5__SHIFT))

#define Output_LED_6			(Output_LED__6__PC)
#define Output_LED_6_INTR	((uint16)((uint16)0x0001u << Output_LED__6__SHIFT))

#define Output_LED_7			(Output_LED__7__PC)
#define Output_LED_7_INTR	((uint16)((uint16)0x0001u << Output_LED__7__SHIFT))

#define Output_LED_8			(Output_LED__8__PC)
#define Output_LED_8_INTR	((uint16)((uint16)0x0001u << Output_LED__8__SHIFT))

#define Output_LED_9			(Output_LED__9__PC)
#define Output_LED_9_INTR	((uint16)((uint16)0x0001u << Output_LED__9__SHIFT))

#define Output_LED_10			(Output_LED__10__PC)
#define Output_LED_10_INTR	((uint16)((uint16)0x0001u << Output_LED__10__SHIFT))

#define Output_LED_11			(Output_LED__11__PC)
#define Output_LED_11_INTR	((uint16)((uint16)0x0001u << Output_LED__11__SHIFT))

#define Output_LED_12			(Output_LED__12__PC)
#define Output_LED_12_INTR	((uint16)((uint16)0x0001u << Output_LED__12__SHIFT))

#define Output_LED_13			(Output_LED__13__PC)
#define Output_LED_13_INTR	((uint16)((uint16)0x0001u << Output_LED__13__SHIFT))

#define Output_LED_INTR_ALL	 ((uint16)(Output_LED_0_INTR| Output_LED_1_INTR| Output_LED_2_INTR| Output_LED_3_INTR| Output_LED_4_INTR| Output_LED_5_INTR| Output_LED_6_INTR| Output_LED_7_INTR| Output_LED_8_INTR| Output_LED_9_INTR| Output_LED_10_INTR| Output_LED_11_INTR| Output_LED_12_INTR| Output_LED_13_INTR))

#endif /* End Pins Output_LED_ALIASES_H */


/* [] END OF FILE */
