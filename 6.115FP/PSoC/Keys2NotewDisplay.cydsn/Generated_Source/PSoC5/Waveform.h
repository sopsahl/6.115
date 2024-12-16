/*******************************************************************************
* File Name: Waveform.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Waveform_H) /* Pins Waveform_H */
#define CY_PINS_Waveform_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Waveform_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Waveform__PORT == 15 && ((Waveform__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Waveform_Write(uint8 value);
void    Waveform_SetDriveMode(uint8 mode);
uint8   Waveform_ReadDataReg(void);
uint8   Waveform_Read(void);
void    Waveform_SetInterruptMode(uint16 position, uint16 mode);
uint8   Waveform_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Waveform_SetDriveMode() function.
     *  @{
     */
        #define Waveform_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Waveform_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Waveform_DM_RES_UP          PIN_DM_RES_UP
        #define Waveform_DM_RES_DWN         PIN_DM_RES_DWN
        #define Waveform_DM_OD_LO           PIN_DM_OD_LO
        #define Waveform_DM_OD_HI           PIN_DM_OD_HI
        #define Waveform_DM_STRONG          PIN_DM_STRONG
        #define Waveform_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Waveform_MASK               Waveform__MASK
#define Waveform_SHIFT              Waveform__SHIFT
#define Waveform_WIDTH              1u

/* Interrupt constants */
#if defined(Waveform__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Waveform_SetInterruptMode() function.
     *  @{
     */
        #define Waveform_INTR_NONE      (uint16)(0x0000u)
        #define Waveform_INTR_RISING    (uint16)(0x0001u)
        #define Waveform_INTR_FALLING   (uint16)(0x0002u)
        #define Waveform_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Waveform_INTR_MASK      (0x01u) 
#endif /* (Waveform__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Waveform_PS                     (* (reg8 *) Waveform__PS)
/* Data Register */
#define Waveform_DR                     (* (reg8 *) Waveform__DR)
/* Port Number */
#define Waveform_PRT_NUM                (* (reg8 *) Waveform__PRT) 
/* Connect to Analog Globals */                                                  
#define Waveform_AG                     (* (reg8 *) Waveform__AG)                       
/* Analog MUX bux enable */
#define Waveform_AMUX                   (* (reg8 *) Waveform__AMUX) 
/* Bidirectional Enable */                                                        
#define Waveform_BIE                    (* (reg8 *) Waveform__BIE)
/* Bit-mask for Aliased Register Access */
#define Waveform_BIT_MASK               (* (reg8 *) Waveform__BIT_MASK)
/* Bypass Enable */
#define Waveform_BYP                    (* (reg8 *) Waveform__BYP)
/* Port wide control signals */                                                   
#define Waveform_CTL                    (* (reg8 *) Waveform__CTL)
/* Drive Modes */
#define Waveform_DM0                    (* (reg8 *) Waveform__DM0) 
#define Waveform_DM1                    (* (reg8 *) Waveform__DM1)
#define Waveform_DM2                    (* (reg8 *) Waveform__DM2) 
/* Input Buffer Disable Override */
#define Waveform_INP_DIS                (* (reg8 *) Waveform__INP_DIS)
/* LCD Common or Segment Drive */
#define Waveform_LCD_COM_SEG            (* (reg8 *) Waveform__LCD_COM_SEG)
/* Enable Segment LCD */
#define Waveform_LCD_EN                 (* (reg8 *) Waveform__LCD_EN)
/* Slew Rate Control */
#define Waveform_SLW                    (* (reg8 *) Waveform__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Waveform_PRTDSI__CAPS_SEL       (* (reg8 *) Waveform__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Waveform_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Waveform__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Waveform_PRTDSI__OE_SEL0        (* (reg8 *) Waveform__PRTDSI__OE_SEL0) 
#define Waveform_PRTDSI__OE_SEL1        (* (reg8 *) Waveform__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Waveform_PRTDSI__OUT_SEL0       (* (reg8 *) Waveform__PRTDSI__OUT_SEL0) 
#define Waveform_PRTDSI__OUT_SEL1       (* (reg8 *) Waveform__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Waveform_PRTDSI__SYNC_OUT       (* (reg8 *) Waveform__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Waveform__SIO_CFG)
    #define Waveform_SIO_HYST_EN        (* (reg8 *) Waveform__SIO_HYST_EN)
    #define Waveform_SIO_REG_HIFREQ     (* (reg8 *) Waveform__SIO_REG_HIFREQ)
    #define Waveform_SIO_CFG            (* (reg8 *) Waveform__SIO_CFG)
    #define Waveform_SIO_DIFF           (* (reg8 *) Waveform__SIO_DIFF)
#endif /* (Waveform__SIO_CFG) */

/* Interrupt Registers */
#if defined(Waveform__INTSTAT)
    #define Waveform_INTSTAT            (* (reg8 *) Waveform__INTSTAT)
    #define Waveform_SNAP               (* (reg8 *) Waveform__SNAP)
    
	#define Waveform_0_INTTYPE_REG 		(* (reg8 *) Waveform__0__INTTYPE)
#endif /* (Waveform__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Waveform_H */


/* [] END OF FILE */
