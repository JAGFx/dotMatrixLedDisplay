//
// Created by CLion.
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 02-Mar-19
// Time: 10:05
//

#ifndef DOTMATRIXLEDDISPLAY_GRAPHMOD_H
#define DOTMATRIXLEDDISPLAY_GRAPHMOD_H

#include <MD_MAX72xx.h>
#include "../../Engine/IMod.h"

class GraphMod : public IMod {
public:
    static const uint8_t BASELINE_ROW = 4;
    
    static const uint8_t STATE_START        = 0;
    static const uint8_t STATE_FIRST_STROKE = 1;
    static const uint8_t STATE_DOWN_STROKE  = 2;
    static const uint8_t STATE_UP_STROKE    = 3;
    static const uint8_t STATE_LAST_STROKE  = 4;
    
    static const uint8_t SPEED_ANIMATION_MS = 1000;
    
    // IMod
    virtual void updateDisplay( MD_Parola *matrix );
    
    virtual void init( MD_Parola *matrix );
    
    virtual void reset( MD_Parola *matrix );
    
    virtual bool needToRefresh();
    
    virtual String currentData();
    
    virtual bool instanceOfMod( ModeType type );
    // ---
    
    const uint8_t getOriginalColumnCount();
    

protected:
    uint8_t originalColumnCount = 0;
    
    // --- Heartbeat
    uint8_t currentState      = STATE_START;
    uint8_t baselineRow       = BASELINE_ROW;
    uint8_t columnCount       = 0;
    bool    bPoint            = true;
    bool    restart           = true;
    bool    animationFinished = false;
    // ---
};


#endif //DOTMATRIXLEDDISPLAY_GRAPHMOD_H
