/*******************************************************************************
* File Name: Wave_Out_PM.c
* Version 2.10
*
* Description:
*  This file provides the power management source code to the API for the
*  DVDAC component.
*
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Wave_Out.h"
#include "Wave_Out_VDAC8.h"

static Wave_Out_BACKUP_STRUCT  Wave_Out_backup;


/*******************************************************************************
* Function Name: Wave_Out_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The
*  Wave_Out_Sleep() API saves the current component state. Then it
*  calls the Wave_Out_Stop() function and calls
*  Wave_Out_SaveConfig() to save the hardware configuration. Call the
*  Wave_Out_Sleep() function before calling the CyPmSleep() or the
*  CyPmHibernate() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void Wave_Out_Sleep(void) 
{
    /* Save VDAC8's enable state */
    if(0u != (Wave_Out_VDAC8_PWRMGR & Wave_Out_VDAC8_ACT_PWR_EN))
    {
        Wave_Out_backup.enableState = 1u;
    }
    else
    {
        Wave_Out_backup.enableState = 0u;
    }

    Wave_Out_Stop();
    Wave_Out_SaveConfig();
}


/*******************************************************************************
* Function Name: Wave_Out_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when
*  Wave_Out_Sleep() was called. The Wave_Out_Wakeup() function
*  calls the Wave_Out_RestoreConfig() function to restore the
*  configuration. If the component was enabled before the
*  Wave_Out_Sleep() function was called, the DVDAC_Wakeup() function
*  will also re-enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void Wave_Out_Wakeup(void) 
{
    Wave_Out_RestoreConfig();

    if(Wave_Out_backup.enableState == 1u)
    {
        Wave_Out_Enable();
    }
}


/*******************************************************************************
* Function Name: Wave_Out_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and non-retention registers.
*  This function is called by the Wave_Out_Sleep() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void Wave_Out_SaveConfig(void) 
{
    Wave_Out_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: Wave_Out_RestoreConfig
********************************************************************************
*
* Summary:
*  This function restores the component configuration and non-retention
*  registers. This function is called by the Wave_Out_Wakeup() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void Wave_Out_RestoreConfig(void) 
{
    Wave_Out_VDAC8_RestoreConfig();
}


/* [] END OF FILE */
