// ======================================================================
// KeysToNote.v generated from TopDesign.cysch
// 05/13/2024 at 14:20
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

/* -- WARNING: The following section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_DIE_LEOPARD 1
`define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
`define CYDEV_CHIP_REV_LEOPARD_ES3 3
`define CYDEV_CHIP_REV_LEOPARD_ES2 1
`define CYDEV_CHIP_REV_LEOPARD_ES1 0
`define CYDEV_CHIP_DIE_PSOC5LP 2
`define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0
`define CYDEV_CHIP_REV_PSOC5LP_ES0 0
`define CYDEV_CHIP_DIE_PSOC5TM 3
`define CYDEV_CHIP_REV_PSOC5TM_PRODUCTION 1
`define CYDEV_CHIP_REV_PSOC5TM_ES1 1
`define CYDEV_CHIP_REV_PSOC5TM_ES0 0
`define CYDEV_CHIP_DIE_TMA4 4
`define CYDEV_CHIP_REV_TMA4_PRODUCTION 17
`define CYDEV_CHIP_REV_TMA4_ES 17
`define CYDEV_CHIP_REV_TMA4_ES2 33
`define CYDEV_CHIP_DIE_PSOC4A 5
`define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17
`define CYDEV_CHIP_REV_PSOC4A_ES0 17
`define CYDEV_CHIP_DIE_PSOC6ABLE2 6
`define CYDEV_CHIP_REV_PSOC6ABLE2_ES 17
`define CYDEV_CHIP_REV_PSOC6ABLE2_PRODUCTION 33
`define CYDEV_CHIP_REV_PSOC6ABLE2_NO_UDB 33
`define CYDEV_CHIP_DIE_VOLANS 7
`define CYDEV_CHIP_REV_VOLANS_PRODUCTION 0
`define CYDEV_CHIP_DIE_BERRYPECKER 8
`define CYDEV_CHIP_REV_BERRYPECKER_PRODUCTION 0
`define CYDEV_CHIP_DIE_CRANE 9
`define CYDEV_CHIP_REV_CRANE_PRODUCTION 0
`define CYDEV_CHIP_DIE_FM3 10
`define CYDEV_CHIP_REV_FM3_PRODUCTION 0
`define CYDEV_CHIP_DIE_FM4 11
`define CYDEV_CHIP_REV_FM4_PRODUCTION 0
`define CYDEV_CHIP_DIE_EXPECT 2
`define CYDEV_CHIP_REV_EXPECT 0
`define CYDEV_CHIP_DIE_ACTUAL 2
/* -- WARNING: The previous section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_FAMILY_PSOC6 4
`define CYDEV_CHIP_FAMILY_FM0P 5
`define CYDEV_CHIP_FAMILY_FM3 6
`define CYDEV_CHIP_FAMILY_FM4 7
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_MEMBER_5B 2
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_MEMBER_5A 3
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_MEMBER_4G 4
`define CYDEV_CHIP_REVISION_4G_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4G_ES 17
`define CYDEV_CHIP_REVISION_4G_ES2 33
`define CYDEV_CHIP_MEMBER_4U 5
`define CYDEV_CHIP_REVISION_4U_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4E 6
`define CYDEV_CHIP_REVISION_4E_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD 0
`define CYDEV_CHIP_MEMBER_4X 7
`define CYDEV_CHIP_REVISION_4X_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4O 8
`define CYDEV_CHIP_REVISION_4O_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4R 9
`define CYDEV_CHIP_REVISION_4R_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4T 10
`define CYDEV_CHIP_REVISION_4T_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4N 11
`define CYDEV_CHIP_REVISION_4N_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4S 12
`define CYDEV_CHIP_REVISION_4S_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4W 13
`define CYDEV_CHIP_REVISION_4W_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4AC 14
`define CYDEV_CHIP_REVISION_4AC_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4AD 15
`define CYDEV_CHIP_REVISION_4AD_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4AE 16
`define CYDEV_CHIP_REVISION_4AE_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Q 17
`define CYDEV_CHIP_REVISION_4Q_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Y 18
`define CYDEV_CHIP_REVISION_4Y_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Z 19
`define CYDEV_CHIP_REVISION_4Z_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4D 20
`define CYDEV_CHIP_REVISION_4D_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4J 21
`define CYDEV_CHIP_REVISION_4J_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4K 22
`define CYDEV_CHIP_REVISION_4K_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4V 23
`define CYDEV_CHIP_REVISION_4V_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4H 24
`define CYDEV_CHIP_REVISION_4H_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4AA 25
`define CYDEV_CHIP_REVISION_4AA_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4A 26
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_MEMBER_4F 27
`define CYDEV_CHIP_REVISION_4F_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0
`define CYDEV_CHIP_MEMBER_4P 28
`define CYDEV_CHIP_REVISION_4P_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4M 29
`define CYDEV_CHIP_REVISION_4M_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4AB 30
`define CYDEV_CHIP_REVISION_4AB_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4L 31
`define CYDEV_CHIP_REVISION_4L_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4I 32
`define CYDEV_CHIP_REVISION_4I_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_6A 33
`define CYDEV_CHIP_REVISION_6A_ES 17
`define CYDEV_CHIP_REVISION_6A_PRODUCTION 33
`define CYDEV_CHIP_REVISION_6A_NO_UDB 33
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 34
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 35
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 36
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM3 37
`define CYDEV_CHIP_REVISION_FM3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM4 38
`define CYDEV_CHIP_REVISION_FM4_PRODUCTION 0
`define CYDEV_CHIP_FAMILY_USED 3
`define CYDEV_CHIP_MEMBER_USED 2
`define CYDEV_CHIP_REVISION_USED 0
// Component: Debouncer_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyComponentLibrary\CyComponentLibrary.cylib\Debouncer_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyComponentLibrary\CyComponentLibrary.cylib\Debouncer_v1_0\Debouncer_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyComponentLibrary\CyComponentLibrary.cylib\Debouncer_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyComponentLibrary\CyComponentLibrary.cylib\Debouncer_v1_0\Debouncer_v1_0.v"
`endif

// Component: or_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0\or_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0\or_v1_0.v"
`endif

// Component: CyStatusReg_v1_90
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyStatusReg_v1_90"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyStatusReg_v1_90\CyStatusReg_v1_90.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyStatusReg_v1_90"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyStatusReg_v1_90\CyStatusReg_v1_90.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: OneTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\OneTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\OneTerminal\OneTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\OneTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\OneTerminal\OneTerminal.v"
`endif

// Timer_v2_80(CaptureAlternatingFall=false, CaptureAlternatingRise=false, CaptureCount=2, CaptureCounterEnabled=false, CaptureInputEnabled=false, CaptureMode=0, CONTROL3=1, ControlRegRemoved=0, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeviceFamily=PSoC5, EnableMode=0, FF16=true, FF8=false, FixedFunction=true, FixedFunctionUsed=1, HWCaptureCounterEnabled=false, InterruptOnCapture=false, InterruptOnFIFOFull=false, InterruptOnTC=true, IntOnCapture=0, IntOnFIFOFull=0, IntOnTC=1, NumberOfCaptures=1, param45=1, Period=1087, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=rstSts, RunMode=0, SiliconRevision=0, SoftwareCaptureModeEnabled=false, SoftwareTriggerModeEnabled=false, TriggerInputEnabled=false, TriggerMode=0, UDB16=false, UDB24=false, UDB32=false, UDB8=false, UDBControlReg=false, UsesHWEnable=0, VerilogSectionReplacementString=sT16, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=Timer_v2_80, CY_CONFIG_TITLE=Waveform_Send, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=Waveform_Send, CY_INSTANCE_SHORT_NAME=Waveform_Send, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=80, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.4, INSTANCE_NAME=Waveform_Send, )
module Timer_v2_80_0 (
    capture,
    capture_out,
    clock,
    enable,
    interrupt,
    reset,
    tc,
    trigger);
    input       capture;
    output      capture_out;
    input       clock;
    input       enable;
    output      interrupt;
    input       reset;
    output      tc;
    input       trigger;

    parameter CaptureCount = 2;
    parameter CaptureCounterEnabled = 0;
    parameter DeviceFamily = "PSoC5";
    parameter InterruptOnCapture = 0;
    parameter InterruptOnTC = 1;
    parameter Resolution = 16;
    parameter SiliconRevision = "0";

          wire  Net_260;
          wire  Net_261;
          wire  Net_266;
          wire  Net_102;
          wire  Net_55;
          wire  Net_57;
          wire  Net_53;
          wire  Net_51;

    cy_psoc3_timer_v1_0 TimerHW (
        .capture(capture),
        .clock(clock),
        .compare(Net_261),
        .enable(Net_266),
        .interrupt(Net_57),
        .kill(Net_260),
        .tc(Net_51),
        .timer_reset(reset));

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_260));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign interrupt = Net_57;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign tc = Net_51;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_266 = Net_102;



endmodule

// VDAC8_v1_90(Data_Source=0, Initial_Value=25, Strobe_Mode=1, VDAC_Range=4, VDAC_Speed=2, Voltage=100, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=VDAC8_v1_90, CY_CONFIG_TITLE=VDAC8, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=Wave_Out:VDAC8, CY_INSTANCE_SHORT_NAME=VDAC8, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=90, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.4, INSTANCE_NAME=Wave_Out_VDAC8, )
module VDAC8_v1_90_1 (
    data,
    strobe,
    vOut);
    input      [7:0] data;
    input       strobe;
    inout       vOut;
    electrical  vOut;

    parameter Data_Source = 0;
    parameter Initial_Value = 25;
    parameter Strobe_Mode = 1;

    electrical  Net_77;
          wire  Net_83;
          wire  Net_82;
          wire  Net_81;

    cy_psoc3_vidac8_v1_0 viDAC8 (
        .data(data[7:0]),
        .idir(Net_81),
        .ioff(Net_82),
        .iout(Net_77),
        .reset(Net_83),
        .strobe(strobe),
        .strobe_udb(strobe),
        .vout(vOut));
    defparam viDAC8.is_all_if_any = 0;
    defparam viDAC8.reg_data = 0;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_81));

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_82));

    ZeroTerminal ZeroTerminal_3 (
        .z(Net_83));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_1 (
        .noconnect(Net_77));



endmodule

// DVDAC_v2_10(DAC_Range=4, Initial_Value=0, InternalClock=true, InternalClockFreqHz=250000, Resolution=12, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=DVDAC_v2_10, CY_CONFIG_TITLE=Wave_Out, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=Wave_Out, CY_INSTANCE_SHORT_NAME=Wave_Out, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=10, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.4, INSTANCE_NAME=Wave_Out, )
module DVDAC_v2_10_2 (
    clock,
    Vout);
    input       clock;
    inout       Vout;
    electrical  Vout;


          wire  Net_9;
          wire  Net_22;
          wire [7:0] Net_20;
          wire  Net_18;
          wire  Net_19;
          wire  Net_17;
          wire  Net_21;
          wire  Net_12;
          wire  Net_1;
          wire  Net_80;


	cy_clock_v1_0
		#(.id("df068792-0d22-425d-ab80-b778b1d3d576/16079296-677d-4c97-a0f1-fd79fcfb8c33"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		BUS_CLK
		 (.clock_out(Net_1));



	cy_dma_v1_0
		#(.drq_type(2'b00))
		DMA
		 (.drq(Net_12),
		  .nrq(Net_19),
		  .trq(1'b0));


    VDAC8_v1_90_1 VDAC8 (
        .data(8'b00000000),
        .strobe(Net_12),
        .vOut(Vout));
    defparam VDAC8.Data_Source = 0;
    defparam VDAC8.Initial_Value = 25;
    defparam VDAC8.Strobe_Mode = 1;


	cy_clock_v1_0
		#(.id("df068792-0d22-425d-ab80-b778b1d3d576/2b3078c1-9a14-4aea-bb80-3826ca4e0c90"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("4000000000"),
		  .is_direct(0),
		  .is_digital(1))
		IntClock
		 (.clock_out(Net_21));


	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_12 = Net_21;

    ZeroTerminal ZeroTerminal_3 (
        .z(Net_80));


    assign Net_9 = Net_80 | Net_1;



endmodule

// Component: cy_analog_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_analog_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_analog_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.4\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
`endif

// OpAmp_v1_90(Mode=1, Power=1, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=OpAmp_v1_90, CY_CONFIG_TITLE=DACBuffer, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=DACBuffer, CY_INSTANCE_SHORT_NAME=DACBuffer, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=90, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.4, INSTANCE_NAME=DACBuffer, )
module OpAmp_v1_90_3 (
    Vminus,
    Vout,
    Vplus);
    inout       Vminus;
    electrical  Vminus;
    inout       Vout;
    electrical  Vout;
    inout       Vplus;
    electrical  Vplus;

    parameter Mode = 1;

    electrical  Net_29;

    cy_psoc3_abuf_v1_0 ABuf (
        .vminus(Net_29),
        .vout(Vout),
        .vplus(Vplus));

	// abuf_negInput_mux (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 abuf_negInput_mux_connect(Net_29, Vout);
	defparam abuf_negInput_mux_connect.sig_width = 1;



endmodule

// top
module top ;

    electrical  Net_757;
    electrical  Net_756;
    electrical  Net_755;
          wire  Net_754;
          wire  Net_765;
          wire  Net_764;
          wire  Net_751;
          wire  Net_763;
          wire  Net_762;
          wire  Net_761;
          wire  Net_769;
          wire  Net_746;
          wire [7:0] Net_686;
          wire  Net_685;
          wire  Net_684;
          wire  Net_683;
          wire [7:0] Net_688;
          wire  Net_687;
          wire  Net_689;
          wire  Net_576;
          wire  Net_723;
          wire  Net_722;
          wire  Net_694;
          wire  Net_721;
          wire  Net_720;
          wire  Net_695;
          wire  Net_719;
          wire  Net_718;
          wire  Net_696;
          wire  Net_717;
          wire  Net_716;
          wire  Net_697;
          wire  Net_715;
          wire  Net_714;
          wire  Net_698;
          wire  Net_713;
          wire  Net_712;
          wire  Net_699;
          wire  Net_711;
          wire  Net_710;
          wire  Net_700;
          wire  Net_709;
          wire  Net_708;
          wire  Net_701;
          wire  Net_707;
          wire  Net_706;
          wire  Net_702;
          wire  Net_705;
          wire  Net_704;
          wire  Net_703;
          wire  Net_725;
          wire  Net_724;
          wire  Net_693;
          wire  Net_727;
          wire  Net_726;
          wire  Net_692;
          wire  Net_729;
          wire  Net_728;
          wire  Net_691;
          wire  Net_745;
          wire  Net_744;
          wire  Net_690;
    electrical  Net_734;
    electrical  Net_735;
    electrical  Net_736;
    electrical  Net_737;
    electrical  Net_738;
    electrical  Net_739;
    electrical  Net_730;
    electrical  Net_731;
    electrical  Net_732;
    electrical  Net_733;
    electrical  Net_743;
    electrical  Net_742;
    electrical  Net_741;
    electrical  Net_740;
          wire  Net_12;
    electrical  Net_315;
    electrical  Net_316;
    electrical  Net_337;
          wire  Net_381;
          wire  Net_387;
          wire  Net_393;
          wire  Net_495;
          wire  Net_501;
          wire  Net_507;
          wire  Net_513;
          wire  Net_519;
          wire  Net_525;
          wire  Net_531;
          wire  Net_537;
          wire  Net_549;
          wire  Net_555;
          wire  Net_561;
          wire  Net_611;
          wire  Net_657;
          wire  Net_614;
          wire  Net_615;
          wire  Net_616;
          wire  Net_617;
          wire  Net_652;
          wire  Net_386;
          wire  Net_620;
          wire  Net_622;
          wire  Net_623;
          wire  Net_625;
          wire  Net_612;
          wire  Net_642;
          wire  Net_643;
          wire  Net_644;
          wire  Net_645;
          wire  Net_646;
          wire  Net_647;
          wire  Net_659;

    cy_annotation_universal_v1_0 SW_4 (
        .connect({
            Net_337,
            Net_740
        })
    );
    defparam SW_4.comp_name = "SwitchSPST_v1_0";
    defparam SW_4.port_names = "T1, T2";
    defparam SW_4.width = 2;

    cy_annotation_universal_v1_0 SW_3 (
        .connect({
            Net_337,
            Net_741
        })
    );
    defparam SW_3.comp_name = "SwitchSPST_v1_0";
    defparam SW_3.port_names = "T1, T2";
    defparam SW_3.width = 2;

    cy_annotation_universal_v1_0 SW_2 (
        .connect({
            Net_337,
            Net_742
        })
    );
    defparam SW_2.comp_name = "SwitchSPST_v1_0";
    defparam SW_2.port_names = "T1, T2";
    defparam SW_2.width = 2;

    cy_annotation_universal_v1_0 SW_1 (
        .connect({
            Net_337,
            Net_743
        })
    );
    defparam SW_1.comp_name = "SwitchSPST_v1_0";
    defparam SW_1.port_names = "T1, T2";
    defparam SW_1.width = 2;

	wire [13:0] tmpOE__SaxKeys_net;
	wire [13:0] tmpIO_13__SaxKeys_net;
	wire [0:0] tmpINTERRUPT_0__SaxKeys_net;
	electrical [0:0] tmpSIOVREF__SaxKeys_net;

	cy_psoc3_pins_v1_10
		#(.id("8d318d8b-cf7b-4b6b-b02c-ab1c5c49d0ba"),
		  .drive_mode(42'b011_011_011_011_011_011_011_011_011_011_011_011_011_011),
		  .ibuf_enabled(14'b1_1_1_1_1_1_1_1_1_1_1_1_1_1),
		  .init_dr_st(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .input_clk_en(0),
		  .input_sync(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .input_sync_mode(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .intr_mode(28'b00_00_00_00_00_00_00_00_00_00_00_00_00_00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(",,,,,,,,,,,,,"),
		  .layout_mode("NONCONTIGUOUS"),
		  .oe_conn(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .oe_reset(0),
		  .oe_sync(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .output_clk_en(0),
		  .output_clock_mode(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .output_conn(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .output_mode(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .output_reset(0),
		  .output_sync(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(",,,,,,,,,,,,,"),
		  .pin_mode("IIIIIIIIIIIIII"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(14'b1_1_1_1_1_1_1_1_1_1_1_1_1_1),
		  .sio_ibuf(""),
		  .sio_info(28'b00_00_00_00_00_00_00_00_00_00_00_00_00_00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .spanning(1),
		  .use_annotation(14'b1_1_1_1_1_1_1_1_1_1_1_1_1_1),
		  .vtrip(28'b00_00_00_00_00_00_00_00_00_00_00_00_00_00),
		  .width(14),
		  .ovt_hyst_trim(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .ovt_needed(14'b0_0_0_0_0_0_0_0_0_0_0_0_0_0),
		  .ovt_slew_control(28'b00_00_00_00_00_00_00_00_00_00_00_00_00_00),
		  .input_buffer_sel(28'b00_00_00_00_00_00_00_00_00_00_00_00_00_00))
		SaxKeys
		 (.oe(tmpOE__SaxKeys_net),
		  .y({14'b0}),
		  .fb({Net_561, Net_555, Net_549, Net_537, Net_531, Net_525, Net_519, Net_513, Net_507, Net_501, Net_495, Net_393, Net_387, Net_381}),
		  .io({tmpIO_13__SaxKeys_net[13:0]}),
		  .siovref(tmpSIOVREF__SaxKeys_net),
		  .interrupt({tmpINTERRUPT_0__SaxKeys_net[0:0]}),
		  .annotation({Net_730, Net_731, Net_732, Net_733, Net_734, Net_735, Net_736, Net_737, Net_738, Net_739, Net_740, Net_741, Net_742, Net_743}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__SaxKeys_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{14'b11111111111111} : {14'b11111111111111};

    Debouncer_v1_0 Debouncer_1 (
        .clock(Net_659),
        .d(Net_381),
        .either(Net_690),
        .neg(Net_744),
        .pos(Net_745),
        .q(Net_617));
    defparam Debouncer_1.EitherEdgeDetect = 1;
    defparam Debouncer_1.NegEdgeDetect = 0;
    defparam Debouncer_1.PosEdgeDetect = 0;
    defparam Debouncer_1.SignalWidth = 1;

    cy_annotation_universal_v1_0 SW_5 (
        .connect({
            Net_337,
            Net_739
        })
    );
    defparam SW_5.comp_name = "SwitchSPST_v1_0";
    defparam SW_5.port_names = "T1, T2";
    defparam SW_5.width = 2;

    cy_annotation_universal_v1_0 SW_6 (
        .connect({
            Net_337,
            Net_738
        })
    );
    defparam SW_6.comp_name = "SwitchSPST_v1_0";
    defparam SW_6.port_names = "T1, T2";
    defparam SW_6.width = 2;

    cy_annotation_universal_v1_0 SW_7 (
        .connect({
            Net_337,
            Net_737
        })
    );
    defparam SW_7.comp_name = "SwitchSPST_v1_0";
    defparam SW_7.port_names = "T1, T2";
    defparam SW_7.width = 2;

    cy_annotation_universal_v1_0 SW_8 (
        .connect({
            Net_337,
            Net_736
        })
    );
    defparam SW_8.comp_name = "SwitchSPST_v1_0";
    defparam SW_8.port_names = "T1, T2";
    defparam SW_8.width = 2;

    cy_annotation_universal_v1_0 SW_9 (
        .connect({
            Net_337,
            Net_735
        })
    );
    defparam SW_9.comp_name = "SwitchSPST_v1_0";
    defparam SW_9.port_names = "T1, T2";
    defparam SW_9.width = 2;

    cy_annotation_universal_v1_0 SW_10 (
        .connect({
            Net_337,
            Net_734
        })
    );
    defparam SW_10.comp_name = "SwitchSPST_v1_0";
    defparam SW_10.port_names = "T1, T2";
    defparam SW_10.width = 2;

    cy_annotation_universal_v1_0 SW_11 (
        .connect({
            Net_337,
            Net_733
        })
    );
    defparam SW_11.comp_name = "SwitchSPST_v1_0";
    defparam SW_11.port_names = "T1, T2";
    defparam SW_11.width = 2;

    cy_annotation_universal_v1_0 SW_12 (
        .connect({
            Net_337,
            Net_732
        })
    );
    defparam SW_12.comp_name = "SwitchSPST_v1_0";
    defparam SW_12.port_names = "T1, T2";
    defparam SW_12.width = 2;

    cy_annotation_universal_v1_0 SW_13 (
        .connect({
            Net_337,
            Net_731
        })
    );
    defparam SW_13.comp_name = "SwitchSPST_v1_0";
    defparam SW_13.port_names = "T1, T2";
    defparam SW_13.width = 2;

    cy_annotation_universal_v1_0 SW_14 (
        .connect({
            Net_337,
            Net_730
        })
    );
    defparam SW_14.comp_name = "SwitchSPST_v1_0";
    defparam SW_14.port_names = "T1, T2";
    defparam SW_14.width = 2;

    cy_annotation_universal_v1_0 PWR_1 (
        .connect({
            Net_337
        })
    );
    defparam PWR_1.comp_name = "Power_v1_0";
    defparam PWR_1.port_names = "T1";
    defparam PWR_1.width = 1;

    Debouncer_v1_0 Debouncer_2 (
        .clock(Net_659),
        .d(Net_387),
        .either(Net_691),
        .neg(Net_728),
        .pos(Net_729),
        .q(Net_652));
    defparam Debouncer_2.EitherEdgeDetect = 1;
    defparam Debouncer_2.NegEdgeDetect = 0;
    defparam Debouncer_2.PosEdgeDetect = 0;
    defparam Debouncer_2.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_3 (
        .clock(Net_659),
        .d(Net_393),
        .either(Net_692),
        .neg(Net_726),
        .pos(Net_727),
        .q(Net_386));
    defparam Debouncer_3.EitherEdgeDetect = 1;
    defparam Debouncer_3.NegEdgeDetect = 0;
    defparam Debouncer_3.PosEdgeDetect = 0;
    defparam Debouncer_3.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_4 (
        .clock(Net_659),
        .d(Net_495),
        .either(Net_693),
        .neg(Net_724),
        .pos(Net_725),
        .q(Net_620));
    defparam Debouncer_4.EitherEdgeDetect = 1;
    defparam Debouncer_4.NegEdgeDetect = 0;
    defparam Debouncer_4.PosEdgeDetect = 0;
    defparam Debouncer_4.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_14 (
        .clock(Net_659),
        .d(Net_561),
        .either(Net_703),
        .neg(Net_704),
        .pos(Net_705),
        .q(Net_647));
    defparam Debouncer_14.EitherEdgeDetect = 1;
    defparam Debouncer_14.NegEdgeDetect = 0;
    defparam Debouncer_14.PosEdgeDetect = 0;
    defparam Debouncer_14.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_13 (
        .clock(Net_659),
        .d(Net_555),
        .either(Net_702),
        .neg(Net_706),
        .pos(Net_707),
        .q(Net_646));
    defparam Debouncer_13.EitherEdgeDetect = 1;
    defparam Debouncer_13.NegEdgeDetect = 0;
    defparam Debouncer_13.PosEdgeDetect = 0;
    defparam Debouncer_13.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_12 (
        .clock(Net_659),
        .d(Net_549),
        .either(Net_701),
        .neg(Net_708),
        .pos(Net_709),
        .q(Net_645));
    defparam Debouncer_12.EitherEdgeDetect = 1;
    defparam Debouncer_12.NegEdgeDetect = 0;
    defparam Debouncer_12.PosEdgeDetect = 0;
    defparam Debouncer_12.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_11 (
        .clock(Net_659),
        .d(Net_537),
        .either(Net_700),
        .neg(Net_710),
        .pos(Net_711),
        .q(Net_644));
    defparam Debouncer_11.EitherEdgeDetect = 1;
    defparam Debouncer_11.NegEdgeDetect = 0;
    defparam Debouncer_11.PosEdgeDetect = 0;
    defparam Debouncer_11.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_10 (
        .clock(Net_659),
        .d(Net_531),
        .either(Net_699),
        .neg(Net_712),
        .pos(Net_713),
        .q(Net_643));
    defparam Debouncer_10.EitherEdgeDetect = 1;
    defparam Debouncer_10.NegEdgeDetect = 0;
    defparam Debouncer_10.PosEdgeDetect = 0;
    defparam Debouncer_10.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_9 (
        .clock(Net_659),
        .d(Net_525),
        .either(Net_698),
        .neg(Net_714),
        .pos(Net_715),
        .q(Net_642));
    defparam Debouncer_9.EitherEdgeDetect = 1;
    defparam Debouncer_9.NegEdgeDetect = 0;
    defparam Debouncer_9.PosEdgeDetect = 0;
    defparam Debouncer_9.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_8 (
        .clock(Net_659),
        .d(Net_519),
        .either(Net_697),
        .neg(Net_716),
        .pos(Net_717),
        .q(Net_625));
    defparam Debouncer_8.EitherEdgeDetect = 1;
    defparam Debouncer_8.NegEdgeDetect = 0;
    defparam Debouncer_8.PosEdgeDetect = 0;
    defparam Debouncer_8.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_7 (
        .clock(Net_659),
        .d(Net_513),
        .either(Net_696),
        .neg(Net_718),
        .pos(Net_719),
        .q(Net_612));
    defparam Debouncer_7.EitherEdgeDetect = 1;
    defparam Debouncer_7.NegEdgeDetect = 0;
    defparam Debouncer_7.PosEdgeDetect = 0;
    defparam Debouncer_7.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_6 (
        .clock(Net_659),
        .d(Net_507),
        .either(Net_695),
        .neg(Net_720),
        .pos(Net_721),
        .q(Net_623));
    defparam Debouncer_6.EitherEdgeDetect = 1;
    defparam Debouncer_6.NegEdgeDetect = 0;
    defparam Debouncer_6.PosEdgeDetect = 0;
    defparam Debouncer_6.SignalWidth = 1;

    Debouncer_v1_0 Debouncer_5 (
        .clock(Net_659),
        .d(Net_501),
        .either(Net_694),
        .neg(Net_722),
        .pos(Net_723),
        .q(Net_622));
    defparam Debouncer_5.EitherEdgeDetect = 1;
    defparam Debouncer_5.NegEdgeDetect = 0;
    defparam Debouncer_5.PosEdgeDetect = 0;
    defparam Debouncer_5.SignalWidth = 1;


	cy_clock_v1_0
		#(.id("2cff6df9-cd66-4b20-8a80-d2f776550af0"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("3333333333333.33"),
		  .is_direct(0),
		  .is_digital(1))
		Clock_1
		 (.clock_out(Net_659));



    assign Net_616 = Net_702 | Net_703;


    assign Net_689 = Net_611 | Net_657 | Net_614 | Net_615 | Net_616;


    assign Net_615 = Net_699 | Net_700 | Net_701;


    assign Net_614 = Net_696 | Net_697 | Net_698;


    assign Net_657 = Net_693 | Net_694 | Net_695;


    assign Net_611 = Net_690 | Net_691 | Net_692;


	cy_isr_v1_0
		#(.int_type(2'b00))
		Button_Switch
		 (.int_signal(Net_689));


    CyStatusReg_v1_90 KeyNote_Low (
        .clock(Net_659),
        .intr(Net_687),
        .status_0(Net_617),
        .status_1(Net_652),
        .status_2(Net_386),
        .status_3(Net_620),
        .status_4(Net_622),
        .status_5(Net_623),
        .status_6(Net_612),
        .status_7(Net_625),
        .status_bus(8'b0));
    defparam KeyNote_Low.Bit0Mode = 0;
    defparam KeyNote_Low.Bit1Mode = 0;
    defparam KeyNote_Low.Bit2Mode = 0;
    defparam KeyNote_Low.Bit3Mode = 0;
    defparam KeyNote_Low.Bit4Mode = 0;
    defparam KeyNote_Low.Bit5Mode = 0;
    defparam KeyNote_Low.Bit6Mode = 0;
    defparam KeyNote_Low.Bit7Mode = 0;
    defparam KeyNote_Low.BusDisplay = 0;
    defparam KeyNote_Low.Interrupt = 0;
    defparam KeyNote_Low.MaskValue = 0;
    defparam KeyNote_Low.NumInputs = 8;

    CyStatusReg_v1_90 KeyNote_High (
        .clock(Net_659),
        .intr(Net_683),
        .status_0(Net_642),
        .status_1(Net_643),
        .status_2(Net_644),
        .status_3(Net_645),
        .status_4(Net_646),
        .status_5(Net_647),
        .status_6(1'b0),
        .status_7(1'b0),
        .status_bus(8'b0));
    defparam KeyNote_High.Bit0Mode = 0;
    defparam KeyNote_High.Bit1Mode = 0;
    defparam KeyNote_High.Bit2Mode = 0;
    defparam KeyNote_High.Bit3Mode = 0;
    defparam KeyNote_High.Bit4Mode = 0;
    defparam KeyNote_High.Bit5Mode = 0;
    defparam KeyNote_High.Bit6Mode = 0;
    defparam KeyNote_High.Bit7Mode = 0;
    defparam KeyNote_High.BusDisplay = 0;
    defparam KeyNote_High.Interrupt = 0;
    defparam KeyNote_High.MaskValue = 0;
    defparam KeyNote_High.NumInputs = 6;


	cy_clock_v1_0
		#(.id("c0fb34bd-1044-4931-9788-16b01ce89812"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		timer_clock
		 (.clock_out(Net_746));


    ZeroTerminal ZeroTerminal_1 (
        .z(Net_12));

    Timer_v2_80_0 Waveform_Send (
        .capture(1'b0),
        .capture_out(Net_762),
        .clock(Net_746),
        .enable(1'b1),
        .interrupt(Net_751),
        .reset(Net_12),
        .tc(Net_764),
        .trigger(1'b1));
    defparam Waveform_Send.CaptureCount = 2;
    defparam Waveform_Send.CaptureCounterEnabled = 0;
    defparam Waveform_Send.DeviceFamily = "PSoC5";
    defparam Waveform_Send.InterruptOnCapture = 0;
    defparam Waveform_Send.InterruptOnTC = 1;
    defparam Waveform_Send.Resolution = 16;
    defparam Waveform_Send.SiliconRevision = "0";

	wire [0:0] tmpOE__Fs_net;
	wire [0:0] tmpFB_0__Fs_net;
	wire [0:0] tmpIO_0__Fs_net;
	wire [0:0] tmpINTERRUPT_0__Fs_net;
	electrical [0:0] tmpSIOVREF__Fs_net;

	cy_psoc3_pins_v1_10
		#(.id("e851a3b9-efb8-48be-bbb8-b303b216c393"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		Fs
		 (.oe(tmpOE__Fs_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Fs_net[0:0]}),
		  .io({tmpIO_0__Fs_net[0:0]}),
		  .siovref(tmpSIOVREF__Fs_net),
		  .interrupt({tmpINTERRUPT_0__Fs_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__Fs_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b10))
		Waveform_ISR
		 (.int_signal(Net_751));


    DVDAC_v2_10_2 Wave_Out (
        .clock(1'b0),
        .Vout(Net_755));

    OpAmp_v1_90_3 DACBuffer (
        .Vminus(Net_756),
        .Vout(Net_757),
        .Vplus(Net_755));
    defparam DACBuffer.Mode = 1;

	wire [0:0] tmpOE__Waveform_net;
	wire [0:0] tmpFB_0__Waveform_net;
	wire [0:0] tmpIO_0__Waveform_net;
	wire [0:0] tmpINTERRUPT_0__Waveform_net;
	electrical [0:0] tmpSIOVREF__Waveform_net;

	cy_psoc3_pins_v1_10
		#(.id("cc3bcd7e-5dc0-48ea-9bf6-6aa082be1ada"),
		  .drive_mode(3'b000),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("NONCONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("A"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(1),
		  .use_annotation(1'b1),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		Waveform
		 (.oe(tmpOE__Waveform_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Waveform_net[0:0]}),
		  .analog({Net_757}),
		  .io({tmpIO_0__Waveform_net[0:0]}),
		  .siovref(tmpSIOVREF__Waveform_net),
		  .interrupt({tmpINTERRUPT_0__Waveform_net[0:0]}),
		  .annotation({Net_316}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__Waveform_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    cy_annotation_universal_v1_0 C_Dither (
        .connect({
            Net_316,
            Net_315
        })
    );
    defparam C_Dither.comp_name = "Capacitor_v1_0";
    defparam C_Dither.port_names = "T1, T2";
    defparam C_Dither.width = 2;

    cy_annotation_universal_v1_0 GND_1 (
        .connect({
            Net_315
        })
    );
    defparam GND_1.comp_name = "Gnd_v1_0";
    defparam GND_1.port_names = "T1";
    defparam GND_1.width = 1;



endmodule

