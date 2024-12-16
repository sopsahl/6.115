/*******************************************************************************
* File Name: Wave_Out_VDAC8_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Wave_Out_VDAC8.h"

static Wave_Out_VDAC8_backupStruct Wave_Out_VDAC8_backup;


/*******************************************************************************
* Function Name: Wave_Out_VDAC8_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Wave_Out_VDAC8_SaveConfig(void) 
{
    if (!((Wave_Out_VDAC8_CR1 & Wave_Out_VDAC8_SRC_MASK) == Wave_Out_VDAC8_SRC_UDB))
    {
        Wave_Out_VDAC8_backup.data_value = Wave_Out_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: Wave_Out_VDAC8_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Wave_Out_VDAC8_RestoreConfig(void) 
{
    if (!((Wave_Out_VDAC8_CR1 & Wave_Out_VDAC8_SRC_MASK) == Wave_Out_VDAC8_SRC_UDB))
    {
        if((Wave_Out_VDAC8_Strobe & Wave_Out_VDAC8_STRB_MASK) == Wave_Out_VDAC8_STRB_EN)
        {
            Wave_Out_VDAC8_Strobe &= (uint8)(~Wave_Out_VDAC8_STRB_MASK);
            Wave_Out_VDAC8_Data = Wave_Out_VDAC8_backup.data_value;
            Wave_Out_VDAC8_Strobe |= Wave_Out_VDAC8_STRB_EN;
        }
        else
        {
            Wave_Out_VDAC8_Data = Wave_Out_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Wave_Out_VDAC8_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  Wave_Out_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Wave_Out_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Wave_Out_VDAC8_ACT_PWR_EN == (Wave_Out_VDAC8_PWRMGR & Wave_Out_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Wave_Out_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Wave_Out_VDAC8_backup.enableState = 0u;
    }
    
    Wave_Out_VDAC8_Stop();
    Wave_Out_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: Wave_Out_VDAC8_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Wave_Out_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Wave_Out_VDAC8_Wakeup(void) 
{
    Wave_Out_VDAC8_RestoreConfig();
    
    if(Wave_Out_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Wave_Out_VDAC8_Enable();

        /* Restore the data register */
        Wave_Out_VDAC8_SetValue(Wave_Out_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
