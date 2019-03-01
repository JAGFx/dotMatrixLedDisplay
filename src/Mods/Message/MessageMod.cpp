//
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 01-Mar-19
// Time: 08:53 PM
//

#include "MessageMod.h"
#include "../../Engine/Orchestrator.h"

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

void MessageMod::updateDisplay( MD_Parola &matrix ) {
    Serial.print( "Is available ?" );
    Serial.println( needToRefresh() );
    
    if ( needToRefresh() ) {
        updateCurrentMessageItem();
        
        Serial.print( "Message: " );
        Serial.println( currentMessageItem->getText() );
        
        matrix.displayText( currentMessageItem->getText(),
                            Orchestrator::DEFAULT_SCROLL_ALIGN,
                            Orchestrator::DEFAULT_SCROLL_SPEED,
                            currentMessageItem->getDelayAtEnd(),
                            currentMessageItem->getEffectIn(),
                            currentMessageItem->getEffectOut() );
        
        Serial.println( "======================" );
    }
}

bool MessageMod::instanceOfMod( IMod::ModeType type ) {
    return type == IMod::ModeType::MessageMod;
}

// -------------------------------------
