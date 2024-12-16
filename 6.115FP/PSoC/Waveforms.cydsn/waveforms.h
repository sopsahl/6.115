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

// waveforms.h

#ifndef WAVEFORMS_H
#define WAVEFORMS_H

#include <stdint.h>

extern uint32_t waveform_sizes[4];
extern uint16_t beginning_waveform[2316];
extern uint16_t repeat_waveform[56];
extern uint16_t end_waveform[5764];
extern uint16_t default_waveform[1];
enum Waveform {
    Beginning,    // Beginning Waveform
    Repeat,  // Repeating Waveform
    End,    // Ending Waveform
    Default    // No waveform
};

#endif /* WAVEFORMS_H */