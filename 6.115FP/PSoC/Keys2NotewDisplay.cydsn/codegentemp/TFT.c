/*******************************************************************************
* File Name: TFT.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the SPI Master component.
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

#if(TFT_TX_SOFTWARE_BUF_ENABLED)
    volatile uint8 TFT_txBuffer[TFT_TX_BUFFER_SIZE];
    volatile uint8 TFT_txBufferFull;
    volatile uint8 TFT_txBufferRead;
    volatile uint8 TFT_txBufferWrite;
#endif /* (TFT_TX_SOFTWARE_BUF_ENABLED) */

#if(TFT_RX_SOFTWARE_BUF_ENABLED)
    volatile uint8 TFT_rxBuffer[TFT_RX_BUFFER_SIZE];
    volatile uint8 TFT_rxBufferFull;
    volatile uint8 TFT_rxBufferRead;
    volatile uint8 TFT_rxBufferWrite;
#endif /* (TFT_RX_SOFTWARE_BUF_ENABLED) */

uint8 TFT_initVar = 0u;

volatile uint8 TFT_swStatusTx;
volatile uint8 TFT_swStatusRx;


/*******************************************************************************
* Function Name: TFT_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default SPIM configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  When this function is called it initializes all of the necessary parameters
*  for execution. i.e. setting the initial interrupt mask, configuring the
*  interrupt service routine, configuring the bit-counter parameters and
*  clearing the FIFO and Status Register.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_Init(void) 
{
    /* Initialize the Bit counter */
    TFT_COUNTER_PERIOD_REG = TFT_BITCTR_INIT;

    /* Init TX ISR  */
    #if(0u != TFT_INTERNAL_TX_INT_ENABLED)
        CyIntDisable         (TFT_TX_ISR_NUMBER);
        CyIntSetPriority     (TFT_TX_ISR_NUMBER,  TFT_TX_ISR_PRIORITY);
        (void) CyIntSetVector(TFT_TX_ISR_NUMBER, &TFT_TX_ISR);
    #endif /* (0u != TFT_INTERNAL_TX_INT_ENABLED) */

    /* Init RX ISR  */
    #if(0u != TFT_INTERNAL_RX_INT_ENABLED)
        CyIntDisable         (TFT_RX_ISR_NUMBER);
        CyIntSetPriority     (TFT_RX_ISR_NUMBER,  TFT_RX_ISR_PRIORITY);
        (void) CyIntSetVector(TFT_RX_ISR_NUMBER, &TFT_RX_ISR);
    #endif /* (0u != TFT_INTERNAL_RX_INT_ENABLED) */

    /* Clear any stray data from the RX and TX FIFO */
    TFT_ClearFIFO();

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

    (void) TFT_ReadTxStatus(); /* Clear Tx status and swStatusTx */
    (void) TFT_ReadRxStatus(); /* Clear Rx status and swStatusRx */

    /* Configure TX and RX interrupt mask */
    TFT_TX_STATUS_MASK_REG = TFT_TX_INIT_INTERRUPTS_MASK;
    TFT_RX_STATUS_MASK_REG = TFT_RX_INIT_INTERRUPTS_MASK;
}


/*******************************************************************************
* Function Name: TFT_Enable
********************************************************************************
*
* Summary:
*  Enable SPIM component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void TFT_Enable(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    TFT_COUNTER_CONTROL_REG |= TFT_CNTR_ENABLE;
    TFT_TX_STATUS_ACTL_REG  |= TFT_INT_ENABLE;
    TFT_RX_STATUS_ACTL_REG  |= TFT_INT_ENABLE;
    CyExitCriticalSection(enableInterrupts);

    #if(0u != TFT_INTERNAL_CLOCK)
        TFT_IntClock_Enable();
    #endif /* (0u != TFT_INTERNAL_CLOCK) */

    TFT_EnableTxInt();
    TFT_EnableRxInt();
}


/*******************************************************************************
* Function Name: TFT_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the SPI Master component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  TFT_initVar - used to check initial configuration, modified on
*  first function call.
*
* Theory:
*  Enable the clock input to enable operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_Start(void) 
{
    if(0u == TFT_initVar)
    {
        TFT_Init();
        TFT_initVar = 1u;
    }

    TFT_Enable();
}


/*******************************************************************************
* Function Name: TFT_Stop
********************************************************************************
*
* Summary:
*  Disable the SPI Master component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the clock input to enable operation.
*
*******************************************************************************/
void TFT_Stop(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    TFT_TX_STATUS_ACTL_REG &= ((uint8) ~TFT_INT_ENABLE);
    TFT_RX_STATUS_ACTL_REG &= ((uint8) ~TFT_INT_ENABLE);
    CyExitCriticalSection(enableInterrupts);

    #if(0u != TFT_INTERNAL_CLOCK)
        TFT_IntClock_Disable();
    #endif /* (0u != TFT_INTERNAL_CLOCK) */

    TFT_DisableTxInt();
    TFT_DisableRxInt();
}


/*******************************************************************************
* Function Name: TFT_EnableTxInt
********************************************************************************
*
* Summary:
*  Enable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void TFT_EnableTxInt(void) 
{
    #if(0u != TFT_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(TFT_TX_ISR_NUMBER);
    #endif /* (0u != TFT_INTERNAL_TX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: TFT_EnableRxInt
********************************************************************************
*
* Summary:
*  Enable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void TFT_EnableRxInt(void) 
{
    #if(0u != TFT_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(TFT_RX_ISR_NUMBER);
    #endif /* (0u != TFT_INTERNAL_RX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: TFT_DisableTxInt
********************************************************************************
*
* Summary:
*  Disable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void TFT_DisableTxInt(void) 
{
    #if(0u != TFT_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(TFT_TX_ISR_NUMBER);
    #endif /* (0u != TFT_INTERNAL_TX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: TFT_DisableRxInt
********************************************************************************
*
* Summary:
*  Disable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void TFT_DisableRxInt(void) 
{
    #if(0u != TFT_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(TFT_RX_ISR_NUMBER);
    #endif /* (0u != TFT_INTERNAL_RX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: TFT_SetTxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void TFT_SetTxInterruptMode(uint8 intSrc) 
{
    TFT_TX_STATUS_MASK_REG = intSrc;
}


/*******************************************************************************
* Function Name: TFT_SetRxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void TFT_SetRxInterruptMode(uint8 intSrc) 
{
    TFT_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: TFT_ReadTxStatus
********************************************************************************
*
* Summary:
*  Read the Tx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Tx status register.
*
* Global variables:
*  TFT_swStatusTx - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Tx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 TFT_ReadTxStatus(void) 
{
    uint8 tmpStatus;

    #if(TFT_TX_SOFTWARE_BUF_ENABLED)
        /* Disable TX interrupt to protect global veriables */
        TFT_DisableTxInt();

        tmpStatus = TFT_GET_STATUS_TX(TFT_swStatusTx);
        TFT_swStatusTx = 0u;

        TFT_EnableTxInt();

    #else

        tmpStatus = TFT_TX_STATUS_REG;

    #endif /* (TFT_TX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: TFT_ReadRxStatus
********************************************************************************
*
* Summary:
*  Read the Rx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Rx status register.
*
* Global variables:
*  TFT_swStatusRx - used to store in software Rx status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Rx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Rx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 TFT_ReadRxStatus(void) 
{
    uint8 tmpStatus;

    #if(TFT_RX_SOFTWARE_BUF_ENABLED)
        /* Disable RX interrupt to protect global veriables */
        TFT_DisableRxInt();

        tmpStatus = TFT_GET_STATUS_RX(TFT_swStatusRx);
        TFT_swStatusRx = 0u;

        TFT_EnableRxInt();

    #else

        tmpStatus = TFT_RX_STATUS_REG;

    #endif /* (TFT_RX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: TFT_WriteTxData
********************************************************************************
*
* Summary:
*  Write a byte of data to be sent across the SPI.
*
* Parameters:
*  txDataByte: The data value to send across the SPI.
*
* Return:
*  None.
*
* Global variables:
*  TFT_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call if TX Software Buffer is used.
*  TFT_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*  TFT_txBuffer[TFT_TX_BUFFER_SIZE] - used to store
*  data to sending, modified every function call if TX Software Buffer is used.
*
* Theory:
*  Allows the user to transmit any byte of data in a single transfer.
*
* Side Effects:
*  If this function is called again before the previous byte is finished then
*  the next byte will be appended to the transfer with no time between
*  the byte transfers. Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_WriteTxData(uint8 txData) 
{
    #if(TFT_TX_SOFTWARE_BUF_ENABLED)

        uint8 tempStatus;
        uint8 tmpTxBufferRead;

        /* Block if TX buffer is FULL: don't overwrite */
        do
        {
            tmpTxBufferRead = TFT_txBufferRead;
            if(0u == tmpTxBufferRead)
            {
                tmpTxBufferRead = (TFT_TX_BUFFER_SIZE - 1u);
            }
            else
            {
                tmpTxBufferRead--;
            }

        }while(tmpTxBufferRead == TFT_txBufferWrite);

        /* Disable TX interrupt to protect global veriables */
        TFT_DisableTxInt();

        tempStatus = TFT_GET_STATUS_TX(TFT_swStatusTx);
        TFT_swStatusTx = tempStatus;


        if((TFT_txBufferRead == TFT_txBufferWrite) &&
           (0u != (TFT_swStatusTx & TFT_STS_TX_FIFO_NOT_FULL)))
        {
            /* Put data element into the TX FIFO */
            CY_SET_REG8(TFT_TXDATA_PTR, txData);
        }
        else
        {
            /* Add to the TX software buffer */
            TFT_txBufferWrite++;
            if(TFT_txBufferWrite >= TFT_TX_BUFFER_SIZE)
            {
                TFT_txBufferWrite = 0u;
            }

            if(TFT_txBufferWrite == TFT_txBufferRead)
            {
                TFT_txBufferRead++;
                if(TFT_txBufferRead >= TFT_TX_BUFFER_SIZE)
                {
                    TFT_txBufferRead = 0u;
                }
                TFT_txBufferFull = 1u;
            }

            TFT_txBuffer[TFT_txBufferWrite] = txData;

            TFT_TX_STATUS_MASK_REG |= TFT_STS_TX_FIFO_NOT_FULL;
        }

        TFT_EnableTxInt();

    #else
        /* Wait until TX FIFO has a place */
        while(0u == (TFT_TX_STATUS_REG & TFT_STS_TX_FIFO_NOT_FULL))
        {
        }

        /* Put data element into the TX FIFO */
        CY_SET_REG8(TFT_TXDATA_PTR, txData);

    #endif /* (TFT_TX_SOFTWARE_BUF_ENABLED) */
}


/*******************************************************************************
* Function Name: TFT_ReadRxData
********************************************************************************
*
* Summary:
*  Read the next byte of data received across the SPI.
*
* Parameters:
*  None.
*
* Return:
*  The next byte of data read from the FIFO.
*
* Global variables:
*  TFT_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  TFT_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function
*  call if RX Software Buffer is used.
*  TFT_rxBuffer[TFT_RX_BUFFER_SIZE] - used to store
*  received data.
*
* Theory:
*  Allows the user to read a byte of data received.
*
* Side Effects:
*  Will return invalid data if the FIFO is empty. The user should Call
*  GetRxBufferSize() and if it returns a non-zero value then it is safe to call
*  ReadByte() function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 TFT_ReadRxData(void) 
{
    uint8 rxData;

    #if(TFT_RX_SOFTWARE_BUF_ENABLED)

        /* Disable RX interrupt to protect global veriables */
        TFT_DisableRxInt();

        if(TFT_rxBufferRead != TFT_rxBufferWrite)
        {
            if(0u == TFT_rxBufferFull)
            {
                TFT_rxBufferRead++;
                if(TFT_rxBufferRead >= TFT_RX_BUFFER_SIZE)
                {
                    TFT_rxBufferRead = 0u;
                }
            }
            else
            {
                TFT_rxBufferFull = 0u;
            }
        }

        rxData = TFT_rxBuffer[TFT_rxBufferRead];

        TFT_EnableRxInt();

    #else

        rxData = CY_GET_REG8(TFT_RXDATA_PTR);

    #endif /* (TFT_RX_SOFTWARE_BUF_ENABLED) */

    return(rxData);
}


/*******************************************************************************
* Function Name: TFT_GetRxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the RX buffer.
*  If RX Software Buffer not used then function return 0 if FIFO empty or 1 if
*  FIFO not empty. In another case function return size of RX Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the RX buffer.
*
* Global variables:
*  TFT_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  TFT_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8 TFT_GetRxBufferSize(void) 
{
    uint8 size;

    #if(TFT_RX_SOFTWARE_BUF_ENABLED)

        /* Disable RX interrupt to protect global veriables */
        TFT_DisableRxInt();

        if(TFT_rxBufferRead == TFT_rxBufferWrite)
        {
            size = 0u;
        }
        else if(TFT_rxBufferRead < TFT_rxBufferWrite)
        {
            size = (TFT_rxBufferWrite - TFT_rxBufferRead);
        }
        else
        {
            size = (TFT_RX_BUFFER_SIZE - TFT_rxBufferRead) + TFT_rxBufferWrite;
        }

        TFT_EnableRxInt();

    #else

        /* We can only know if there is data in the RX FIFO */
        size = (0u != (TFT_RX_STATUS_REG & TFT_STS_RX_FIFO_NOT_EMPTY)) ? 1u : 0u;

    #endif /* (TFT_TX_SOFTWARE_BUF_ENABLED) */

    return(size);
}


/*******************************************************************************
* Function Name: TFT_GetTxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the TX buffer.
*  If TX Software Buffer not used then function return 0 - if FIFO empty, 1 - if
*  FIFO not full, 4 - if FIFO full. In another case function return size of TX
*  Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the TX buffer.
*
* Global variables:
*  TFT_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  TFT_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8  TFT_GetTxBufferSize(void) 
{
    uint8 size;

    #if(TFT_TX_SOFTWARE_BUF_ENABLED)
        /* Disable TX interrupt to protect global veriables */
        TFT_DisableTxInt();

        if(TFT_txBufferRead == TFT_txBufferWrite)
        {
            size = 0u;
        }
        else if(TFT_txBufferRead < TFT_txBufferWrite)
        {
            size = (TFT_txBufferWrite - TFT_txBufferRead);
        }
        else
        {
            size = (TFT_TX_BUFFER_SIZE - TFT_txBufferRead) + TFT_txBufferWrite;
        }

        TFT_EnableTxInt();

    #else

        size = TFT_TX_STATUS_REG;

        if(0u != (size & TFT_STS_TX_FIFO_EMPTY))
        {
            size = 0u;
        }
        else if(0u != (size & TFT_STS_TX_FIFO_NOT_FULL))
        {
            size = 1u;
        }
        else
        {
            size = TFT_FIFO_SIZE;
        }

    #endif /* (TFT_TX_SOFTWARE_BUF_ENABLED) */

    return(size);
}


/*******************************************************************************
* Function Name: TFT_ClearRxBuffer
********************************************************************************
*
* Summary:
*  Clear the RX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  TFT_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer, modified every function
*  call - resets to zero.
*  TFT_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any received data not read from the RAM buffer will be lost when overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_ClearRxBuffer(void) 
{
    /* Clear Hardware RX FIFO */
    while(0u !=(TFT_RX_STATUS_REG & TFT_STS_RX_FIFO_NOT_EMPTY))
    {
        (void) CY_GET_REG8(TFT_RXDATA_PTR);
    }

    #if(TFT_RX_SOFTWARE_BUF_ENABLED)
        /* Disable RX interrupt to protect global veriables */
        TFT_DisableRxInt();

        TFT_rxBufferFull  = 0u;
        TFT_rxBufferRead  = 0u;
        TFT_rxBufferWrite = 0u;

        TFT_EnableRxInt();
    #endif /* (TFT_RX_SOFTWARE_BUF_ENABLED) */
}


/*******************************************************************************
* Function Name: TFT_ClearTxBuffer
********************************************************************************
*
* Summary:
*  Clear the TX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  TFT_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call - resets to zero.
*  TFT_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any data not yet transmitted from the RAM buffer will be lost when
*  overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_ClearTxBuffer(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    /* Clear TX FIFO */
    TFT_AUX_CONTROL_DP0_REG |= ((uint8)  TFT_TX_FIFO_CLR);
    TFT_AUX_CONTROL_DP0_REG &= ((uint8) ~TFT_TX_FIFO_CLR);

    #if(TFT_USE_SECOND_DATAPATH)
        /* Clear TX FIFO for 2nd Datapath */
        TFT_AUX_CONTROL_DP1_REG |= ((uint8)  TFT_TX_FIFO_CLR);
        TFT_AUX_CONTROL_DP1_REG &= ((uint8) ~TFT_TX_FIFO_CLR);
    #endif /* (TFT_USE_SECOND_DATAPATH) */
    CyExitCriticalSection(enableInterrupts);

    #if(TFT_TX_SOFTWARE_BUF_ENABLED)
        /* Disable TX interrupt to protect global veriables */
        TFT_DisableTxInt();

        TFT_txBufferFull  = 0u;
        TFT_txBufferRead  = 0u;
        TFT_txBufferWrite = 0u;

        /* Buffer is EMPTY: disable TX FIFO NOT FULL interrupt */
        TFT_TX_STATUS_MASK_REG &= ((uint8) ~TFT_STS_TX_FIFO_NOT_FULL);

        TFT_EnableTxInt();
    #endif /* (TFT_TX_SOFTWARE_BUF_ENABLED) */
}


#if(0u != TFT_BIDIRECTIONAL_MODE)
    /*******************************************************************************
    * Function Name: TFT_TxEnable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI master is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to transmit.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void TFT_TxEnable(void) 
    {
        TFT_CONTROL_REG |= TFT_CTRL_TX_SIGNAL_EN;
    }


    /*******************************************************************************
    * Function Name: TFT_TxDisable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI master is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to receive.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void TFT_TxDisable(void) 
    {
        TFT_CONTROL_REG &= ((uint8) ~TFT_CTRL_TX_SIGNAL_EN);
    }

#endif /* (0u != TFT_BIDIRECTIONAL_MODE) */


/*******************************************************************************
* Function Name: TFT_PutArray
********************************************************************************
*
* Summary:
*  Write available data from ROM/RAM to the TX buffer while space is available
*  in the TX buffer. Keep trying until all data is passed to the TX buffer.
*
* Parameters:
*  *buffer: Pointer to the location in RAM containing the data to send
*  byteCount: The number of bytes to move to the transmit buffer.
*
* Return:
*  None.
*
* Side Effects:
*  Will stay in this routine until all data has been sent.  May get locked in
*  this loop if data is not being initiated by the master if there is not
*  enough room in the TX FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_PutArray(const uint8 buffer[], uint8 byteCount)
                                                                          
{
    uint8 bufIndex;

    bufIndex = 0u;

    while(byteCount > 0u)
    {
        TFT_WriteTxData(buffer[bufIndex]);
        bufIndex++;
        byteCount--;
    }
}


/*******************************************************************************
* Function Name: TFT_ClearFIFO
********************************************************************************
*
* Summary:
*  Clear the RX and TX FIFO's of all data for a fresh start.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
void TFT_ClearFIFO(void) 
{
    uint8 enableInterrupts;

    /* Clear Hardware RX FIFO */
    while(0u !=(TFT_RX_STATUS_REG & TFT_STS_RX_FIFO_NOT_EMPTY))
    {
        (void) CY_GET_REG8(TFT_RXDATA_PTR);
    }

    enableInterrupts = CyEnterCriticalSection();
    /* Clear TX FIFO */
    TFT_AUX_CONTROL_DP0_REG |= ((uint8)  TFT_TX_FIFO_CLR);
    TFT_AUX_CONTROL_DP0_REG &= ((uint8) ~TFT_TX_FIFO_CLR);

    #if(TFT_USE_SECOND_DATAPATH)
        /* Clear TX FIFO for 2nd Datapath */
        TFT_AUX_CONTROL_DP1_REG |= ((uint8)  TFT_TX_FIFO_CLR);
        TFT_AUX_CONTROL_DP1_REG &= ((uint8) ~TFT_TX_FIFO_CLR);
    #endif /* (TFT_USE_SECOND_DATAPATH) */
    CyExitCriticalSection(enableInterrupts);
}


/* Following functions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects.
*/


/*******************************************************************************
* Function Name: TFT_EnableInt
********************************************************************************
*
* Summary:
*  Enable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void TFT_EnableInt(void) 
{
    TFT_EnableRxInt();
    TFT_EnableTxInt();
}


/*******************************************************************************
* Function Name: TFT_DisableInt
********************************************************************************
*
* Summary:
*  Disable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void TFT_DisableInt(void) 
{
    TFT_DisableTxInt();
    TFT_DisableRxInt();
}


/*******************************************************************************
* Function Name: TFT_SetInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void TFT_SetInterruptMode(uint8 intSrc) 
{
    TFT_TX_STATUS_MASK_REG  = (intSrc & ((uint8) ~TFT_STS_SPI_IDLE));
    TFT_RX_STATUS_MASK_REG  =  intSrc;
}


/*******************************************************************************
* Function Name: TFT_ReadStatus
********************************************************************************
*
* Summary:
*  Read the status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the status register.
*
* Global variables:
*  TFT_swStatus - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the status register for error detection
*  and flow control.
*
* Side Effects:
*  Clear status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 TFT_ReadStatus(void) 
{
    uint8 tmpStatus;

    #if(TFT_TX_SOFTWARE_BUF_ENABLED || TFT_RX_SOFTWARE_BUF_ENABLED)

        TFT_DisableInt();

        tmpStatus  = TFT_GET_STATUS_RX(TFT_swStatusRx);
        tmpStatus |= TFT_GET_STATUS_TX(TFT_swStatusTx);
        tmpStatus &= ((uint8) ~TFT_STS_SPI_IDLE);

        TFT_swStatusTx = 0u;
        TFT_swStatusRx = 0u;

        TFT_EnableInt();

    #else

        tmpStatus  = TFT_RX_STATUS_REG;
        tmpStatus |= TFT_TX_STATUS_REG;
        tmpStatus &= ((uint8) ~TFT_STS_SPI_IDLE);

    #endif /* (TFT_TX_SOFTWARE_BUF_ENABLED || TFT_RX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/* [] END OF FILE */
