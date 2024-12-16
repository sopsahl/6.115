/*******************************************************************************
* File Name: DACBuffer_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "DACBuffer.h"

static DACBuffer_BACKUP_STRUCT  DACBuffer_backup;


/*******************************************************************************  
* Function Name: DACBuffer_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void DACBuffer_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: DACBuffer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void DACBuffer_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: DACBuffer_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DACBuffer_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void DACBuffer_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((DACBuffer_PM_ACT_CFG_REG & DACBuffer_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        DACBuffer_backup.enableState = 1u;
         /* Stops the component */
         DACBuffer_Stop();
    }
    else
    {
        /* Component is disabled */
        DACBuffer_backup.enableState = 0u;
    }
    /* Saves the configuration */
    DACBuffer_SaveConfig();
}


/*******************************************************************************  
* Function Name: DACBuffer_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DACBuffer_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void DACBuffer_Wakeup(void) 
{
    /* Restore the user configuration */
    DACBuffer_RestoreConfig();

    /* Enables the component operation */
    if(DACBuffer_backup.enableState == 1u)
    {
        DACBuffer_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
