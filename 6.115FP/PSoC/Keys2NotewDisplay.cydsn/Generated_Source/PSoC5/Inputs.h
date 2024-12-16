/*******************************************************************************
* File Name: Inputs.h
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
#if !defined(CY_ISR_Inputs_H)
#define CY_ISR_Inputs_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Inputs_Start(void);
void Inputs_StartEx(cyisraddress address);
void Inputs_Stop(void);

CY_ISR_PROTO(Inputs_Interrupt);

void Inputs_SetVector(cyisraddress address);
cyisraddress Inputs_GetVector(void);

void Inputs_SetPriority(uint8 priority);
uint8 Inputs_GetPriority(void);

void Inputs_Enable(void);
uint8 Inputs_GetState(void);
void Inputs_Disable(void);

void Inputs_SetPending(void);
void Inputs_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Inputs ISR. */
#define Inputs_INTC_VECTOR            ((reg32 *) Inputs__INTC_VECT)

/* Address of the Inputs ISR priority. */
#define Inputs_INTC_PRIOR             ((reg8 *) Inputs__INTC_PRIOR_REG)

/* Priority of the Inputs interrupt. */
#define Inputs_INTC_PRIOR_NUMBER      Inputs__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Inputs interrupt. */
#define Inputs_INTC_SET_EN            ((reg32 *) Inputs__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Inputs interrupt. */
#define Inputs_INTC_CLR_EN            ((reg32 *) Inputs__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Inputs interrupt state to pending. */
#define Inputs_INTC_SET_PD            ((reg32 *) Inputs__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Inputs interrupt. */
#define Inputs_INTC_CLR_PD            ((reg32 *) Inputs__INTC_CLR_PD_REG)


#endif /* CY_ISR_Inputs_H */


/* [] END OF FILE */
