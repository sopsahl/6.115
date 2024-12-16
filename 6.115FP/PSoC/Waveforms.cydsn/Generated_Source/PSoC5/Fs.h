/*******************************************************************************
* File Name: Fs.h  
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

#if !defined(CY_PINS_Fs_H) /* Pins Fs_H */
#define CY_PINS_Fs_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Fs_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Fs__PORT == 15 && ((Fs__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Fs_Write(uint8 value);
void    Fs_SetDriveMode(uint8 mode);
uint8   Fs_ReadDataReg(void);
uint8   Fs_Read(void);
void    Fs_SetInterruptMode(uint16 position, uint16 mode);
uint8   Fs_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Fs_SetDriveMode() function.
     *  @{
     */
        #define Fs_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Fs_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Fs_DM_RES_UP          PIN_DM_RES_UP
        #define Fs_DM_RES_DWN         PIN_DM_RES_DWN
        #define Fs_DM_OD_LO           PIN_DM_OD_LO
        #define Fs_DM_OD_HI           PIN_DM_OD_HI
        #define Fs_DM_STRONG          PIN_DM_STRONG
        #define Fs_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Fs_MASK               Fs__MASK
#define Fs_SHIFT              Fs__SHIFT
#define Fs_WIDTH              1u

/* Interrupt constants */
#if defined(Fs__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Fs_SetInterruptMode() function.
     *  @{
     */
        #define Fs_INTR_NONE      (uint16)(0x0000u)
        #define Fs_INTR_RISING    (uint16)(0x0001u)
        #define Fs_INTR_FALLING   (uint16)(0x0002u)
        #define Fs_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Fs_INTR_MASK      (0x01u) 
#endif /* (Fs__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Fs_PS                     (* (reg8 *) Fs__PS)
/* Data Register */
#define Fs_DR                     (* (reg8 *) Fs__DR)
/* Port Number */
#define Fs_PRT_NUM                (* (reg8 *) Fs__PRT) 
/* Connect to Analog Globals */                                                  
#define Fs_AG                     (* (reg8 *) Fs__AG)                       
/* Analog MUX bux enable */
#define Fs_AMUX                   (* (reg8 *) Fs__AMUX) 
/* Bidirectional Enable */                                                        
#define Fs_BIE                    (* (reg8 *) Fs__BIE)
/* Bit-mask for Aliased Register Access */
#define Fs_BIT_MASK               (* (reg8 *) Fs__BIT_MASK)
/* Bypass Enable */
#define Fs_BYP                    (* (reg8 *) Fs__BYP)
/* Port wide control signals */                                                   
#define Fs_CTL                    (* (reg8 *) Fs__CTL)
/* Drive Modes */
#define Fs_DM0                    (* (reg8 *) Fs__DM0) 
#define Fs_DM1                    (* (reg8 *) Fs__DM1)
#define Fs_DM2                    (* (reg8 *) Fs__DM2) 
/* Input Buffer Disable Override */
#define Fs_INP_DIS                (* (reg8 *) Fs__INP_DIS)
/* LCD Common or Segment Drive */
#define Fs_LCD_COM_SEG            (* (reg8 *) Fs__LCD_COM_SEG)
/* Enable Segment LCD */
#define Fs_LCD_EN                 (* (reg8 *) Fs__LCD_EN)
/* Slew Rate Control */
#define Fs_SLW                    (* (reg8 *) Fs__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Fs_PRTDSI__CAPS_SEL       (* (reg8 *) Fs__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Fs_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Fs__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Fs_PRTDSI__OE_SEL0        (* (reg8 *) Fs__PRTDSI__OE_SEL0) 
#define Fs_PRTDSI__OE_SEL1        (* (reg8 *) Fs__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Fs_PRTDSI__OUT_SEL0       (* (reg8 *) Fs__PRTDSI__OUT_SEL0) 
#define Fs_PRTDSI__OUT_SEL1       (* (reg8 *) Fs__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Fs_PRTDSI__SYNC_OUT       (* (reg8 *) Fs__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Fs__SIO_CFG)
    #define Fs_SIO_HYST_EN        (* (reg8 *) Fs__SIO_HYST_EN)
    #define Fs_SIO_REG_HIFREQ     (* (reg8 *) Fs__SIO_REG_HIFREQ)
    #define Fs_SIO_CFG            (* (reg8 *) Fs__SIO_CFG)
    #define Fs_SIO_DIFF           (* (reg8 *) Fs__SIO_DIFF)
#endif /* (Fs__SIO_CFG) */

/* Interrupt Registers */
#if defined(Fs__INTSTAT)
    #define Fs_INTSTAT            (* (reg8 *) Fs__INTSTAT)
    #define Fs_SNAP               (* (reg8 *) Fs__SNAP)
    
	#define Fs_0_INTTYPE_REG 		(* (reg8 *) Fs__0__INTTYPE)
#endif /* (Fs__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Fs_H */


/* [] END OF FILE */
