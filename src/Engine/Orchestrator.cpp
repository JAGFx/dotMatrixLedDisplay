//
// Created by emsm on 24-Feb-19.
//

#include "Orchestrator.h"


Orchestrator::Orchestrator( MD_MAX72XX::moduleType_t mod, uint8_t dataPin, uint8_t clkPin, uint8_t csPin,
                            uint8_t numDevices ) : matrix( MD_Parola( mod, dataPin, clkPin, csPin, numDevices ) ) {
    matrix.setIntensity( Orchestrator::DEFAULT_LED_INTENSITY );
}

// -------------------------------------
// -- Matrix

MD_Parola Orchestrator::getMatrix() {
    //Serial.println( "Get matrix" );
    return matrix;
}

void Orchestrator::begin() {
    matrix.begin();
    Serial.println( "Matrix begin" );
}

void Orchestrator::updateDisplay() {
    if ( matrix.displayAnimate() ) {
        Serial.print( "Is available ?" );
        Serial.println( newSlideAreAvailable() );
        
        if ( newSlideAreAvailable() ) {
            
            prevTextSlide = currentTextSlide;
            delete prevTextSlide;
            currentTextSlide = getNextSlide();
            
            currentTextSlide->getText()->toCharArray( curMessage, currentTextSlide->getText()->length() + 1 );
            
            Serial.print( "Message: " );
            Serial.println( curMessage );
            
            matrix.displayText( curMessage,
                                DEFAULT_SCROLL_ALIGN,
                                DEFAULT_SCROLL_SPEED,
                                currentTextSlide->getDelayAtEnd(),
                                currentTextSlide->getEffect(),
                                currentTextSlide->getEffect() );
            
            Serial.println( "======================" );
            
        } else {
            Serial.println( "Reset" );
            resetQueue();
            Serial.println( "======================" );
        }
    }
}

void Orchestrator::resetQueue() {
    clearQueue();
    addInQueue( new TextSlide( new String( "Norway is comming soon !" ), PA_SCROLL_LEFT, 0 ) );
    addInQueue( new TextSlide( new String( "\\o/" ), PA_DISSOLVE, 2000 ) );
}

// -------------------------------------


// -------------------------------------
// -- Project configuration

// -------------------------------------



// -------------------------------------
// -- Project management

void Orchestrator::addInQueue( TextSlide *textSlide ) {
    queue.push( textSlide );
}

void Orchestrator::clearQueue() {
    queue.clear();
}

bool Orchestrator::newSlideAreAvailable() {
    // Serial.println(queue.count());
    
    return queue.count() > 0;
}

TextSlide *Orchestrator::getNextSlide() {
    return queue.pop();
}

// -------------------------------------
