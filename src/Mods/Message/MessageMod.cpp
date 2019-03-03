//
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 01-Mar-19
// Time: 08:53 PM
//

#include "MessageMod.h"
#include "../../Engine/Orchestrator.h"
#include "MessageSprites.h"

MessageMod::MessageMod() = default;

// -------------------------------------
// -- Mod management

void MessageMod::addInQueue( MessageItem *textSlide ) {
    queue.push( textSlide );
}

void MessageMod::clearQueue() {
    queue.clear();
}

void MessageMod::updateCurrentMessageItem() {
    if ( currentMessageItem != nullptr ) {
        prevTextSlide = currentMessageItem;
        delete prevTextSlide;
    }
    
    currentMessageItem = queue.pop();
}

// -------------------------------------


// -------------------------------------
// -- IMod

bool MessageMod::needToRefresh() {
    // Serial.println(queue.count());
    
    return queue.count() > 0;
}

void MessageMod::updateDisplay( MD_Parola *matrix ) {
    Serial.print( "Is available ?" );
    Serial.println( needToRefresh() );
    
    if ( needToRefresh() ) {
        updateCurrentMessageItem();
        
        Serial.print( "Message: " );
        Serial.println( currentMessageItem->getText() );
    
        matrix->displayText( currentMessageItem->getText(),
                             Orchestrator::DEFAULT_SCROLL_ALIGN,
                             Orchestrator::DEFAULT_SCROLL_SPEED,
                             currentMessageItem->getDelayAtEnd(),
                             currentMessageItem->getEffectIn(),
                             currentMessageItem->getEffectOut() );
    
        /*if ( currentMessageItem->getEffectIn() == PA_SPRITE ) {
            Serial.println( "SPRIIIIIIIIITE !!!" );
            
            const uint8_t PROGMEM rocket[] = {
                    0x18, 0x3c, 0x66, 0xc3, 0x99, 0x3c, 0x66, 0xc3, 0x81,
            };
            
            matrix->setSpriteData( rocket,
                                   Chevron::widthFrameByte,
                                   Chevron::numberOfFrame,
                                   rocket,
                                   Chevron::widthFrameByte,
                                   Chevron::numberOfFrame );
            
            *//*matrix->setSpriteData( Chevron::spriteData,
                                  Chevron::widthFrameByte,
                                  Chevron::numberOfFrame,
                                  Chevron::spriteData,
                                  Chevron::widthFrameByte,
                                  Chevron::numberOfFrame );*//*
        }*/
        
        Serial.println( "======================" );
    }
}

void MessageMod::init( MD_Parola *matrix ) {

}

void MessageMod::reset( MD_Parola *matrix ) {

}

bool MessageMod::instanceOfMod( IMod::ModeType type ) {
    return type == IMod::ModeType::MessageMod;
}

// -------------------------------------
