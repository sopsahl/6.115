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
#include "GUI.h"
#include "tft.h"
enum Note {
    Bb1, B1, C2, Csharp2, D2, Dsharp2, E2, F2, Fsharp2, G2, Gsharp2, A2,
    Bb2, B2, C3, Csharp3, D3, Dsharp3, E3, F3, Fsharp3, G3, Gsharp3, A3,
    Bb3, B3, C4, Csharp4
};


void MainTask(void);
void displayNotes(enum Note, enum Note);



int main()
{
    enum Note note = Csharp4;
    CyGlobalIntEnable;                      // Enable global interrupts
    SPIM_1_Start();                         // initialize SPIM component 
    MainTask();                             // all of the emWin exmples use MainTask() as the entry point
    for(;;) {}                              // loop
}

void MainTask()
{
    GUI_Init();                             // initilize graphics library
    GUI_Clear();
    
    displayNotes(Csharp2, Csharp2);
    
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringAt("Desired", 20, 20);
    GUI_DispStringAt("Note", 20, 40);
    GUI_DrawLine(20, 100,80, 100);
    GUI_DrawLine(20, 120, 80, 120);
    GUI_DrawLine(20, 140, 80, 140);
    GUI_DrawLine(20, 160, 80, 160);
    GUI_DrawLine(20, 180, 80, 180);
    
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringAt("Played", 160, 20);
    GUI_DispStringAt("Note", 160, 40);
    GUI_DrawLine(160, 100,220,100);
    GUI_DrawLine(160, 120, 220, 120);
    GUI_DrawLine(160, 140, 220, 140);
    GUI_DrawLine(160, 160, 220, 160);
    GUI_DrawLine(160, 180, 220, 180);
    GUI_SetFont(&GUI_Font8x16x2x2);
    GUI_DispStringAt("Bb-1", 160, 240);
    
    if (1) {
        GUI_SetFont(&GUI_Font8x16x2x2);
        GUI_DispStringAt("==", 104, 240);
    } else {
        GUI_SetFont(&GUI_Font8x16x2x2);
        GUI_DispStringAt("!=", 104, 240);
    }
    
}

void displayNotes(enum Note played, enum Note desired) {
    switch (desired) {
        case Bb1:
            GUI_SetFont(&GUI_Font8x16x2x2);
            GUI_DispStringAt("Bb-1", 20, 240);
            GUI_DrawCircle(50, 205, 5);
            GUI_SetFont(&GUI_Font8x16);
            GUI_DispStringAt("b", 35, 197);
            GUI_DrawLine(40, 200, 60, 200);
            break;
        case B1:
            GUI_SetFont(&GUI_Font8x16x2x2);
            GUI_DispStringAt("B-1", 20, 240);
            GUI_DrawCircle(50, 205, 5);
            GUI_DrawLine(40, 200, 60, 200);
            break;
        case C2:
            GUI_SetFont(&GUI_Font8x16x2x2);
            GUI_DispStringAt("C-2", 20, 240);
            GUI_DrawCircle(50, 200, 5);
            GUI_DrawLine(40, 200, 60, 200);
            break;
        case Csharp2:
            GUI_SetFont(&GUI_Font8x16x2x2);
            GUI_DispStringAt("C#-2", 20, 240);
            GUI_DrawCircle(50, 200, 5);
            GUI_SetFont(&GUI_Font8x16);
            GUI_DispStringAt("#", 35, 192);
            GUI_DrawLine(40, 200, 60, 200); 
            break;
        case D2:
            GUI_SetFont(&GUI_Font8x16x2x2);
            GUI_DispStringAt("D-2", 20, 240);
            GUI_DrawCircle(50, 185, 5);
            break;
        case Dsharp2:
            GUI_SetFont(&GUI_Font8x16x2x2);
            GUI_DispStringAt("D#-2", 20, 240);
            GUI_DrawCircle(50, 185, 5);
            GUI_SetFont(&GUI_Font8x16);
            GUI_DispStringAt("#", 35, 177);
            break;
        case E2:
            GUI_SetFont(&GUI_Font8x16x2x2);
            GUI_DispStringAt("D-2", 20, 240);
            GUI_DrawCircle(50, 185, 5);
            GUI_SetFont(&GUI_Font8x16);
            GUI_DispStringAt("#", 35, 177);
            break;
        case F2:
        case Fsharp2:
        case G2:
        case Gsharp2:
        case A2:
        case Bb2:
        case B2:
        case C3:
        case Csharp3:
        case D3:
        case Dsharp3:
        case E3:
        case F3:
        case Fsharp3:
        case G3:
        case Gsharp3:
        case A3:
        case Bb3:
        case B3:
        case C4:
        case Csharp4:break;
}
}
/* [] END OF FILE */
