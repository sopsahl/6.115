/*******************************************************************************
* File Name: Wave_Out.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the DVDAC component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_DVDAC_Wave_Out_H)
#define CY_DVDAC_Wave_Out_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Data Struct Definition
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Wave_Out_BACKUP_STRUCT;

/* Component init state */
extern uint8 Wave_Out_initVar;


/***************************************
*        API constants
***************************************/
#define Wave_Out_RESOLUTION                 (12u)
#define Wave_Out_INTERNAL_CLOCK_USED        (1u)

#define Wave_Out_INTEGER_PORTION_SHIFT      (Wave_Out_RESOLUTION - 8u)
#define Wave_Out_DITHERED_ARRAY_SIZE        ((uint8)(1u << Wave_Out_INTEGER_PORTION_SHIFT))
#define Wave_Out_FRACTIONAL_PORTION_MASK    (Wave_Out_DITHERED_ARRAY_SIZE - 1u)
#define Wave_Out_INTEGER_PORTION_MAX_VALUE  (0xFFu)

/* DMA Configuration */
#define Wave_Out_DMA_BYTES_PER_BURST        (1u)
#define Wave_Out_DMA_REQUEST_PER_BURST      (1u)
#define Wave_Out_DMA_SRC_BASE               (CYDEV_SRAM_BASE)
#define Wave_Out_DMA_DST_BASE               (CYDEV_PERIPH_BASE)


#if   (Wave_Out_RESOLUTION ==  9u)
    #define Wave_Out_DVDAC_MAX_VALUE        (0x1FEu)
#elif (Wave_Out_RESOLUTION == 10u)
    #define Wave_Out_DVDAC_MAX_VALUE        (0x3FCu)
#elif (Wave_Out_RESOLUTION == 11u)
    #define Wave_Out_DVDAC_MAX_VALUE        (0x7F8u)
#else   /* Resolution 12 bits */
    #define Wave_Out_DVDAC_MAX_VALUE        (0xFF0u)
#endif  /* (Wave_Out_RESOLUTION ==  9u) */


/***************************************
*        Function Prototypes
***************************************/

void Wave_Out_Init(void)                ;
void Wave_Out_Enable(void)              ;
void Wave_Out_Start(void)               ;
void Wave_Out_Stop(void)                ;
void Wave_Out_SetValue(uint16 value)    ;
void Wave_Out_Sleep(void)               ;
void Wave_Out_Wakeup(void)              ;
void Wave_Out_SaveConfig(void)          ;
void Wave_Out_RestoreConfig(void)       ;

#endif /* CY_DVDAC_Wave_Out_H */


/* [] END OF FILE */
