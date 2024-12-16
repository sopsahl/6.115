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
volatile enum Waveform waveform_select = Default;
uint16_t* waveforms[4] = {beginning_waveform, repeat_waveform, end_waveform, default_waveform};
uint16 periods[28] = {4111, 3879, 3662, 3455, 3262, 3078, 2906, 2742, 2589, 2444, 2306, 2177, 2054, 1939, 1830, 1728, 1631, 1539, 1453, 1371, 1294, 1222, 1153, 1088, 1027, 970, 915, 864};
uint16 new_period = 4110;
enum new_waveform {
    False,
    True
};
volatile enum new_waveform new_waveform = False;
volatile uint16_t key_status = 0;

enum Note {
    Bb1, B1, C2, Csharp2, D2, Dsharp2, E2, F2, Fsharp2, G2, Gsharp2, A2,
    Bb2, B2, C3, Csharp3, D3, Dsharp3, E3, F3, Fsharp3, G3, Gsharp3, A3,
    Bb3, B3, C4, Csharp4
};

volatile enum Note note = Csharp3;


CY_ISR(Waveform_ISR) {
    
    // Toggle the digital pin
    Fs_Write(~Fs_Read());
    
    // Update DAC output with the next value from the waveform
    waveVal = (waveforms[waveform_select][waveformIndex]*volume) + 2048;
    Wave_Out_SetValue(waveVal);
    
    // Increment waveform index for the next interrupt
    waveformIndex++;
    
    // Update the waveform counter if overflowed
    if (waveformIndex >= waveform_sizes[waveform_select]) {
        // Reset the counter
        waveformIndex = 0;
        
        switch (waveform_select) {
            case Beginning:
                waveform_select = Repeat; // Moves onto the repeat waveform
                break;
            case Repeat:
                if (new_waveform == True) { waveform_select = End; new_waveform = False; } // Moves onto the end waveform if a button is pressed
                break;
            case End:
                waveform_select = Beginning; 
                Waveform_Send_WritePeriod(periods[note]); // moves to the new waveform sampling freq               
                break;
            case Default:
                if (new_waveform == True) { waveform_select = Beginning; new_waveform = False; Waveform_Send_WritePeriod(periods[note]); } // starts a waveform if pressed
               
                break; 
        }
    }
    
    // Resets the TC flag
    Waveform_Send_ReadStatusRegister();
}

CY_ISR(Button_ISR) {
    
    key_status = ((uint16_t)KeyNote_High_Read()  << 8) | KeyNote_Low_Read(); // get the values of keys pressed 
    new_waveform = True; // we have a new waveform
    
    // bit 13 is key 1 in the note table, bit 0 is key 14
    switch (key_status) {
        case 0b11111100010001: note = Bb1; break;
        case 0b11111100010100: note = B1; break;
        case 0b11111100010000: note = C2; break;
        case 0b11111100010010: note = Csharp2; break;
        case 0b11111100000000: note = D2; break;
        case 0b11111100100000: note = Dsharp2; break;
        case 0b11111000000000: note = E2; break;
        case 0b11110000000000: note = F2; break;
        case 0b11101000000000: note = Fsharp2; break;
        case 0b11100000000000: note = G2; break;
        case 0b11100000001000: note = Gsharp2; break;
        case 0b11000000000000: note = A2;  break;
        case 0b11000001000000: note = Bb2; break;
        case 0b10000000000000: note = B2; break;
        case 0b01000000000000: note = C3; break;
        case 0b00000000000000: note = Csharp3; break;
        case 0b11111110000000: note = D3; break;
        case 0b11111110100000: note = Dsharp3; break;
        case 0b11111010000000: note = E3; break;
        case 0b11110010000000: note = F3; break;
        case 0b11101010000000: note = Fsharp3; break;
        case 0b11100010000000: note = G3; break;
        case 0b11100010001000: note = Gsharp3; break;
        case 0b11000010000000: note = A3; break;
        case 0b11000011000000: note = Bb3; break;
        case 0b10000010000000: note = B3; break;
        case 0b01000010000000: note = C4; break;
        case 0b00000010000000: note = Csharp4; break;
        default: break;
    }  
}

int main(void) {
    
    CyGlobalIntEnable; // Enable global interrupts
    Waveform_ISR_StartEx(Waveform_ISR); // Initialize the Waveform ISR
    Button_Switch_StartEx(Button_ISR); // Initialize the Button ISR
    
    // Initialize components
    Waveform_Send_Start(); // Start the Waveform Timer
    Wave_Out_Start(); // Start the DAC
    DACBuffer_Start(); // Start the OpAmp
    
    for(;;) {}  // Whole lotta nothing //
}

/* [] END OF FILE */
