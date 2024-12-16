/*******************************************************************************
* File Name: Wave_Out.c
* Version 2.10
*
* Description:
*  This file provides the source code of APIs for the DVDAC component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Wave_Out.h"
#include "Wave_Out_VDAC8.h"
#include "CyDmac.h"
#include "Wave_Out_DMA_dma.H"

#if(Wave_Out_INTERNAL_CLOCK_USED)
    #include "Wave_Out_IntClock.h"
#endif /* Wave_Out_INTERNAL_CLOCK_USED */


static uint8 Wave_Out_ditheredValues[16u] = {0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 
                                             0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u};


uint8 Wave_Out_initVar = 0u;

static uint8 Wave_Out_dmaChan;
static uint8 Wave_Out_dmaTd = CY_DMA_INVALID_TD;

static void Wave_Out_InitDma(void)  ;


/*******************************************************************************
* Function Name: Wave_Out_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call Wave_Out_Init() because
*  the Wave_Out_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  All registers will be set to values according to the customizer Configure
*  dialog.
*
* Global variables:
*  None
*
*******************************************************************************/
void Wave_Out_Init(void) 
{
    Wave_Out_VDAC8_Init();

    if(CY_DMA_INVALID_TD == Wave_Out_dmaTd)
    {
        Wave_Out_InitDma();
    }
}


/*******************************************************************************
* Function Name: Wave_Out_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary to
*  call Wave_Out_Enable() because the Wave_Out_Start() API calls
*  this function, which is the preferred method to begin component operation.
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
void Wave_Out_Enable(void) 
{
    (void) CyDmaChEnable(Wave_Out_dmaChan, 1u);

    #if(Wave_Out_INTERNAL_CLOCK_USED)
        Wave_Out_IntClock_Start();
    #endif /* Wave_Out_INTERNAL_CLOCK_USED */

    Wave_Out_VDAC8_Enable();
}


/*******************************************************************************
* Function Name: Wave_Out_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables
*  power to the block. The first time the routine is executed, the component is
*  initialized to the configured settings. When called to restart the DVDAC
*  following a Wave_Out_Stop() call, the current component parameter
*  settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Wave_Out_initVar variable is already set, this function only
*  calls the Wave_Out_Enable() function.
*
* Global variables:
*  Wave_Out_initVar - indicates whether the DVDAC has been initialized.
*  The variable is initialized to 0 and set to 1 the first time DVDAC_Start()
*  is called. This allows the component to restart without reinitialization
*  after the first call to the Wave_Out_Start() routine. If
*  reinitialization of the component is required, then the
*  Wave_Out_Init() function can be called before the
*  Wave_Out_Start() or Wave_Out_Enable() function.
*
*******************************************************************************/
void Wave_Out_Start(void) 
{
    /* Hardware initiazation only needs to occure the first time */
    if(0u == Wave_Out_initVar)
    {
        Wave_Out_Init();
        Wave_Out_initVar = 1u;
    }

    Wave_Out_Enable();
}


/*******************************************************************************
* Function Name: Wave_Out_Stop
********************************************************************************
*
* Summary:
*  Stops the component and turns off the analog blocks in the DVDAC.
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
void Wave_Out_Stop(void) 
{
    #if(Wave_Out_INTERNAL_CLOCK_USED)
        Wave_Out_IntClock_Stop();
    #endif /* Wave_Out_INTERNAL_CLOCK_USED */

    (void) CyDmaChDisable(Wave_Out_dmaChan);
    Wave_Out_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: Wave_Out_SetValue
********************************************************************************
*
* Summary:
*  Sets the DVDACs output. The function populates the SRAM array based on the
*  value and the resolution setting. That array is then transferred to the
*  internal VDAC by DMA.
*
* Parameters:
*  (uint16) value:  The maximum value will be dependent on the resolution
*  selected:
*   Resolution       Valid range
*        9 bits       0x0 - 0x1FE
*       10 bits       0x0 - 0x3FC
*       11 bits       0x0 - 0x7F8
*       12 bits       0x0 - 0xFF0
*
*  This value includes an integer portion and a fractional portion that varies
*  depending on number of bits of resolution:
*   - 9-bits:  1 fractional bit
*   - 10-bits: 2 fractional bits
*   - 11-bits: 3 fractional bits
*   - 12-bits: 4 fractional bits
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void Wave_Out_SetValue(uint16 value) 
{
    uint8  lowCount  = (uint8)(value & Wave_Out_FRACTIONAL_PORTION_MASK);
    uint8 highCount  = (uint8)(value >> Wave_Out_INTEGER_PORTION_SHIFT);
    uint8 i;


    CYASSERT(value <= Wave_Out_DVDAC_MAX_VALUE);

    if (Wave_Out_INTEGER_PORTION_MAX_VALUE == highCount)
    {
        for (i = 0u; i < Wave_Out_DITHERED_ARRAY_SIZE; i++)
        {
            Wave_Out_ditheredValues[i] = Wave_Out_INTEGER_PORTION_MAX_VALUE;
        }
    }
    else
    {
        for(i = 0u; i < Wave_Out_DITHERED_ARRAY_SIZE; i++)
        {
            if(i < (Wave_Out_DITHERED_ARRAY_SIZE - lowCount))
            {
                Wave_Out_ditheredValues[i] = highCount;
            }
            else
            {
                Wave_Out_ditheredValues[i] = highCount + 1u;
            }
        }
    }
}


/*******************************************************************************
* Function Name: Wave_Out_InitDma
********************************************************************************
*
* Summary:
*  Configures a DMA transfer of channel values from memory to VDAC.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void Wave_Out_InitDma(void)  
{
    /***************************************************************************
    * Transfers channel values from SRAM to VDAC register. One byte transfer,
    * each burst requires a request.
    ***************************************************************************/
    Wave_Out_dmaChan = Wave_Out_DMA_DmaInitialize(
                                    Wave_Out_DMA_BYTES_PER_BURST,
                                    Wave_Out_DMA_REQUEST_PER_BURST,
                                    HI16(Wave_Out_DMA_SRC_BASE),
                                    HI16(Wave_Out_DMA_DST_BASE));

    Wave_Out_dmaTd = CyDmaTdAllocate();


    /***************************************************************************
    * One TD looping on itself, increment the source address, but not the
    * destination address.
    ***************************************************************************/
    (void) CyDmaTdSetConfiguration( Wave_Out_dmaTd,
                                    Wave_Out_DITHERED_ARRAY_SIZE,
                                    Wave_Out_dmaTd,
                                    (uint8) CY_DMA_TD_INC_SRC_ADR);

    /* Transfers the value for each channel from memory to VDAC */
    (void) CyDmaTdSetAddress(   Wave_Out_dmaTd,
                                LO16((uint32)Wave_Out_ditheredValues),
                                LO16((uint32)Wave_Out_VDAC8_Data_PTR));

    (void) CyDmaChSetInitialTd(Wave_Out_dmaChan, Wave_Out_dmaTd);
}

/* [] END OF FILE */

