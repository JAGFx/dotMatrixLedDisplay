//
// Created by emsm on 24-Feb-19.
//

#ifndef DISPLAYTEXTDOTMATRIX_ORCHESTRATOR_H
#define DISPLAYTEXTDOTMATRIX_ORCHESTRATOR_H

#include "../Slides/TextSlide.h"
#include <MD_Parola.h>
#include <QueueH.h>

#define    BUF_SIZE    75


class Orchestrator {
    static const uint8_t        DEFAULT_MIN_DISPLAY   = 1;
    static const uint8_t        DEFAULT_LED_INTENSITY = 1;
    static const uint8_t        DEFAULT_SCROLL_SPEED  = 35;
    static const textPosition_t DEFAULT_SCROLL_ALIGN  = PA_CENTER;
    static const uint8_t        MAX_SLIDE_IN_QUEUE    = 10;

public:
    
    explicit Orchestrator( MD_MAX72XX::moduleType_t mod, uint8_t dataPin, uint8_t clkPin, uint8_t csPin,
                           uint8_t numDevices = DEFAULT_MIN_DISPLAY );
    
    // Matrix
    MD_Parola getMatrix();
    
    void begin();
    
    void updateDisplay();
    // ----
    
    // Project configuration
    // ----
    
    // Project management
    void addInQueue( TextSlide *textSlide );
    
    void clearQueue();
    
    bool newSlideAreAvailable();
    
    void updateCurrentSlide();
    // ----



protected:
    // Matrix
    MD_Parola matrix;
    // ----
    
    // Project configuration
    
    // ----
    
    // Project management
    QueueH < TextSlide * > queue                = QueueH < TextSlide * >( MAX_SLIDE_IN_QUEUE );
    TextSlide              *currentTextSlide    = nullptr;
    TextSlide              *prevTextSlide       = nullptr;
    // ----
};


#endif //DISPLAYTEXTDOTMATRIX_ORCHESTRATOR_H
