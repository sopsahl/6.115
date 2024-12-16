/*******************************************************************************
* File Name: ReadInputs_PM.c
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

#include "ReadInputs.h"

static ReadInputs_backupStruct ReadInputs_backup;


/*******************************************************************************
* Function Name: ReadInputs_SaveConfig
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
*  ReadInputs_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ReadInputs_SaveConfig(void) 
{
    #if (!ReadInputs_UsingFixedFunction)
        ReadInputs_backup.TimerUdb = ReadInputs_ReadCounter();
        ReadInputs_backup.InterruptMaskValue = ReadInputs_STATUS_MASK;
        #if (ReadInputs_UsingHWCaptureCounter)
            ReadInputs_backup.TimerCaptureCounter = ReadInputs_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!ReadInputs_UDB_CONTROL_REG_REMOVED)
            ReadInputs_backup.TimerControlRegister = ReadInputs_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: ReadInputs_RestoreConfig
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
*  ReadInputs_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ReadInputs_RestoreConfig(void) 
{   
    #if (!ReadInputs_UsingFixedFunction)

        ReadInputs_WriteCounter(ReadInputs_backup.TimerUdb);
        ReadInputs_STATUS_MASK =ReadInputs_backup.InterruptMaskValue;
        #if (ReadInputs_UsingHWCaptureCounter)
            ReadInputs_SetCaptureCount(ReadInputs_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!ReadInputs_UDB_CONTROL_REG_REMOVED)
            ReadInputs_WriteControlRegister(ReadInputs_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: ReadInputs_Sleep
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
*  ReadInputs_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void ReadInputs_Sleep(void) 
{
    #if(!ReadInputs_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(ReadInputs_CTRL_ENABLE == (ReadInputs_CONTROL & ReadInputs_CTRL_ENABLE))
        {
            /* Timer is enabled */
            ReadInputs_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            ReadInputs_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    ReadInputs_Stop();
    ReadInputs_SaveConfig();
}


/*******************************************************************************
* Function Name: ReadInputs_Wakeup
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
*  ReadInputs_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ReadInputs_Wakeup(void) 
{
    ReadInputs_RestoreConfig();
    #if(!ReadInputs_UDB_CONTROL_REG_REMOVED)
        if(ReadInputs_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                ReadInputs_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
