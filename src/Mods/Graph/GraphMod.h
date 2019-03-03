//
// Created by CLion.
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 02-Mar-19
// Time: 10:05
//

#ifndef DOTMATRIXLEDDISPLAY_GRAPHMOD_H
#define DOTMATRIXLEDDISPLAY_GRAPHMOD_H

#include <MD_MAX72XX.h>
#include "../../Engine/IMod.h"

class GraphMod : public IMod {
public:
    static const uint8_t BASELINE_ROW = 4;
    
    static const uint8_t STATE_START        = 0;
    static const uint8_t STATE_FIRST_STROKE = 1;
    static const uint8_t STATE_DOWN_STROKE  = 2;
    static const uint8_t STATE_UP_STROKE    = 3;
    static const uint8_t STATE_LAST_STROKE  = 4;
    
    
    // IMod
    virtual void updateDisplay( MD_Parola *matrix );
    
    virtual void init( MD_Parola *matrix );
    
    virtual void reset( MD_Parola *matrix );
    
    virtual bool needToRefresh();
    
    virtual bool instanceOfMod( ModeType type );
    // ---

protected:
    
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
