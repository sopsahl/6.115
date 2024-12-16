/*******************************************************************************
* File Name: TFT_PM.c
* Version 2.50
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TFT_PVT.h"

static TFT_BACKUP_STRUCT TFT_backup =
{
    TFT_DISABLED,
    TFT_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: TFT_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TFT_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: TFT_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TFT_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: TFT_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TFT_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_Sleep(void) 
{
    /* Save components enable state */
    TFT_backup.enableState = ((uint8) TFT_IS_ENABLED);

    TFT_Stop();
}


/*******************************************************************************
* Function Name: TFT_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TFT_backup - used when non-retention registers are restored.
*  TFT_txBufferWrite - modified every function call - resets to
*  zero.
*  TFT_txBufferRead - modified every function call - resets to
*  zero.
*  TFT_rxBufferWrite - modified every function call - resets to
*  zero.
*  TFT_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_Wakeup(void) 
{
    #if(TFT_RX_SOFTWARE_BUF_ENABLED)
        TFT_rxBufferFull  = 0u;
        TFT_rxBufferRead  = 0u;
        TFT_rxBufferWrite = 0u;
    #endif /* (TFT_RX_SOFTWARE_BUF_ENABLED) */

    #if(TFT_TX_SOFTWARE_BUF_ENABLED)
        TFT_txBufferFull  = 0u;
        TFT_txBufferRead  = 0u;
        TFT_txBufferWrite = 0u;
    #endif /* (TFT_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    TFT_ClearFIFO();

    /* Restore components block enable state */
    if(0u != TFT_backup.enableState)
    {
        TFT_Enable();
    }
}


/* [] END OF FILE */
