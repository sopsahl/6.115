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
#include "GUI.h"
#include "tft.h" 

enum Note {
    Bb1, B1, C2, Csharp2, D2, Dsharp2, E2, F2, Fsharp2, G2, Gsharp2, A2,
    Bb2, B2, C3, Csharp3, D3, Dsharp3, E3, F3, Fsharp3, G3, Gsharp3, A3,
    Bb3, B3, C4, Csharp4
};
void DisplayInit(void);
void displayNotes(void);

volatile uint32_t waveformIndex = 0;
volatile uint16_t waveVal = 0;
volatile uint8_t volume = 0;
volatile enum Waveform waveform_select = Default;
uint16_t* waveforms[4] = {beginning_waveform, repeat_waveform, end_waveform, default_waveform};
uint16 periods[28] = {4110, 3879, 3662, 3455, 3262, 3078, 2906, 2742, 2589, 2444, 2306, 2177, 2054, 1939, 1830, 1728, 1631, 1539, 1453, 1371, 1294, 1222, 1153, 1088, 1027, 970, 915, 864};
volatile uint16_t key_status = 0;

volatile enum Note note = Csharp3;

volatile uint8 isChange = 0;

enum Note desired_notes[16] = {E3, E3, F3, G3, G3, F3, E3, D3, C3, C3, D3, E3, E3, D3, D3, D3};
uint8 note_locations[16] = {30, 40, 50, 60, 80, 90, 100, 110, 130, 140, 150, 160, 180, 190, 200, 200};
volatile uint8 desired_note_index = 0; 
volatile uint8 old_location = 0; 
uint8 song_length = 16;
volatile int16 volumeControl = 0;

CY_ISR(Waveform_ISR) {
    
    // Toggle the digital pin
    Fs_Write(~Fs_Read());
    
    // Update DAC output with the next value from the waveform
    waveVal = (waveforms[waveform_select][waveformIndex]*volume) + 1024;
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
                waveform_select = End; // Moves onto the end waveform if a button is pressed
                break;
            case End:
                waveform_select = Default;               
                break;
            case Default:
                break; 
        }
    }
    
    // Resets the TC flag
    Waveform_Send_ReadStatusRegister();
}

CY_ISR(Button_ISR) {
    
    key_status = ((uint16_t)KeyNote_High_Read()  << 8) | KeyNote_Low_Read(); // get the values of keys pressed 
    
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
    
    waveform_select = Beginning; // restarts the waveform
    waveformIndex = 0;
    Waveform_Send_WritePeriod(periods[note]); // changes the frequency
    
}

CY_ISR(Inputs_ISR) {
    
    // polls the volume pedal every 1/100 second
    volumeControl = ADC_VolumePedal_Read16();
    
    // changes the volume based on the read of the ADC  
    if (volumeControl < 20) {volume = 0;}
    else if (volumeControl < 40) {volume = 5;}
    else if (volumeControl < 60) {volume = 10;}
    else if (volumeControl < 100) {volume = 15;}
    else if (volumeControl < 140) {volume = 20;}
    else if (volumeControl < 180) {volume = 25;}
    else if (volumeControl < 220) {volume = 30;}
    else if (volumeControl < 240) {volume = 35;}
    else {volume = 40;}
    
    // Resets the TC flag
    ReadInputs_ReadStatusRegister();
    

}

CY_ISR(Notes_ISR) {
    
    isChange = 1;
    desired_note_index = (desired_note_index + 1)%song_length;
    
    // Resets the TC flag
    UpdateNote_ReadStatusRegister();
    
    switch (desired_notes[desired_note_index]) {
    case Bb1:
        Control_Reg_1_Write(0b11111100);
        Control_Reg_2_Write(0b010001);
        break;
    case B1:
        Control_Reg_1_Write(0b11111100);
        Control_Reg_2_Write(0b010100);
        break;
    case C2:
        Control_Reg_1_Write(0b11111100);
        Control_Reg_2_Write(0b010000);
        break;
    case Csharp2:
        Control_Reg_1_Write(0b11111100);
        Control_Reg_2_Write(0b010010);
        break;
    case D2:
        Control_Reg_1_Write(0b11111100);
        Control_Reg_2_Write(0b000000);
        break;
    case Dsharp2:
        Control_Reg_1_Write(0b11111100);
        Control_Reg_2_Write(0b100000);
        break;
    case E2:
        Control_Reg_1_Write(0b11111000);
        Control_Reg_2_Write(0b000000);
        break;
    case F2:
        Control_Reg_1_Write(0b11110000);
        Control_Reg_2_Write(0b000000);
        break;
    case Fsharp2:
        Control_Reg_1_Write(0b11101000);
        Control_Reg_2_Write(0b000000);
        break;
    case G2:
        Control_Reg_1_Write(0b11100000);
        Control_Reg_2_Write(0b000000);
        break;
    case Gsharp2:
        Control_Reg_1_Write(0b11100000);
        Control_Reg_2_Write(0b001000);
        break;
    case A2:
        Control_Reg_1_Write(0b11000000);
        Control_Reg_2_Write(0b000000);
        break;
    case Bb2:
        Control_Reg_1_Write(0b11000001);
        Control_Reg_2_Write(0b000000);
        break;
    case B2:
        Control_Reg_1_Write(0b10000000);
        Control_Reg_2_Write(0b000000);
        break;
    case C3:
        Control_Reg_1_Write(0b01000000);
        Control_Reg_2_Write(0b000000);
        break;
    case Csharp3:
        Control_Reg_1_Write(0b00000000);
        Control_Reg_2_Write(0b000000);
        break;
    case D3:
        Control_Reg_1_Write(0b11111110);
        Control_Reg_2_Write(0b000000);
        break;
    case Dsharp3:
        Control_Reg_1_Write(0b11111110);
        Control_Reg_2_Write(0b100000);
        break;
    case E3:
        Control_Reg_1_Write(0b11111010);
        Control_Reg_2_Write(0b000000);
        break;
    case F3:
        Control_Reg_1_Write(0b11110010);
        Control_Reg_2_Write(0b000000);
        break;
    case Fsharp3:
        Control_Reg_1_Write(0b11101010);
        Control_Reg_2_Write(0b000000);
        break;
    case G3:
        Control_Reg_1_Write(0b11100010);
        Control_Reg_2_Write(0b000000);
        break;
    case Gsharp3:
        Control_Reg_1_Write(0b11100010);
        Control_Reg_2_Write(0b001000);
        break;
    case A3:
        Control_Reg_1_Write(0b11000010);
        Control_Reg_2_Write(0b000000);
        break;
    case Bb3:
        Control_Reg_1_Write(0b11000011);
        Control_Reg_2_Write(0b000000);
        break;
    case B3:
        Control_Reg_1_Write(0b10000010);
        Control_Reg_2_Write(0b000000);
        break;
    case C4:
        Control_Reg_1_Write(0b01000010);
        Control_Reg_2_Write(0b000000);
        break;
    case Csharp4:
        Control_Reg_1_Write(0b00000010);
        Control_Reg_2_Write(0b000000);
        break;
    default:
        break;
}

 
}

int main(void) {
    
    CyGlobalIntEnable; // Enable global interrupts
    Waveform_ISR_StartEx(Waveform_ISR); // Initialize the Waveform ISR
    Button_Switch_StartEx(Button_ISR); // Initialize the Button ISR
    Inputs_StartEx(Inputs_ISR); // Initialize the Button ISR
    NewNote_StartEx(Notes_ISR); // Initialize the Notes ISR
    
    // Initialize components
    Waveform_Send_Start(); // Start the Waveform Timer
    ReadInputs_Start(); // Start the inputs timer
    UpdateNote_Start(); // Start the song timer
    Wave_Out_Start(); // Start the DAC
    DACBuffer_Start(); // Start the OpAmp
    ADC_VolumePedal_Start(); // Start the Volume ADC
    
    // Initialize Display
    SPIM_1_Start(); 
    DisplayInit();
    
    for(;;) { displayNotes(); }  // Display 
}

void DisplayInit(){
    
    GUI_Init(); // Initialize the display
    GUI_Clear(); // Clear the Display

   
    GUI_SetFont(&GUI_Font8x16x2x2);
    GUI_DispStringAt("Ode to Joy", 40, 15); // Title of the Song
    
    // Notes of the Song
    
    GUI_DrawLine(20, 100, 20, 140); // Bar 1
    
    GUI_FillCircle(30, 105, 3);
    GUI_DrawLine(27, 105, 27, 135); // E quarter
    
    GUI_FillCircle(40, 105, 3);
    GUI_DrawLine(37, 105, 37, 135); // E quarter
    
    GUI_FillCircle(50, 100, 3);
    GUI_DrawLine(47, 100, 47, 130); // F quarter
    
    GUI_FillCircle(60, 95, 3);
    GUI_DrawLine(57, 95, 57, 125); // G quarter
    
    GUI_DrawLine(70, 100, 70, 140); // Bar 2
    
    GUI_FillCircle(80, 95, 3);
    GUI_DrawLine(77, 95, 77, 125); // G quarter
    
    GUI_FillCircle(90, 100, 3);
    GUI_DrawLine(87, 100, 87, 130); // F quarter
    
    GUI_FillCircle(100, 105, 3);
    GUI_DrawLine(97, 105, 97, 135); // E quarter
    
    GUI_FillCircle(110, 110, 3);
    GUI_DrawLine(107, 110, 107, 140); // D quarter
    
    GUI_DrawLine(120, 100, 120, 140); // Bar 3
    
    GUI_FillCircle(130, 115, 3);
    GUI_DrawLine(127, 115, 127, 145); // C quarter
    
    GUI_FillCircle(140, 115, 3);
    GUI_DrawLine(137, 115, 137, 145); // C quarter
    
    GUI_FillCircle(150, 110, 3);
    GUI_DrawLine(147, 110, 147, 140); // D quarter
    
    GUI_FillCircle(160, 105, 3);
    GUI_DrawLine(157, 105, 157, 135); // E quarter
    
    GUI_DrawLine(170, 100, 170, 140); // Bar 4
    
    GUI_FillCircle(180, 105, 3);
    GUI_DrawLine(177, 105, 177, 135); // E quarter
    
    GUI_FillCircle(190, 110, 3);
    GUI_DrawLine(187, 110, 187, 140); // D quarter
    
    GUI_DrawCircle(200, 110, 3);
    GUI_DrawLine(197, 110, 197, 140); // D half
    
    GUI_DrawLine(220, 100, 220, 140); // End
    
    // Note Lines
    
    GUI_DrawLine(20, 100, 220, 100);
    GUI_DrawLine(20, 110, 220, 110);
    GUI_DrawLine(20, 120,220, 120);
    GUI_DrawLine(20, 130, 220, 130);
    GUI_DrawLine(20, 140, 220, 140);
    
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringAt("Desired", 20, 200);
    GUI_DispStringAt("Note", 20, 220);
    GUI_DispStringAt("Played", 160, 200);
    GUI_DispStringAt("Note", 160, 220);
    
}

void displayNotes() {
    
    GUI_SetFont(&GUI_Font8x16x2x2);

    switch (desired_notes[desired_note_index]) {
        case Bb1: GUI_DispStringAt("Bb-1", 20, 240); break;
        case B1: GUI_DispStringAt("B-1 ", 20, 240); break;
        case C2: GUI_DispStringAt("C-2 ", 20, 240); break;
        case Csharp2: GUI_DispStringAt("C#-2", 20, 240); break;
        case D2: GUI_DispStringAt("D-2 ", 20, 240); break;
        case Dsharp2: GUI_DispStringAt("D#-2", 20, 240); break;
        case E2: GUI_DispStringAt("E-2 ", 20, 240); break;
        case F2: GUI_DispStringAt("F-2 ", 20, 240); break;
        case Fsharp2: GUI_DispStringAt("F#-2", 20, 240); break;
        case G2: GUI_DispStringAt("G-2 ", 20, 240); break;
        case Gsharp2: GUI_DispStringAt("G#-2", 20, 240); break;
        case A2: GUI_DispStringAt("A-2 ", 20, 240); break;
        case Bb2: GUI_DispStringAt("Bb-2", 20, 240); break;
        case B2: GUI_DispStringAt("B-2 ", 20, 240); break;
        case C3: GUI_DispStringAt("C-3 ", 20, 240); break;
        case Csharp3: GUI_DispStringAt("C#-3", 20, 240); break;
        case D3: GUI_DispStringAt("D-3 ", 20, 240); break;
        case Dsharp3: GUI_DispStringAt("D#-3", 20, 240); break;
        case E3: GUI_DispStringAt("E-3 ", 20, 240); break;
        case F3: GUI_DispStringAt("F-3 ", 20, 240); break;
        case Fsharp3: GUI_DispStringAt("F#-3", 20, 240); break;
        case G3: GUI_DispStringAt("G-3 ", 20, 240); break;
        case Gsharp3: GUI_DispStringAt("G#-3", 20, 240); break;
        case A3: GUI_DispStringAt("A-3 ", 20, 240); break;
        case Bb3: GUI_DispStringAt("Bb-3", 20, 240); break;
        case B3: GUI_DispStringAt("B-3 ", 20, 240); break;
        case C4: GUI_DispStringAt("C-4 ", 20, 240); break;
        case Csharp4: GUI_DispStringAt("C#-4", 20, 240); break;
    }
    
    if (note == desired_notes[desired_note_index]) {
        GUI_DispStringAt("==", 104, 240);
    } else {
        GUI_DispStringAt("!=", 104, 240);
    }
    
    switch (note) {
        case Bb1: GUI_DispStringAt("Bb-1", 160, 240); break;
        case B1: GUI_DispStringAt("B-1 ", 160, 240); break;
        case C2: GUI_DispStringAt("C-2 ", 160, 240); break;
        case Csharp2: GUI_DispStringAt("C#-2", 160, 240); break;
        case D2: GUI_DispStringAt("D-2 ", 160, 240); break;
        case Dsharp2: GUI_DispStringAt("D#-2", 160, 240); break;
        case E2: GUI_DispStringAt("E-2 ", 160, 240); break;
        case F2: GUI_DispStringAt("F-2 ", 160, 240); break;
        case Fsharp2: GUI_DispStringAt("F#-2", 160, 240); break;
        case G2: GUI_DispStringAt("G-2 ", 160, 240); break;
        case Gsharp2: GUI_DispStringAt("G#-2", 160, 240); break;
        case A2: GUI_DispStringAt("A-2 ", 160, 240); break;
        case Bb2: GUI_DispStringAt("Bb-2", 160, 240); break;
        case B2: GUI_DispStringAt("B-2 ", 160, 240); break;
        case C3: GUI_DispStringAt("C-3 ", 160, 240); break;
        case Csharp3: GUI_DispStringAt("C#-3", 160, 240); break;
        case D3: GUI_DispStringAt("D-3 ", 160, 240); break;
        case Dsharp3: GUI_DispStringAt("D#-3", 160, 240); break;
        case E3: GUI_DispStringAt("E-3 ", 160, 240); break;
        case F3: GUI_DispStringAt("F-3 ", 160, 240); break;
        case Fsharp3: GUI_DispStringAt("F#-3", 160, 240); break;
        case G3: GUI_DispStringAt("G-3 ", 160, 240); break;
        case Gsharp3: GUI_DispStringAt("G#-3", 160, 240); break;
        case A3: GUI_DispStringAt("A-3 ", 160, 240); break;
        case Bb3: GUI_DispStringAt("Bb-3", 160, 240); break;
        case B3: GUI_DispStringAt("B-3 ", 160, 240); break;
        case C4: GUI_DispStringAt("C-4 ", 160, 240); break;
        case Csharp4: GUI_DispStringAt("C#-4", 160, 240); break;
    }
     
    //if (isChange) {
    //    GUI_SetFont(&GUI_Font8x16);
    //    GUI_DispStringAt("                                                 ", 20, 60);
    //    GUI_DispStringAt("v", note_locations[desired_note_index]-4, 60);
    //    isChange = 0;
   // }
    
}
/* [] END OF FILE */
