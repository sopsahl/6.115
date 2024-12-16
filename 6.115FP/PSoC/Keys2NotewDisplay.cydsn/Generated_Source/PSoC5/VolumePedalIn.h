/*******************************************************************************
* File Name: VolumePedalIn.h  
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

#if !defined(CY_PINS_VolumePedalIn_H) /* Pins VolumePedalIn_H */
#define CY_PINS_VolumePedalIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VolumePedalIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VolumePedalIn__PORT == 15 && ((VolumePedalIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VolumePedalIn_Write(uint8 value);
void    VolumePedalIn_SetDriveMode(uint8 mode);
uint8   VolumePedalIn_ReadDataReg(void);
uint8   VolumePedalIn_Read(void);
void    VolumePedalIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   VolumePedalIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VolumePedalIn_SetDriveMode() function.
     *  @{
     */
        #define VolumePedalIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VolumePedalIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VolumePedalIn_DM_RES_UP          PIN_DM_RES_UP
        #define VolumePedalIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define VolumePedalIn_DM_OD_LO           PIN_DM_OD_LO
        #define VolumePedalIn_DM_OD_HI           PIN_DM_OD_HI
        #define VolumePedalIn_DM_STRONG          PIN_DM_STRONG
        #define VolumePedalIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VolumePedalIn_MASK               VolumePedalIn__MASK
#define VolumePedalIn_SHIFT              VolumePedalIn__SHIFT
#define VolumePedalIn_WIDTH              1u

/* Interrupt constants */
#if defined(VolumePedalIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VolumePedalIn_SetInterruptMode() function.
     *  @{
     */
        #define VolumePedalIn_INTR_NONE      (uint16)(0x0000u)
        #define VolumePedalIn_INTR_RISING    (uint16)(0x0001u)
        #define VolumePedalIn_INTR_FALLING   (uint16)(0x0002u)
        #define VolumePedalIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VolumePedalIn_INTR_MASK      (0x01u) 
#endif /* (VolumePedalIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VolumePedalIn_PS                     (* (reg8 *) VolumePedalIn__PS)
/* Data Register */
#define VolumePedalIn_DR                     (* (reg8 *) VolumePedalIn__DR)
/* Port Number */
#define VolumePedalIn_PRT_NUM                (* (reg8 *) VolumePedalIn__PRT) 
/* Connect to Analog Globals */                                                  
#define VolumePedalIn_AG                     (* (reg8 *) VolumePedalIn__AG)                       
/* Analog MUX bux enable */
#define VolumePedalIn_AMUX                   (* (reg8 *) VolumePedalIn__AMUX) 
/* Bidirectional Enable */                                                        
#define VolumePedalIn_BIE                    (* (reg8 *) VolumePedalIn__BIE)
/* Bit-mask for Aliased Register Access */
#define VolumePedalIn_BIT_MASK               (* (reg8 *) VolumePedalIn__BIT_MASK)
/* Bypass Enable */
#define VolumePedalIn_BYP                    (* (reg8 *) VolumePedalIn__BYP)
/* Port wide control signals */                                                   
#define VolumePedalIn_CTL                    (* (reg8 *) VolumePedalIn__CTL)
/* Drive Modes */
#define VolumePedalIn_DM0                    (* (reg8 *) VolumePedalIn__DM0) 
#define VolumePedalIn_DM1                    (* (reg8 *) VolumePedalIn__DM1)
#define VolumePedalIn_DM2                    (* (reg8 *) VolumePedalIn__DM2) 
/* Input Buffer Disable Override */
#define VolumePedalIn_INP_DIS                (* (reg8 *) VolumePedalIn__INP_DIS)
/* LCD Common or Segment Drive */
#define VolumePedalIn_LCD_COM_SEG            (* (reg8 *) VolumePedalIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define VolumePedalIn_LCD_EN                 (* (reg8 *) VolumePedalIn__LCD_EN)
/* Slew Rate Control */
#define VolumePedalIn_SLW                    (* (reg8 *) VolumePedalIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VolumePedalIn_PRTDSI__CAPS_SEL       (* (reg8 *) VolumePedalIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VolumePedalIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VolumePedalIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VolumePedalIn_PRTDSI__OE_SEL0        (* (reg8 *) VolumePedalIn__PRTDSI__OE_SEL0) 
#define VolumePedalIn_PRTDSI__OE_SEL1        (* (reg8 *) VolumePedalIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VolumePedalIn_PRTDSI__OUT_SEL0       (* (reg8 *) VolumePedalIn__PRTDSI__OUT_SEL0) 
#define VolumePedalIn_PRTDSI__OUT_SEL1       (* (reg8 *) VolumePedalIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VolumePedalIn_PRTDSI__SYNC_OUT       (* (reg8 *) VolumePedalIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VolumePedalIn__SIO_CFG)
    #define VolumePedalIn_SIO_HYST_EN        (* (reg8 *) VolumePedalIn__SIO_HYST_EN)
    #define VolumePedalIn_SIO_REG_HIFREQ     (* (reg8 *) VolumePedalIn__SIO_REG_HIFREQ)
    #define VolumePedalIn_SIO_CFG            (* (reg8 *) VolumePedalIn__SIO_CFG)
    #define VolumePedalIn_SIO_DIFF           (* (reg8 *) VolumePedalIn__SIO_DIFF)
#endif /* (VolumePedalIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(VolumePedalIn__INTSTAT)
    #define VolumePedalIn_INTSTAT            (* (reg8 *) VolumePedalIn__INTSTAT)
    #define VolumePedalIn_SNAP               (* (reg8 *) VolumePedalIn__SNAP)
    
	#define VolumePedalIn_0_INTTYPE_REG 		(* (reg8 *) VolumePedalIn__0__INTTYPE)
#endif /* (VolumePedalIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VolumePedalIn_H */


/* [] END OF FILE */
