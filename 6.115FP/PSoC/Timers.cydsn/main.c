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

CY_ISR(Timer_ISR)
{
    // Toggle the digital pin
    Pin_1_Write(~Pin_1_Read());
    Waveform_Send_ReadStatusRegister();
}


int main(void)
{
    // Initialize components
    CyGlobalIntEnable; // Enable global interrupts
    uint16 periods[28] = {4110, 3879, 3662, 3455, 3262, 3078, 2906, 2742, 2589, 2444, 2306, 2177, 2054, 1939, 1830, 1728, 1631, 1539, 1453, 1371, 1294, 1222, 1153, 1088, 1027, 970, 915, 864};
    
    // Initialize Timer
    Timer_ISR_StartEx(Timer_ISR);
    Waveform_Send_Start(); // Start the timer
    
    for(;;)
    {
        for (int i = 0; i < 28; i++){
             Waveform_Send_WritePeriod(periods[i]);
            CyDelay(10000);
        }
    }
}


/* [] END OF FILE */
