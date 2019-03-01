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
        Serial.println( "Plop" );
        currentMod->updateDisplay( matrix );
    }
}

// -------------------------------------


// -------------------------------------
// -- Mod management

IMod *Orchestrator::getCurrentMod() {
    return currentMod;
}

void Orchestrator::setCurrentMod( IMod *currentMod ) {
    Orchestrator::currentMod = currentMod;
}

// -------------------------------------

