/*******************************************************************************
* File Name: KeyNote_Low.c  
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

#include "KeyNote_Low.h"

#if !defined(KeyNote_Low_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: KeyNote_Low_Read
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
uint8 KeyNote_Low_Read(void) 
{ 
    return KeyNote_Low_Status;
}


/*******************************************************************************
* Function Name: KeyNote_Low_InterruptEnable
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
void KeyNote_Low_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    KeyNote_Low_Status_Aux_Ctrl |= KeyNote_Low_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: KeyNote_Low_InterruptDisable
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
void KeyNote_Low_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    KeyNote_Low_Status_Aux_Ctrl &= (uint8)(~KeyNote_Low_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: KeyNote_Low_WriteMask
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
void KeyNote_Low_WriteMask(uint8 mask) 
{
    #if(KeyNote_Low_INPUTS < 8u)
    	mask &= ((uint8)(1u << KeyNote_Low_INPUTS) - 1u);
	#endif /* End KeyNote_Low_INPUTS < 8u */
    KeyNote_Low_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: KeyNote_Low_ReadMask
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
uint8 KeyNote_Low_ReadMask(void) 
{
    return KeyNote_Low_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
