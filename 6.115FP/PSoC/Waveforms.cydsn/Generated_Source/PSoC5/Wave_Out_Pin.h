/*******************************************************************************
* File Name: Wave_Out_Pin.h  
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

#if !defined(CY_PINS_Wave_Out_Pin_H) /* Pins Wave_Out_Pin_H */
#define CY_PINS_Wave_Out_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Wave_Out_Pin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Wave_Out_Pin__PORT == 15 && ((Wave_Out_Pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Wave_Out_Pin_Write(uint8 value);
void    Wave_Out_Pin_SetDriveMode(uint8 mode);
uint8   Wave_Out_Pin_ReadDataReg(void);
uint8   Wave_Out_Pin_Read(void);
void    Wave_Out_Pin_SetInterruptMode(uint16 position, uint16 mode);
uint8   Wave_Out_Pin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Wave_Out_Pin_SetDriveMode() function.
     *  @{
     */
        #define Wave_Out_Pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Wave_Out_Pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Wave_Out_Pin_DM_RES_UP          PIN_DM_RES_UP
        #define Wave_Out_Pin_DM_RES_DWN         PIN_DM_RES_DWN
        #define Wave_Out_Pin_DM_OD_LO           PIN_DM_OD_LO
        #define Wave_Out_Pin_DM_OD_HI           PIN_DM_OD_HI
        #define Wave_Out_Pin_DM_STRONG          PIN_DM_STRONG
        #define Wave_Out_Pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Wave_Out_Pin_MASK               Wave_Out_Pin__MASK
#define Wave_Out_Pin_SHIFT              Wave_Out_Pin__SHIFT
#define Wave_Out_Pin_WIDTH              1u

/* Interrupt constants */
#if defined(Wave_Out_Pin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Wave_Out_Pin_SetInterruptMode() function.
     *  @{
     */
        #define Wave_Out_Pin_INTR_NONE      (uint16)(0x0000u)
        #define Wave_Out_Pin_INTR_RISING    (uint16)(0x0001u)
        #define Wave_Out_Pin_INTR_FALLING   (uint16)(0x0002u)
        #define Wave_Out_Pin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Wave_Out_Pin_INTR_MASK      (0x01u) 
#endif /* (Wave_Out_Pin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Wave_Out_Pin_PS                     (* (reg8 *) Wave_Out_Pin__PS)
/* Data Register */
#define Wave_Out_Pin_DR                     (* (reg8 *) Wave_Out_Pin__DR)
/* Port Number */
#define Wave_Out_Pin_PRT_NUM                (* (reg8 *) Wave_Out_Pin__PRT) 
/* Connect to Analog Globals */                                                  
#define Wave_Out_Pin_AG                     (* (reg8 *) Wave_Out_Pin__AG)                       
/* Analog MUX bux enable */
#define Wave_Out_Pin_AMUX                   (* (reg8 *) Wave_Out_Pin__AMUX) 
/* Bidirectional Enable */                                                        
#define Wave_Out_Pin_BIE                    (* (reg8 *) Wave_Out_Pin__BIE)
/* Bit-mask for Aliased Register Access */
#define Wave_Out_Pin_BIT_MASK               (* (reg8 *) Wave_Out_Pin__BIT_MASK)
/* Bypass Enable */
#define Wave_Out_Pin_BYP                    (* (reg8 *) Wave_Out_Pin__BYP)
/* Port wide control signals */                                                   
#define Wave_Out_Pin_CTL                    (* (reg8 *) Wave_Out_Pin__CTL)
/* Drive Modes */
#define Wave_Out_Pin_DM0                    (* (reg8 *) Wave_Out_Pin__DM0) 
#define Wave_Out_Pin_DM1                    (* (reg8 *) Wave_Out_Pin__DM1)
#define Wave_Out_Pin_DM2                    (* (reg8 *) Wave_Out_Pin__DM2) 
/* Input Buffer Disable Override */
#define Wave_Out_Pin_INP_DIS                (* (reg8 *) Wave_Out_Pin__INP_DIS)
/* LCD Common or Segment Drive */
#define Wave_Out_Pin_LCD_COM_SEG            (* (reg8 *) Wave_Out_Pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define Wave_Out_Pin_LCD_EN                 (* (reg8 *) Wave_Out_Pin__LCD_EN)
/* Slew Rate Control */
#define Wave_Out_Pin_SLW                    (* (reg8 *) Wave_Out_Pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Wave_Out_Pin_PRTDSI__CAPS_SEL       (* (reg8 *) Wave_Out_Pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Wave_Out_Pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Wave_Out_Pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Wave_Out_Pin_PRTDSI__OE_SEL0        (* (reg8 *) Wave_Out_Pin__PRTDSI__OE_SEL0) 
#define Wave_Out_Pin_PRTDSI__OE_SEL1        (* (reg8 *) Wave_Out_Pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Wave_Out_Pin_PRTDSI__OUT_SEL0       (* (reg8 *) Wave_Out_Pin__PRTDSI__OUT_SEL0) 
#define Wave_Out_Pin_PRTDSI__OUT_SEL1       (* (reg8 *) Wave_Out_Pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Wave_Out_Pin_PRTDSI__SYNC_OUT       (* (reg8 *) Wave_Out_Pin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Wave_Out_Pin__SIO_CFG)
    #define Wave_Out_Pin_SIO_HYST_EN        (* (reg8 *) Wave_Out_Pin__SIO_HYST_EN)
    #define Wave_Out_Pin_SIO_REG_HIFREQ     (* (reg8 *) Wave_Out_Pin__SIO_REG_HIFREQ)
    #define Wave_Out_Pin_SIO_CFG            (* (reg8 *) Wave_Out_Pin__SIO_CFG)
    #define Wave_Out_Pin_SIO_DIFF           (* (reg8 *) Wave_Out_Pin__SIO_DIFF)
#endif /* (Wave_Out_Pin__SIO_CFG) */

/* Interrupt Registers */
#if defined(Wave_Out_Pin__INTSTAT)
    #define Wave_Out_Pin_INTSTAT            (* (reg8 *) Wave_Out_Pin__INTSTAT)
    #define Wave_Out_Pin_SNAP               (* (reg8 *) Wave_Out_Pin__SNAP)
    
	#define Wave_Out_Pin_0_INTTYPE_REG 		(* (reg8 *) Wave_Out_Pin__0__INTTYPE)
#endif /* (Wave_Out_Pin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Wave_Out_Pin_H */


/* [] END OF FILE */
