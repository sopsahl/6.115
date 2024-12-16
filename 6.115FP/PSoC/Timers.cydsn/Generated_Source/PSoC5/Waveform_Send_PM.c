/*******************************************************************************
* File Name: Waveform_Send_PM.c
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

#include "Waveform_Send.h"

static Waveform_Send_backupStruct Waveform_Send_backup;


/*******************************************************************************
* Function Name: Waveform_Send_SaveConfig
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
*  Waveform_Send_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Waveform_Send_SaveConfig(void) 
{
    #if (!Waveform_Send_UsingFixedFunction)
        Waveform_Send_backup.TimerUdb = Waveform_Send_ReadCounter();
        Waveform_Send_backup.InterruptMaskValue = Waveform_Send_STATUS_MASK;
        #if (Waveform_Send_UsingHWCaptureCounter)
            Waveform_Send_backup.TimerCaptureCounter = Waveform_Send_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Waveform_Send_UDB_CONTROL_REG_REMOVED)
            Waveform_Send_backup.TimerControlRegister = Waveform_Send_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Waveform_Send_RestoreConfig
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
*  Waveform_Send_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Waveform_Send_RestoreConfig(void) 
{   
    #if (!Waveform_Send_UsingFixedFunction)

        Waveform_Send_WriteCounter(Waveform_Send_backup.TimerUdb);
        Waveform_Send_STATUS_MASK =Waveform_Send_backup.InterruptMaskValue;
        #if (Waveform_Send_UsingHWCaptureCounter)
            Waveform_Send_SetCaptureCount(Waveform_Send_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Waveform_Send_UDB_CONTROL_REG_REMOVED)
            Waveform_Send_WriteControlRegister(Waveform_Send_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Waveform_Send_Sleep
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
*  Waveform_Send_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Waveform_Send_Sleep(void) 
{
    #if(!Waveform_Send_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Waveform_Send_CTRL_ENABLE == (Waveform_Send_CONTROL & Waveform_Send_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Waveform_Send_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Waveform_Send_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Waveform_Send_Stop();
    Waveform_Send_SaveConfig();
}


/*******************************************************************************
* Function Name: Waveform_Send_Wakeup
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
*  Waveform_Send_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Waveform_Send_Wakeup(void) 
{
    Waveform_Send_RestoreConfig();
    #if(!Waveform_Send_UDB_CONTROL_REG_REMOVED)
        if(Waveform_Send_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Waveform_Send_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
