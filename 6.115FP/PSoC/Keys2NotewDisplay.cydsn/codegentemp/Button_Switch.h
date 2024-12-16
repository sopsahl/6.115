/*******************************************************************************
* File Name: Button_Switch.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Button_Switch_H)
#define CY_ISR_Button_Switch_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Button_Switch_Start(void);
void Button_Switch_StartEx(cyisraddress address);
void Button_Switch_Stop(void);

CY_ISR_PROTO(Button_Switch_Interrupt);

void Button_Switch_SetVector(cyisraddress address);
cyisraddress Button_Switch_GetVector(void);

void Button_Switch_SetPriority(uint8 priority);
uint8 Button_Switch_GetPriority(void);

void Button_Switch_Enable(void);
uint8 Button_Switch_GetState(void);
void Button_Switch_Disable(void);

void Button_Switch_SetPending(void);
void Button_Switch_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Button_Switch ISR. */
#define Button_Switch_INTC_VECTOR            ((reg32 *) Button_Switch__INTC_VECT)

/* Address of the Button_Switch ISR priority. */
#define Button_Switch_INTC_PRIOR             ((reg8 *) Button_Switch__INTC_PRIOR_REG)

/* Priority of the Button_Switch interrupt. */
#define Button_Switch_INTC_PRIOR_NUMBER      Button_Switch__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Button_Switch interrupt. */
#define Button_Switch_INTC_SET_EN            ((reg32 *) Button_Switch__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Button_Switch interrupt. */
#define Button_Switch_INTC_CLR_EN            ((reg32 *) Button_Switch__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Button_Switch interrupt state to pending. */
#define Button_Switch_INTC_SET_PD            ((reg32 *) Button_Switch__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Button_Switch interrupt. */
#define Button_Switch_INTC_CLR_PD            ((reg32 *) Button_Switch__INTC_CLR_PD_REG)


#endif /* CY_ISR_Button_Switch_H */


/* [] END OF FILE */
