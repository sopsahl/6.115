/*******************************************************************************
* File Name: UpdateNote_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "UpdateNote.h"

static UpdateNote_backupStruct UpdateNote_backup;


/*******************************************************************************
* Function Name: UpdateNote_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UpdateNote_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void UpdateNote_SaveConfig(void) 
{
    #if (!UpdateNote_UsingFixedFunction)
        UpdateNote_backup.TimerUdb = UpdateNote_ReadCounter();
        UpdateNote_backup.InterruptMaskValue = UpdateNote_STATUS_MASK;
        #if (UpdateNote_UsingHWCaptureCounter)
            UpdateNote_backup.TimerCaptureCounter = UpdateNote_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!UpdateNote_UDB_CONTROL_REG_REMOVED)
            UpdateNote_backup.TimerControlRegister = UpdateNote_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: UpdateNote_RestoreConfig
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
* Global variables:
*  UpdateNote_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void UpdateNote_RestoreConfig(void) 
{   
    #if (!UpdateNote_UsingFixedFunction)

        UpdateNote_WriteCounter(UpdateNote_backup.TimerUdb);
        UpdateNote_STATUS_MASK =UpdateNote_backup.InterruptMaskValue;
        #if (UpdateNote_UsingHWCaptureCounter)
            UpdateNote_SetCaptureCount(UpdateNote_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!UpdateNote_UDB_CONTROL_REG_REMOVED)
            UpdateNote_WriteControlRegister(UpdateNote_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: UpdateNote_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UpdateNote_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void UpdateNote_Sleep(void) 
{
    #if(!UpdateNote_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(UpdateNote_CTRL_ENABLE == (UpdateNote_CONTROL & UpdateNote_CTRL_ENABLE))
        {
            /* Timer is enabled */
            UpdateNote_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            UpdateNote_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    UpdateNote_Stop();
    UpdateNote_SaveConfig();
}


/*******************************************************************************
* Function Name: UpdateNote_Wakeup
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
*  UpdateNote_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void UpdateNote_Wakeup(void) 
{
    UpdateNote_RestoreConfig();
    #if(!UpdateNote_UDB_CONTROL_REG_REMOVED)
        if(UpdateNote_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                UpdateNote_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
