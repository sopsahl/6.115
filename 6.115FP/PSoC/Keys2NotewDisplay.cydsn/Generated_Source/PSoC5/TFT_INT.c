/*******************************************************************************
* File Name: TFT_INT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TFT_PVT.h"
#include "cyapicallbacks.h"

/* User code required at start of ISR */
/* `#START TFT_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: TFT_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  TFT_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  TFT_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  TFT_txBuffer[TFT_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(TFT_TX_ISR)
{
    #if(TFT_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (TFT_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef TFT_TX_ISR_ENTRY_CALLBACK
        TFT_TX_ISR_EntryCallback();
    #endif /* TFT_TX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START TFT_TX_ISR_START` */

    /* `#END` */
    
    #if(TFT_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(TFT_txBufferRead != TFT_txBufferWrite)
        {
            tmpStatus = TFT_GET_STATUS_TX(TFT_swStatusTx);
            TFT_swStatusTx = tmpStatus;

            if(0u != (TFT_swStatusTx & TFT_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == TFT_txBufferFull)
                {
                   TFT_txBufferRead++;

                    if(TFT_txBufferRead >= TFT_TX_BUFFER_SIZE)
                    {
                        TFT_txBufferRead = 0u;
                    }
                }
                else
                {
                    TFT_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG8(TFT_TXDATA_PTR, 
                                             TFT_txBuffer[TFT_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(TFT_txBufferRead == TFT_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            TFT_TX_STATUS_MASK_REG &= ((uint8) ~TFT_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (TFT_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START TFT_TX_ISR_END` */

    /* `#END` */
    
    #ifdef TFT_TX_ISR_EXIT_CALLBACK
        TFT_TX_ISR_ExitCallback();
    #endif /* TFT_TX_ISR_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: TFT_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  TFT_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  TFT_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  TFT_rxBuffer[TFT_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(TFT_RX_ISR)
{
    #if(TFT_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (TFT_RX_SOFTWARE_BUF_ENABLED) */

    #ifdef TFT_RX_ISR_ENTRY_CALLBACK
        TFT_RX_ISR_EntryCallback();
    #endif /* TFT_RX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START TFT_RX_ISR_START` */

    /* `#END` */
    
    #if(TFT_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = TFT_GET_STATUS_RX(TFT_swStatusRx);
        TFT_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (TFT_swStatusRx & TFT_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG8(TFT_RXDATA_PTR);

            /* Set next pointer. */
            TFT_rxBufferWrite++;
            if(TFT_rxBufferWrite >= TFT_RX_BUFFER_SIZE)
            {
                TFT_rxBufferWrite = 0u;
            }

            if(TFT_rxBufferWrite == TFT_rxBufferRead)
            {
                TFT_rxBufferRead++;
                if(TFT_rxBufferRead >= TFT_RX_BUFFER_SIZE)
                {
                    TFT_rxBufferRead = 0u;
                }

                TFT_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            TFT_rxBuffer[TFT_rxBufferWrite] = rxData;

            tmpStatus = TFT_GET_STATUS_RX(TFT_swStatusRx);
            TFT_swStatusRx = tmpStatus;
        }

    #endif /* (TFT_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START TFT_RX_ISR_END` */

    /* `#END` */
    
    #ifdef TFT_RX_ISR_EXIT_CALLBACK
        TFT_RX_ISR_ExitCallback();
    #endif /* TFT_RX_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
