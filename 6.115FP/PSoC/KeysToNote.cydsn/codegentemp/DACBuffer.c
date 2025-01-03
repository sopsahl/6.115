/*******************************************************************************
* File Name: DACBuffer.c
* Version 1.90
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer) 
*  Component.
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

uint8 DACBuffer_initVar = 0u;


/*******************************************************************************   
* Function Name: DACBuffer_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  DACBuffer_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void DACBuffer_Init(void) 
{
    DACBuffer_SetPower(DACBuffer_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: DACBuffer_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void DACBuffer_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    DACBuffer_PUMP_CR1_REG  |= (DACBuffer_PUMP_CR1_CLKSEL | DACBuffer_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    DACBuffer_PM_ACT_CFG_REG |= DACBuffer_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    DACBuffer_PM_STBY_CFG_REG |= DACBuffer_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   DACBuffer_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and 
*  sets the power to the given level. A power level of 0, is same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  DACBuffer_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void DACBuffer_Start(void) 
{
    if(DACBuffer_initVar == 0u)
    {
        DACBuffer_initVar = 1u;
        DACBuffer_Init();
    }

    DACBuffer_Enable();
}


/*******************************************************************************
* Function Name: DACBuffer_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void DACBuffer_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    DACBuffer_PM_ACT_CFG_REG &= (uint8)(~DACBuffer_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    DACBuffer_PM_STBY_CFG_REG &= (uint8)(~DACBuffer_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(DACBuffer_PM_ACT_CFG_REG == 0u)
    {
        DACBuffer_PUMP_CR1_REG &= (uint8)(~(DACBuffer_PUMP_CR1_CLKSEL | DACBuffer_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: DACBuffer_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters: 
*  power: PSoC3: Sets power level between low (1) and high power (3).
*         PSoC5: Sets power level High (0)
*
* Return:
*  void
*
**********************************************************************************/
void DACBuffer_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        DACBuffer_CR_REG &= (uint8)(~DACBuffer_PWR_MASK);
        DACBuffer_CR_REG |= power & DACBuffer_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(DACBuffer_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
