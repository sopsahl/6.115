/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "waveforms.h"

volatile uint32_t waveformIndex = 0;
volatile uint16_t waveVal = 0;
volatile uint8_t volume = 10;
volatile enum Waveform waveform_select = Beginning;
uint16_t* waveforms[4] = {beginning_waveform, repeat_waveform, end_waveform, default_waveform};

CY_ISR(Waveform_ISR)
{
    // Toggle the digital pin
    Fs_Write(~Fs_Read());
    
    // Update DAC output with the next value from the waveform
    waveVal = (waveforms[waveform_select][waveformIndex]*volume) + 2048;
    Wave_Out_SetValue(waveVal);
    // Increment waveform index for the next interrupt
    waveformIndex++;
    
    // Update the waveform counter
    if (waveformIndex >= waveform_sizes[waveform_select]) {
        // Reset the counter
        waveformIndex = 0;
        waveform_select = (waveform_select + 1)%4;
    }
    
    // Resets the TC flag
    Waveform_Send_ReadStatusRegister();
}


int main(void)
{
    
    CyGlobalIntEnable; // Enable global interrupts
    
    // Different sampling periods of different notes
    uint16 periods[28] = {4110, 3879, 3662, 3455, 3262, 3078, 2906, 2742, 2589, 2444, 2306, 2177, 2054, 1939, 1830, 1728, 1631, 1539, 1453, 1371, 1294, 1222, 1153, 1088, 1027, 970, 915, 864};
    
    // Initialize components
    Waveform_ISR_StartEx(Waveform_ISR); // Initialize the ISR
    Waveform_Send_Start(); // Start the timer
    Wave_Out_Start(); // Start the DAC
    DACBuffer_Start(); // Start the OpAmp
    
    
    
    for(;;)
    {
        for (int i = 0; i < 28; i++){
            Waveform_Send_WritePeriod(periods[i]);
            CyDelay(1000);
        }
    }
}


/* [] END OF FILE */
