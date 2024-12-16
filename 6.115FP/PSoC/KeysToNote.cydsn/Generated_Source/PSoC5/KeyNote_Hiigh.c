/*******************************************************************************
* File Name: KeyNote_Hiigh.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "KeyNote_Hiigh.h"

#if !defined(KeyNote_Hiigh_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: KeyNote_Hiigh_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 KeyNote_Hiigh_Read(void) 
{ 
    return KeyNote_Hiigh_Status;
}


/*******************************************************************************
* Function Name: KeyNote_Hiigh_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void KeyNote_Hiigh_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    KeyNote_Hiigh_Status_Aux_Ctrl |= KeyNote_Hiigh_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: KeyNote_Hiigh_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void KeyNote_Hiigh_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    KeyNote_Hiigh_Status_Aux_Ctrl &= (uint8)(~KeyNote_Hiigh_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: KeyNote_Hiigh_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void KeyNote_Hiigh_WriteMask(uint8 mask) 
{
    #if(KeyNote_Hiigh_INPUTS < 8u)
    	mask &= ((uint8)(1u << KeyNote_Hiigh_INPUTS) - 1u);
	#endif /* End KeyNote_Hiigh_INPUTS < 8u */
    KeyNote_Hiigh_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: KeyNote_Hiigh_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 KeyNote_Hiigh_ReadMask(void) 
{
    return KeyNote_Hiigh_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
