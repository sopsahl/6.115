/*******************************************************************************
* File Name: UpdateNote.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_UpdateNote_H)
#define CY_TIMER_UpdateNote_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 UpdateNote_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define UpdateNote_Resolution                 32u
#define UpdateNote_UsingFixedFunction         0u
#define UpdateNote_UsingHWCaptureCounter      0u
#define UpdateNote_SoftwareCaptureMode        0u
#define UpdateNote_SoftwareTriggerMode        0u
#define UpdateNote_UsingHWEnable              0u
#define UpdateNote_EnableTriggerMode          0u
#define UpdateNote_InterruptOnCaptureCount    0u
#define UpdateNote_RunModeUsed                0u
#define UpdateNote_ControlRegRemoved          0u

#if defined(UpdateNote_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define UpdateNote_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (UpdateNote_UsingFixedFunction)
    #define UpdateNote_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define UpdateNote_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End UpdateNote_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!UpdateNote_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (UpdateNote_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!UpdateNote_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}UpdateNote_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    UpdateNote_Start(void) ;
void    UpdateNote_Stop(void) ;

void    UpdateNote_SetInterruptMode(uint8 interruptMode) ;
uint8   UpdateNote_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define UpdateNote_GetInterruptSource() UpdateNote_ReadStatusRegister()

#if(!UpdateNote_UDB_CONTROL_REG_REMOVED)
    uint8   UpdateNote_ReadControlRegister(void) ;
    void    UpdateNote_WriteControlRegister(uint8 control) ;
#endif /* (!UpdateNote_UDB_CONTROL_REG_REMOVED) */

uint32  UpdateNote_ReadPeriod(void) ;
void    UpdateNote_WritePeriod(uint32 period) ;
uint32  UpdateNote_ReadCounter(void) ;
void    UpdateNote_WriteCounter(uint32 counter) ;
uint32  UpdateNote_ReadCapture(void) ;
void    UpdateNote_SoftwareCapture(void) ;

#if(!UpdateNote_UsingFixedFunction) /* UDB Prototypes */
    #if (UpdateNote_SoftwareCaptureMode)
        void    UpdateNote_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!UpdateNote_UsingFixedFunction) */

    #if (UpdateNote_SoftwareTriggerMode)
        void    UpdateNote_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (UpdateNote_SoftwareTriggerMode) */

    #if (UpdateNote_EnableTriggerMode)
        void    UpdateNote_EnableTrigger(void) ;
        void    UpdateNote_DisableTrigger(void) ;
    #endif /* (UpdateNote_EnableTriggerMode) */


    #if(UpdateNote_InterruptOnCaptureCount)
        void    UpdateNote_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (UpdateNote_InterruptOnCaptureCount) */

    #if (UpdateNote_UsingHWCaptureCounter)
        void    UpdateNote_SetCaptureCount(uint8 captureCount) ;
        uint8   UpdateNote_ReadCaptureCount(void) ;
    #endif /* (UpdateNote_UsingHWCaptureCounter) */

    void UpdateNote_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void UpdateNote_Init(void)          ;
void UpdateNote_Enable(void)        ;
void UpdateNote_SaveConfig(void)    ;
void UpdateNote_RestoreConfig(void) ;
void UpdateNote_Sleep(void)         ;
void UpdateNote_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define UpdateNote__B_TIMER__CM_NONE 0
#define UpdateNote__B_TIMER__CM_RISINGEDGE 1
#define UpdateNote__B_TIMER__CM_FALLINGEDGE 2
#define UpdateNote__B_TIMER__CM_EITHEREDGE 3
#define UpdateNote__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define UpdateNote__B_TIMER__TM_NONE 0x00u
#define UpdateNote__B_TIMER__TM_RISINGEDGE 0x04u
#define UpdateNote__B_TIMER__TM_FALLINGEDGE 0x08u
#define UpdateNote__B_TIMER__TM_EITHEREDGE 0x0Cu
#define UpdateNote__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define UpdateNote_INIT_PERIOD             23999999u
#define UpdateNote_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << UpdateNote_CTRL_CAP_MODE_SHIFT))
#define UpdateNote_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << UpdateNote_CTRL_TRIG_MODE_SHIFT))
#if (UpdateNote_UsingFixedFunction)
    #define UpdateNote_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << UpdateNote_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << UpdateNote_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define UpdateNote_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << UpdateNote_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << UpdateNote_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << UpdateNote_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (UpdateNote_UsingFixedFunction) */
#define UpdateNote_INIT_CAPTURE_COUNT      (2u)
#define UpdateNote_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << UpdateNote_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (UpdateNote_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define UpdateNote_STATUS         (*(reg8 *) UpdateNote_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define UpdateNote_STATUS_MASK    (*(reg8 *) UpdateNote_TimerHW__SR0 )
    #define UpdateNote_CONTROL        (*(reg8 *) UpdateNote_TimerHW__CFG0)
    #define UpdateNote_CONTROL2       (*(reg8 *) UpdateNote_TimerHW__CFG1)
    #define UpdateNote_CONTROL2_PTR   ( (reg8 *) UpdateNote_TimerHW__CFG1)
    #define UpdateNote_RT1            (*(reg8 *) UpdateNote_TimerHW__RT1)
    #define UpdateNote_RT1_PTR        ( (reg8 *) UpdateNote_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define UpdateNote_CONTROL3       (*(reg8 *) UpdateNote_TimerHW__CFG2)
        #define UpdateNote_CONTROL3_PTR   ( (reg8 *) UpdateNote_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define UpdateNote_GLOBAL_ENABLE  (*(reg8 *) UpdateNote_TimerHW__PM_ACT_CFG)
    #define UpdateNote_GLOBAL_STBY_ENABLE  (*(reg8 *) UpdateNote_TimerHW__PM_STBY_CFG)

    #define UpdateNote_CAPTURE_LSB         (* (reg16 *) UpdateNote_TimerHW__CAP0 )
    #define UpdateNote_CAPTURE_LSB_PTR       ((reg16 *) UpdateNote_TimerHW__CAP0 )
    #define UpdateNote_PERIOD_LSB          (* (reg16 *) UpdateNote_TimerHW__PER0 )
    #define UpdateNote_PERIOD_LSB_PTR        ((reg16 *) UpdateNote_TimerHW__PER0 )
    #define UpdateNote_COUNTER_LSB         (* (reg16 *) UpdateNote_TimerHW__CNT_CMP0 )
    #define UpdateNote_COUNTER_LSB_PTR       ((reg16 *) UpdateNote_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define UpdateNote_BLOCK_EN_MASK                     UpdateNote_TimerHW__PM_ACT_MSK
    #define UpdateNote_BLOCK_STBY_EN_MASK                UpdateNote_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define UpdateNote_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define UpdateNote_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define UpdateNote_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define UpdateNote_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define UpdateNote_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define UpdateNote_CTRL_ENABLE                        ((uint8)((uint8)0x01u << UpdateNote_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define UpdateNote_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define UpdateNote_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << UpdateNote_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define UpdateNote_CTRL_MODE_SHIFT                 0x01u
        #define UpdateNote_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << UpdateNote_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define UpdateNote_CTRL_RCOD_SHIFT        0x02u
        #define UpdateNote_CTRL_ENBL_SHIFT        0x00u
        #define UpdateNote_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define UpdateNote_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << UpdateNote_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define UpdateNote_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << UpdateNote_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define UpdateNote_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << UpdateNote_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define UpdateNote_CTRL_RCOD       ((uint8)((uint8)0x03u << UpdateNote_CTRL_RCOD_SHIFT))
        #define UpdateNote_CTRL_ENBL       ((uint8)((uint8)0x80u << UpdateNote_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define UpdateNote_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define UpdateNote_RT1_MASK                        ((uint8)((uint8)0x03u << UpdateNote_RT1_SHIFT))
    #define UpdateNote_SYNC                            ((uint8)((uint8)0x03u << UpdateNote_RT1_SHIFT))
    #define UpdateNote_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define UpdateNote_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << UpdateNote_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define UpdateNote_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << UpdateNote_SYNCDSI_SHIFT))

    #define UpdateNote_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << UpdateNote_CTRL_MODE_SHIFT))
    #define UpdateNote_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << UpdateNote_CTRL_MODE_SHIFT))
    #define UpdateNote_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << UpdateNote_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define UpdateNote_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define UpdateNote_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define UpdateNote_STATUS_TC_INT_MASK_SHIFT        (UpdateNote_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define UpdateNote_STATUS_CAPTURE_INT_MASK_SHIFT   (UpdateNote_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define UpdateNote_STATUS_TC                       ((uint8)((uint8)0x01u << UpdateNote_STATUS_TC_SHIFT))
    #define UpdateNote_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << UpdateNote_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define UpdateNote_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << UpdateNote_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define UpdateNote_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << UpdateNote_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define UpdateNote_STATUS              (* (reg8 *) UpdateNote_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define UpdateNote_STATUS_MASK         (* (reg8 *) UpdateNote_TimerUDB_rstSts_stsreg__MASK_REG)
    #define UpdateNote_STATUS_AUX_CTRL     (* (reg8 *) UpdateNote_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define UpdateNote_CONTROL             (* (reg8 *) UpdateNote_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(UpdateNote_Resolution <= 8u) /* 8-bit Timer */
        #define UpdateNote_CAPTURE_LSB         (* (reg8 *) UpdateNote_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define UpdateNote_CAPTURE_LSB_PTR       ((reg8 *) UpdateNote_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define UpdateNote_PERIOD_LSB          (* (reg8 *) UpdateNote_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define UpdateNote_PERIOD_LSB_PTR        ((reg8 *) UpdateNote_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define UpdateNote_COUNTER_LSB         (* (reg8 *) UpdateNote_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define UpdateNote_COUNTER_LSB_PTR       ((reg8 *) UpdateNote_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(UpdateNote_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define UpdateNote_CAPTURE_LSB         (* (reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define UpdateNote_CAPTURE_LSB_PTR       ((reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define UpdateNote_PERIOD_LSB          (* (reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define UpdateNote_PERIOD_LSB_PTR        ((reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define UpdateNote_COUNTER_LSB         (* (reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define UpdateNote_COUNTER_LSB_PTR       ((reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define UpdateNote_CAPTURE_LSB         (* (reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define UpdateNote_CAPTURE_LSB_PTR       ((reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define UpdateNote_PERIOD_LSB          (* (reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define UpdateNote_PERIOD_LSB_PTR        ((reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define UpdateNote_COUNTER_LSB         (* (reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define UpdateNote_COUNTER_LSB_PTR       ((reg16 *) UpdateNote_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(UpdateNote_Resolution <= 24u)/* 24-bit Timer */
        #define UpdateNote_CAPTURE_LSB         (* (reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define UpdateNote_CAPTURE_LSB_PTR       ((reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define UpdateNote_PERIOD_LSB          (* (reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define UpdateNote_PERIOD_LSB_PTR        ((reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define UpdateNote_COUNTER_LSB         (* (reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define UpdateNote_COUNTER_LSB_PTR       ((reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define UpdateNote_CAPTURE_LSB         (* (reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define UpdateNote_CAPTURE_LSB_PTR       ((reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define UpdateNote_PERIOD_LSB          (* (reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define UpdateNote_PERIOD_LSB_PTR        ((reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define UpdateNote_COUNTER_LSB         (* (reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define UpdateNote_COUNTER_LSB_PTR       ((reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define UpdateNote_CAPTURE_LSB         (* (reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define UpdateNote_CAPTURE_LSB_PTR       ((reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define UpdateNote_PERIOD_LSB          (* (reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define UpdateNote_PERIOD_LSB_PTR        ((reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define UpdateNote_COUNTER_LSB         (* (reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define UpdateNote_COUNTER_LSB_PTR       ((reg32 *) UpdateNote_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define UpdateNote_COUNTER_LSB_PTR_8BIT       ((reg8 *) UpdateNote_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (UpdateNote_UsingHWCaptureCounter)
        #define UpdateNote_CAP_COUNT              (*(reg8 *) UpdateNote_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define UpdateNote_CAP_COUNT_PTR          ( (reg8 *) UpdateNote_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define UpdateNote_CAPTURE_COUNT_CTRL     (*(reg8 *) UpdateNote_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define UpdateNote_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) UpdateNote_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (UpdateNote_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define UpdateNote_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define UpdateNote_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define UpdateNote_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define UpdateNote_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define UpdateNote_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define UpdateNote_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << UpdateNote_CTRL_INTCNT_SHIFT))
    #define UpdateNote_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << UpdateNote_CTRL_TRIG_MODE_SHIFT))
    #define UpdateNote_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << UpdateNote_CTRL_TRIG_EN_SHIFT))
    #define UpdateNote_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << UpdateNote_CTRL_CAP_MODE_SHIFT))
    #define UpdateNote_CTRL_ENABLE                    ((uint8)((uint8)0x01u << UpdateNote_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define UpdateNote_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define UpdateNote_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define UpdateNote_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define UpdateNote_STATUS_TC_INT_MASK_SHIFT       UpdateNote_STATUS_TC_SHIFT
    #define UpdateNote_STATUS_CAPTURE_INT_MASK_SHIFT  UpdateNote_STATUS_CAPTURE_SHIFT
    #define UpdateNote_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define UpdateNote_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define UpdateNote_STATUS_FIFOFULL_INT_MASK_SHIFT UpdateNote_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define UpdateNote_STATUS_TC                      ((uint8)((uint8)0x01u << UpdateNote_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define UpdateNote_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << UpdateNote_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define UpdateNote_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << UpdateNote_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define UpdateNote_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << UpdateNote_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define UpdateNote_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << UpdateNote_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define UpdateNote_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << UpdateNote_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define UpdateNote_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << UpdateNote_STATUS_FIFOFULL_SHIFT))

    #define UpdateNote_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define UpdateNote_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define UpdateNote_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define UpdateNote_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define UpdateNote_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define UpdateNote_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_UpdateNote_H */


/* [] END OF FILE */
