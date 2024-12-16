/*******************************************************************************
* File Name: NewNote.h
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
#if !defined(CY_ISR_NewNote_H)
#define CY_ISR_NewNote_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void NewNote_Start(void);
void NewNote_StartEx(cyisraddress address);
void NewNote_Stop(void);

CY_ISR_PROTO(NewNote_Interrupt);

void NewNote_SetVector(cyisraddress address);
cyisraddress NewNote_GetVector(void);

void NewNote_SetPriority(uint8 priority);
uint8 NewNote_GetPriority(void);

void NewNote_Enable(void);
uint8 NewNote_GetState(void);
void NewNote_Disable(void);

void NewNote_SetPending(void);
void NewNote_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the NewNote ISR. */
#define NewNote_INTC_VECTOR            ((reg32 *) NewNote__INTC_VECT)

/* Address of the NewNote ISR priority. */
#define NewNote_INTC_PRIOR             ((reg8 *) NewNote__INTC_PRIOR_REG)

/* Priority of the NewNote interrupt. */
#define NewNote_INTC_PRIOR_NUMBER      NewNote__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable NewNote interrupt. */
#define NewNote_INTC_SET_EN            ((reg32 *) NewNote__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the NewNote interrupt. */
#define NewNote_INTC_CLR_EN            ((reg32 *) NewNote__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the NewNote interrupt state to pending. */
#define NewNote_INTC_SET_PD            ((reg32 *) NewNote__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the NewNote interrupt. */
#define NewNote_INTC_CLR_PD            ((reg32 *) NewNote__INTC_CLR_PD_REG)


#endif /* CY_ISR_NewNote_H */


/* [] END OF FILE */
