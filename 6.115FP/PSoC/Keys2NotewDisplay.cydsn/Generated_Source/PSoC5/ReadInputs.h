/*******************************************************************************
* File Name: ReadInputs.h
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

#if !defined(CY_TIMER_ReadInputs_H)
#define CY_TIMER_ReadInputs_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 ReadInputs_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define ReadInputs_Resolution                 16u
#define ReadInputs_UsingFixedFunction         1u
#define ReadInputs_UsingHWCaptureCounter      0u
#define ReadInputs_SoftwareCaptureMode        0u
#define ReadInputs_SoftwareTriggerMode        0u
#define ReadInputs_UsingHWEnable              0u
#define ReadInputs_EnableTriggerMode          0u
#define ReadInputs_InterruptOnCaptureCount    0u
#define ReadInputs_RunModeUsed                0u
#define ReadInputs_ControlRegRemoved          0u

#if defined(ReadInputs_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define ReadInputs_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (ReadInputs_UsingFixedFunction)
    #define ReadInputs_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define ReadInputs_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End ReadInputs_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!ReadInputs_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (ReadInputs_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!ReadInputs_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}ReadInputs_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    ReadInputs_Start(void) ;
void    ReadInputs_Stop(void) ;

void    ReadInputs_SetInterruptMode(uint8 interruptMode) ;
uint8   ReadInputs_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define ReadInputs_GetInterruptSource() ReadInputs_ReadStatusRegister()

#if(!ReadInputs_UDB_CONTROL_REG_REMOVED)
    uint8   ReadInputs_ReadControlRegister(void) ;
    void    ReadInputs_WriteControlRegister(uint8 control) ;
#endif /* (!ReadInputs_UDB_CONTROL_REG_REMOVED) */

uint16  ReadInputs_ReadPeriod(void) ;
void    ReadInputs_WritePeriod(uint16 period) ;
uint16  ReadInputs_ReadCounter(void) ;
void    ReadInputs_WriteCounter(uint16 counter) ;
uint16  ReadInputs_ReadCapture(void) ;
void    ReadInputs_SoftwareCapture(void) ;

#if(!ReadInputs_UsingFixedFunction) /* UDB Prototypes */
    #if (ReadInputs_SoftwareCaptureMode)
        void    ReadInputs_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!ReadInputs_UsingFixedFunction) */

    #if (ReadInputs_SoftwareTriggerMode)
        void    ReadInputs_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (ReadInputs_SoftwareTriggerMode) */

    #if (ReadInputs_EnableTriggerMode)
        void    ReadInputs_EnableTrigger(void) ;
        void    ReadInputs_DisableTrigger(void) ;
    #endif /* (ReadInputs_EnableTriggerMode) */


    #if(ReadInputs_InterruptOnCaptureCount)
        void    ReadInputs_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (ReadInputs_InterruptOnCaptureCount) */

    #if (ReadInputs_UsingHWCaptureCounter)
        void    ReadInputs_SetCaptureCount(uint8 captureCount) ;
        uint8   ReadInputs_ReadCaptureCount(void) ;
    #endif /* (ReadInputs_UsingHWCaptureCounter) */

    void ReadInputs_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void ReadInputs_Init(void)          ;
void ReadInputs_Enable(void)        ;
void ReadInputs_SaveConfig(void)    ;
void ReadInputs_RestoreConfig(void) ;
void ReadInputs_Sleep(void)         ;
void ReadInputs_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define ReadInputs__B_TIMER__CM_NONE 0
#define ReadInputs__B_TIMER__CM_RISINGEDGE 1
#define ReadInputs__B_TIMER__CM_FALLINGEDGE 2
#define ReadInputs__B_TIMER__CM_EITHEREDGE 3
#define ReadInputs__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define ReadInputs__B_TIMER__TM_NONE 0x00u
#define ReadInputs__B_TIMER__TM_RISINGEDGE 0x04u
#define ReadInputs__B_TIMER__TM_FALLINGEDGE 0x08u
#define ReadInputs__B_TIMER__TM_EITHEREDGE 0x0Cu
#define ReadInputs__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define ReadInputs_INIT_PERIOD             23999u
#define ReadInputs_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << ReadInputs_CTRL_CAP_MODE_SHIFT))
#define ReadInputs_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << ReadInputs_CTRL_TRIG_MODE_SHIFT))
#if (ReadInputs_UsingFixedFunction)
    #define ReadInputs_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << ReadInputs_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << ReadInputs_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define ReadInputs_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << ReadInputs_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << ReadInputs_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << ReadInputs_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (ReadInputs_UsingFixedFunction) */
#define ReadInputs_INIT_CAPTURE_COUNT      (2u)
#define ReadInputs_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << ReadInputs_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (ReadInputs_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define ReadInputs_STATUS         (*(reg8 *) ReadInputs_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define ReadInputs_STATUS_MASK    (*(reg8 *) ReadInputs_TimerHW__SR0 )
    #define ReadInputs_CONTROL        (*(reg8 *) ReadInputs_TimerHW__CFG0)
    #define ReadInputs_CONTROL2       (*(reg8 *) ReadInputs_TimerHW__CFG1)
    #define ReadInputs_CONTROL2_PTR   ( (reg8 *) ReadInputs_TimerHW__CFG1)
    #define ReadInputs_RT1            (*(reg8 *) ReadInputs_TimerHW__RT1)
    #define ReadInputs_RT1_PTR        ( (reg8 *) ReadInputs_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define ReadInputs_CONTROL3       (*(reg8 *) ReadInputs_TimerHW__CFG2)
        #define ReadInputs_CONTROL3_PTR   ( (reg8 *) ReadInputs_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define ReadInputs_GLOBAL_ENABLE  (*(reg8 *) ReadInputs_TimerHW__PM_ACT_CFG)
    #define ReadInputs_GLOBAL_STBY_ENABLE  (*(reg8 *) ReadInputs_TimerHW__PM_STBY_CFG)

    #define ReadInputs_CAPTURE_LSB         (* (reg16 *) ReadInputs_TimerHW__CAP0 )
    #define ReadInputs_CAPTURE_LSB_PTR       ((reg16 *) ReadInputs_TimerHW__CAP0 )
    #define ReadInputs_PERIOD_LSB          (* (reg16 *) ReadInputs_TimerHW__PER0 )
    #define ReadInputs_PERIOD_LSB_PTR        ((reg16 *) ReadInputs_TimerHW__PER0 )
    #define ReadInputs_COUNTER_LSB         (* (reg16 *) ReadInputs_TimerHW__CNT_CMP0 )
    #define ReadInputs_COUNTER_LSB_PTR       ((reg16 *) ReadInputs_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define ReadInputs_BLOCK_EN_MASK                     ReadInputs_TimerHW__PM_ACT_MSK
    #define ReadInputs_BLOCK_STBY_EN_MASK                ReadInputs_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define ReadInputs_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define ReadInputs_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define ReadInputs_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define ReadInputs_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define ReadInputs_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define ReadInputs_CTRL_ENABLE                        ((uint8)((uint8)0x01u << ReadInputs_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define ReadInputs_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define ReadInputs_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << ReadInputs_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define ReadInputs_CTRL_MODE_SHIFT                 0x01u
        #define ReadInputs_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << ReadInputs_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define ReadInputs_CTRL_RCOD_SHIFT        0x02u
        #define ReadInputs_CTRL_ENBL_SHIFT        0x00u
        #define ReadInputs_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define ReadInputs_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << ReadInputs_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define ReadInputs_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << ReadInputs_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define ReadInputs_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << ReadInputs_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define ReadInputs_CTRL_RCOD       ((uint8)((uint8)0x03u << ReadInputs_CTRL_RCOD_SHIFT))
        #define ReadInputs_CTRL_ENBL       ((uint8)((uint8)0x80u << ReadInputs_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define ReadInputs_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define ReadInputs_RT1_MASK                        ((uint8)((uint8)0x03u << ReadInputs_RT1_SHIFT))
    #define ReadInputs_SYNC                            ((uint8)((uint8)0x03u << ReadInputs_RT1_SHIFT))
    #define ReadInputs_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define ReadInputs_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << ReadInputs_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define ReadInputs_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << ReadInputs_SYNCDSI_SHIFT))

    #define ReadInputs_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << ReadInputs_CTRL_MODE_SHIFT))
    #define ReadInputs_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << ReadInputs_CTRL_MODE_SHIFT))
    #define ReadInputs_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << ReadInputs_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define ReadInputs_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define ReadInputs_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define ReadInputs_STATUS_TC_INT_MASK_SHIFT        (ReadInputs_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define ReadInputs_STATUS_CAPTURE_INT_MASK_SHIFT   (ReadInputs_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define ReadInputs_STATUS_TC                       ((uint8)((uint8)0x01u << ReadInputs_STATUS_TC_SHIFT))
    #define ReadInputs_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << ReadInputs_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define ReadInputs_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << ReadInputs_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define ReadInputs_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << ReadInputs_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define ReadInputs_STATUS              (* (reg8 *) ReadInputs_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define ReadInputs_STATUS_MASK         (* (reg8 *) ReadInputs_TimerUDB_rstSts_stsreg__MASK_REG)
    #define ReadInputs_STATUS_AUX_CTRL     (* (reg8 *) ReadInputs_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define ReadInputs_CONTROL             (* (reg8 *) ReadInputs_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(ReadInputs_Resolution <= 8u) /* 8-bit Timer */
        #define ReadInputs_CAPTURE_LSB         (* (reg8 *) ReadInputs_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define ReadInputs_CAPTURE_LSB_PTR       ((reg8 *) ReadInputs_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define ReadInputs_PERIOD_LSB          (* (reg8 *) ReadInputs_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define ReadInputs_PERIOD_LSB_PTR        ((reg8 *) ReadInputs_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define ReadInputs_COUNTER_LSB         (* (reg8 *) ReadInputs_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define ReadInputs_COUNTER_LSB_PTR       ((reg8 *) ReadInputs_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(ReadInputs_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define ReadInputs_CAPTURE_LSB         (* (reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define ReadInputs_CAPTURE_LSB_PTR       ((reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define ReadInputs_PERIOD_LSB          (* (reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define ReadInputs_PERIOD_LSB_PTR        ((reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define ReadInputs_COUNTER_LSB         (* (reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define ReadInputs_COUNTER_LSB_PTR       ((reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define ReadInputs_CAPTURE_LSB         (* (reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define ReadInputs_CAPTURE_LSB_PTR       ((reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define ReadInputs_PERIOD_LSB          (* (reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define ReadInputs_PERIOD_LSB_PTR        ((reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define ReadInputs_COUNTER_LSB         (* (reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define ReadInputs_COUNTER_LSB_PTR       ((reg16 *) ReadInputs_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(ReadInputs_Resolution <= 24u)/* 24-bit Timer */
        #define ReadInputs_CAPTURE_LSB         (* (reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define ReadInputs_CAPTURE_LSB_PTR       ((reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define ReadInputs_PERIOD_LSB          (* (reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define ReadInputs_PERIOD_LSB_PTR        ((reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define ReadInputs_COUNTER_LSB         (* (reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define ReadInputs_COUNTER_LSB_PTR       ((reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define ReadInputs_CAPTURE_LSB         (* (reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define ReadInputs_CAPTURE_LSB_PTR       ((reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define ReadInputs_PERIOD_LSB          (* (reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define ReadInputs_PERIOD_LSB_PTR        ((reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define ReadInputs_COUNTER_LSB         (* (reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define ReadInputs_COUNTER_LSB_PTR       ((reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define ReadInputs_CAPTURE_LSB         (* (reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define ReadInputs_CAPTURE_LSB_PTR       ((reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define ReadInputs_PERIOD_LSB          (* (reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define ReadInputs_PERIOD_LSB_PTR        ((reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define ReadInputs_COUNTER_LSB         (* (reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define ReadInputs_COUNTER_LSB_PTR       ((reg32 *) ReadInputs_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define ReadInputs_COUNTER_LSB_PTR_8BIT       ((reg8 *) ReadInputs_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (ReadInputs_UsingHWCaptureCounter)
        #define ReadInputs_CAP_COUNT              (*(reg8 *) ReadInputs_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define ReadInputs_CAP_COUNT_PTR          ( (reg8 *) ReadInputs_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define ReadInputs_CAPTURE_COUNT_CTRL     (*(reg8 *) ReadInputs_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define ReadInputs_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) ReadInputs_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (ReadInputs_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define ReadInputs_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define ReadInputs_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define ReadInputs_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define ReadInputs_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define ReadInputs_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define ReadInputs_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << ReadInputs_CTRL_INTCNT_SHIFT))
    #define ReadInputs_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << ReadInputs_CTRL_TRIG_MODE_SHIFT))
    #define ReadInputs_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << ReadInputs_CTRL_TRIG_EN_SHIFT))
    #define ReadInputs_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << ReadInputs_CTRL_CAP_MODE_SHIFT))
    #define ReadInputs_CTRL_ENABLE                    ((uint8)((uint8)0x01u << ReadInputs_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define ReadInputs_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define ReadInputs_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define ReadInputs_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define ReadInputs_STATUS_TC_INT_MASK_SHIFT       ReadInputs_STATUS_TC_SHIFT
    #define ReadInputs_STATUS_CAPTURE_INT_MASK_SHIFT  ReadInputs_STATUS_CAPTURE_SHIFT
    #define ReadInputs_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define ReadInputs_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define ReadInputs_STATUS_FIFOFULL_INT_MASK_SHIFT ReadInputs_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define ReadInputs_STATUS_TC                      ((uint8)((uint8)0x01u << ReadInputs_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define ReadInputs_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << ReadInputs_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define ReadInputs_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << ReadInputs_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define ReadInputs_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << ReadInputs_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define ReadInputs_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << ReadInputs_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define ReadInputs_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << ReadInputs_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define ReadInputs_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << ReadInputs_STATUS_FIFOFULL_SHIFT))

    #define ReadInputs_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define ReadInputs_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define ReadInputs_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define ReadInputs_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define ReadInputs_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define ReadInputs_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_ReadInputs_H */


/* [] END OF FILE */
