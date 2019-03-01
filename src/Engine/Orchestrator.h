//
// Created by emsm on 24-Feb-19.
//

#ifndef DISPLAYTEXTDOTMATRIX_ORCHESTRATOR_H
#define DISPLAYTEXTDOTMATRIX_ORCHESTRATOR_H

#include "../Mods/Message/MessageItem.h"
#include "IMod.h"
#include <MD_Parola.h>

class Orchestrator {


public:
    static const uint8_t        DEFAULT_MIN_DISPLAY   = 1;
    static const uint8_t        DEFAULT_LED_INTENSITY = 1;
    static const textPosition_t DEFAULT_SCROLL_ALIGN  = PA_CENTER;
    static const uint8_t        DEFAULT_SCROLL_SPEED  = 35;
    
    
    explicit Orchestrator( MD_MAX72XX::moduleType_t mod, uint8_t dataPin, uint8_t clkPin, uint8_t csPin,
                           uint8_t numDevices = DEFAULT_MIN_DISPLAY );
    
    // Matrix
    MD_Parola getMatrix();
    
    void begin();
    
    void updateDisplay();
    // ----
    
    // Mod management
    IMod *getCurrentMod();
    
    void setCurrentMod( IMod *currentMod );
    // ----
    
protected:
    // Matrix
    MD_Parola matrix;
    // ----
    
    // Mod management
    IMod *currentMod = nullptr;
    // ----
    
    
};


#endif //DISPLAYTEXTDOTMATRIX_ORCHESTRATOR_H
